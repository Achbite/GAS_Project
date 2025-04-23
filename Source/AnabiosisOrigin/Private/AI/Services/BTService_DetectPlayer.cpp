/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: BTService_DetectPlayer.cpp
* 功能描述： 实现 BTService_DetectPlayer 的逻辑。
*/

#include "AI/Services/BTService_DetectPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EnemyBaseCharacter.h"
#include "AI/AiBehaviorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h" // For Player Character
#include "GameplayTagContainer.h" // For Gameplay Tags
#include "DrawDebugHelpers.h" // For Debug Lines
#include "GameFramework/Actor.h" // Include for IsValid check

// --- Gameplay Tag Constants ---
#define AI_STATE_TAG_NAME(TagName) FName(TagName)

UBTService_DetectPlayer::UBTService_DetectPlayer()
{
	NodeName = "Detect Player Service";

	// 设置服务间隔和随机偏差，以避免所有 AI 同时执行检测
	Interval = 0.5f;
	RandomDeviation = 0.1f;

	// 确保 Blackboard Key 选择器被正确初始化
	TargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_DetectPlayer, TargetActorKey), AActor::StaticClass());
	AIStateKey.AddNameFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_DetectPlayer, AIStateKey));

	// 服务需要在每次激活时执行 Tick
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = false; // 不需要停止时的通知

	// 初始化缓存指针
	CachedAiBehaviorComp = nullptr;
	CachedOwnerCharacter = nullptr;
	CachedOwnerController = nullptr;
	CachedBlackboardComp = nullptr;
}

bool UBTService_DetectPlayer::CacheComponents(UBehaviorTreeComponent& OwnerComp)
{
	// 尝试获取 Controller
	if (!IsValid(CachedOwnerController)) // Check if controller is valid or needs recaching
	{
		CachedOwnerController = OwnerComp.GetAIOwner();
		if (!IsValid(CachedOwnerController)) return false; // Still invalid after getting
	}

	// 尝试获取 Pawn
	if (!IsValid(CachedOwnerCharacter)) // Check if character is valid or needs recaching
	{
		CachedOwnerCharacter = Cast<AEnemyBaseCharacter>(CachedOwnerController->GetPawn());
		if (!IsValid(CachedOwnerCharacter)) return false; // Still invalid after getting
	}

	// 尝试获取 AiBehaviorComp
	if (!IsValid(CachedAiBehaviorComp)) // Check if behavior comp is valid or needs recaching
	{
		// Ensure OwnerCharacter is valid before accessing it
		if (!IsValid(CachedOwnerCharacter)) return false;
		CachedAiBehaviorComp = CachedOwnerCharacter->FindComponentByClass<UAiBehaviorComponent>();
		if (!IsValid(CachedAiBehaviorComp)) return false; // Still invalid after getting
	}

	// 尝试获取 Blackboard
	if (!IsValid(CachedBlackboardComp)) // Check if blackboard is valid or needs recaching
	{
		CachedBlackboardComp = OwnerComp.GetBlackboardComponent(); // Use OwnerComp's BB
		if (!IsValid(CachedBlackboardComp)) return false; // Still invalid after getting
	}

	return true; // All necessary components seem valid
}


void UBTService_DetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// --- 重命名局部变量 ---
	// Use cached controller/pawn for logging if available, otherwise get fresh ones
	AAIController* ControllerForLog = IsValid(CachedOwnerController) ? CachedOwnerController.Get() : OwnerComp.GetAIOwner(); // 重命名
	APawn* LogPawn = IsValid(CachedOwnerCharacter) ? CachedOwnerCharacter.Get() : (ControllerForLog ? ControllerForLog->GetPawn() : nullptr); // 使用新名字
	UE_LOG(LogTemp, Verbose, TEXT("BTService_DetectPlayer::TickNode: Controller: %s, Pawn: %s"),
		ControllerForLog ? *ControllerForLog->GetName() : TEXT("NULL"), // 使用新名字
		LogPawn ? *LogPawn->GetName() : TEXT("NULL"));
	// -----------------------

	// 1. 获取/验证必要的组件和黑板
	if (!CacheComponents(OwnerComp))
	{
		// --- 修改日志级别为 Verbose，避免过多 Warning ---
		UE_LOG(LogTemp, Verbose, TEXT("BTService_DetectPlayer: Failed to get or cache required components. Controller: %s, Pawn: %s"),
			ControllerForLog ? *ControllerForLog->GetName() : TEXT("NULL"), // 使用新名字
			LogPawn ? *LogPawn->GetName() : TEXT("NULL"));
		// ---------------------------------------------
		return;
	}

	// 如果角色已死亡，设置状态并返回 (确保使用缓存的 Blackboard)
	if (CachedOwnerCharacter->IsDead()) // Assumes CachedOwnerCharacter is valid due to CacheComponents check
	{
		// Check if blackboard is valid before using
		if(IsValid(CachedBlackboardComp))
		{
			CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
			CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Dead"));
			UE_LOG(LogTemp, Verbose, TEXT("BTService_DetectPlayer: Owner %s is dead, setting state to Dead."), *CachedOwnerCharacter->GetName());
		}
		// Consider stopping the tree if not already handled by death logic
		// OwnerComp.StopTree(EBTStopMode::Safe);
		return;
	}

	// 2. 获取当前状态和目标 (确保使用缓存的 Blackboard)
	FName CurrentStateName = CachedBlackboardComp->GetValueAsName(AIStateKey.SelectedKeyName);
	AActor* CurrentTarget = Cast<AActor>(CachedBlackboardComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0); // 获取第一个玩家

	// 3. 检查玩家是否存在且有效
	if (!IsValid(PlayerCharacter))
	{
		// 如果没有有效玩家，且当前在追击或攻击，则返回或进入 Idle
		if (CurrentStateName == AI_STATE_TAG_NAME("AI.State.Chasing") || CurrentStateName == AI_STATE_TAG_NAME("AI.State.Attacking"))
		{
			CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
			// Decide whether to return home or go idle based on behavior type perhaps
			// For now, let's go Idle if no player exists
			CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Idle"));
			UE_LOG(LogTemp, Log, TEXT("%s: Player not found or invalid, going Idle."), *CachedOwnerCharacter->GetName());
		}
		// If already Idle, Patrolling, Returning, no need to change state here if player disappears
		return; // 没有玩家可检测
	}

	// 4. 主要逻辑：根据当前状态决定行为
	bool bPlayerDetected = CachedAiBehaviorComp->IsInDetectionRange(PlayerCharacter) && HasLineOfSight(CachedOwnerController, PlayerCharacter);
	bool bPlayerInChaseRange = CachedAiBehaviorComp->IsInChaseRange(PlayerCharacter);
	bool bHasLineOfSightToPlayer = HasLineOfSight(CachedOwnerController, PlayerCharacter); // 单独获取视线状态

	if (CurrentStateName == AI_STATE_TAG_NAME("AI.State.Chasing") || CurrentStateName == AI_STATE_TAG_NAME("AI.State.Attacking"))
	{
		// 当前在追击或攻击
		bool bTargetIsPlayer = (CurrentTarget == PlayerCharacter);

		// --- 添加详细日志 ---
		UE_LOG(LogTemp, Verbose, TEXT("%s: In Chasing/Attacking State. TargetIsPlayer: %s, InChaseRange: %s, HasLoS: %s"),
			*CachedOwnerCharacter->GetName(),
			bTargetIsPlayer ? TEXT("true") : TEXT("false"),
			bPlayerInChaseRange ? TEXT("true") : TEXT("false"),
			bHasLineOfSightToPlayer ? TEXT("true") : TEXT("false"));
		// --------------------

		if (bTargetIsPlayer && bPlayerInChaseRange && bHasLineOfSightToPlayer)
		{
			// 目标有效且在范围内/视线内，保持当前状态 (由BT其他部分决定是 Chasing 还是 Attacking)
			// UE_LOG(LogTemp, Verbose, TEXT("%s: Target %s still valid in chase/attack."), *CachedOwnerCharacter->GetName(), *PlayerCharacter->GetName());
		}
		else
		{
			// 目标丢失 (超出范围、丢失视线或目标改变/无效)
			// --- 添加目标丢失原因日志 ---
			FString LostReason = TEXT("");
			if (!bTargetIsPlayer) LostReason += TEXT("Target changed; ");
			if (!bPlayerInChaseRange) LostReason += TEXT("Out of chase range; ");
			if (!bHasLineOfSightToPlayer) LostReason += TEXT("Lost line of sight; ");
			UE_LOG(LogTemp, Log, TEXT("%s: Lost target %s. Reason: %s Returning home."),
				*CachedOwnerCharacter->GetName(),
				PlayerCharacter ? *PlayerCharacter->GetName() : TEXT("NULL"),
				*LostReason);
			// ---------------------------

			CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
			// 根据行为类型决定是返回还是搜索等，这里先设置为 Returning
			CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Returning"));
		}
	}
	else // 非追击/攻击状态 (Idle, Patrolling, Returning)
	{
		// --- 添加检测日志 ---
		UE_LOG(LogTemp, Verbose, TEXT("%s: In Non-Chasing State (%s). PlayerDetected: %s (InDetectRange: %s, HasLoS: %s)"),
			*CachedOwnerCharacter->GetName(),
			*CurrentStateName.ToString(),
			bPlayerDetected ? TEXT("true") : TEXT("false"),
			CachedAiBehaviorComp->IsInDetectionRange(PlayerCharacter) ? TEXT("true") : TEXT("false"), // Log individual components of detection
			bHasLineOfSightToPlayer ? TEXT("true") : TEXT("false"));
		// --------------------

		if (bPlayerDetected)
		{
			// 发现玩家！设置目标并切换到追击状态
			CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, PlayerCharacter);
			CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Chasing"));
			UE_LOG(LogTemp, Log, TEXT("%s: Detected player %s, starting chase!"), *CachedOwnerCharacter->GetName(), *PlayerCharacter->GetName());
		}
		else
		{
			// 未发现玩家或玩家不在视线/范围内
			// 如果之前有目标 (例如刚从追击切换过来)，则清除目标
			if (CurrentTarget != nullptr)
			{
				CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
				UE_LOG(LogTemp, Verbose, TEXT("%s: Target cleared (was %s)."), *CachedOwnerCharacter->GetName(), *CurrentTarget->GetName());
				// 不需要改变状态，让行为树的其他部分处理 Idle/Patrolling/Returning 逻辑
			}
		}
	}
}

bool UBTService_DetectPlayer::HasLineOfSight(AAIController* OwnerController, const AActor* TargetActor) const
{
	if (!OwnerController || !TargetActor)
	{
		return false;
	}

	// 使用 AIController 的内置视线检查
	// 注意：这依赖于 AIController 的 PerceptionComponent 设置（如果使用的话）或默认实现
	bool bHasLoS = OwnerController->LineOfSightTo(TargetActor);

	// --- 可选：添加调试线 ---
	#if ENABLE_DRAW_DEBUG
	if (CachedOwnerCharacter)
	{
		FVector Start = CachedOwnerCharacter->GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		FColor LineColor = bHasLoS ? FColor::Green : FColor::Red;
		DrawDebugLine(GetWorld(), Start, End, LineColor, false, Interval, 0, 1.0f);
	}
	#endif
	// -----------------------

	return bHasLoS;

	// --- 或者，使用简单的 LineTrace ---
	/*
	if (!CachedOwnerCharacter) return false;
	FVector StartLocation = CachedOwnerCharacter->GetActorLocation(); // 或者眼睛的位置
	FVector EndLocation = TargetActor->GetActorLocation();
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(CachedOwnerCharacter); // 忽略自身

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility, // 使用 Visibility 通道
		QueryParams
	);

	#if ENABLE_DRAW_DEBUG
	FColor LineColor = (!bHit || HitResult.GetActor() == TargetActor) ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, LineColor, false, Interval, 0, 1.0f);
	#endif

	// 如果没有命中，或者命中的是目标 Actor，则认为有视线
	return !bHit || HitResult.GetActor() == TargetActor;
	*/
}
