/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: BTService_DetectPlayer.cpp
* 功能描述： 实现行为树服务节点 UBTService_DetectPlayer 的逻辑。
*            周期性地检测玩家，判断距离、视线，并根据当前 AI 状态更新黑板中的目标和状态。
* 结构：
* - 构造函数：设置节点名称、服务间隔和黑板键过滤器。
* - CacheComponents：缓存常用组件以提高性能。
* - TickNode：服务核心逻辑，包括：
*   - 获取和验证组件。
*   - 处理角色死亡状态。
*   - 获取玩家角色。
*   - 根据当前状态（追击、攻击、其他）和检测结果（距离、视线）更新黑板中的 TargetActor 和 AIState。
* - HasLineOfSight：检查 AI 对目标的视线。
*/

#include "AI/Services/BTService_DetectPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EnemyBaseCharacter.h"
#include "AI/AiBehaviorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h" // 包含玩家角色类
#include "GameplayTagContainer.h" // 包含 GameplayTag
#include "DrawDebugHelpers.h" // 包含调试绘制函数
#include "GameFramework/Actor.h" // 包含 Actor 类

// --- Gameplay Tag 常量 ---
// 将字符串转换为 FName，用于设置黑板中的 GameplayTag Name
#define AI_STATE_TAG_NAME(TagName) FName(TagName)

UBTService_DetectPlayer::UBTService_DetectPlayer()
{
	NodeName = "Detect Player Service"; // 设置节点在行为树编辑器中的显示名称

	// 设置服务执行的间隔和随机偏差
	Interval = 0.5f; // 每 0.5 秒执行一次
	RandomDeviation = 0.1f; // 随机偏差 0.1 秒

	// 确保黑板键选择器被正确初始化，并设置过滤器
	TargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_DetectPlayer, TargetActorKey), AActor::StaticClass()); // 目标 Actor 键，只接受 Actor 对象
	AIStateKey.AddNameFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_DetectPlayer, AIStateKey)); // AI 状态键，只接受 Name 类型 (存储 GameplayTag 的 Name)

	// 设置服务通知类型
	bNotifyBecomeRelevant = true; // 当服务变得相关时（即其所在分支被激活时）执行 Tick
	bNotifyCeaseRelevant = false; // 当服务不再相关时不需要通知

	// 初始化缓存指针为空
	CachedAiBehaviorComp = nullptr;
	CachedOwnerCharacter = nullptr;
	CachedOwnerController = nullptr;
	CachedBlackboardComp = nullptr;
}

bool UBTService_DetectPlayer::CacheComponents(UBehaviorTreeComponent& OwnerComp)
{
	// 尝试获取并缓存 AI 控制器
	if (!IsValid(CachedOwnerController)) // 检查缓存是否有效或需要重新获取
	{
		CachedOwnerController = OwnerComp.GetAIOwner();
		if (!IsValid(CachedOwnerController)) return false; // 获取后仍然无效则失败
	}

	// 尝试获取并缓存拥有的敌人角色
	if (!IsValid(CachedOwnerCharacter)) // 检查缓存是否有效或需要重新获取
	{
		CachedOwnerCharacter = Cast<AEnemyBaseCharacter>(CachedOwnerController->GetPawn());
		if (!IsValid(CachedOwnerCharacter)) return false; // 获取后仍然无效则失败
	}

	// 尝试获取并缓存 AI 行为组件
	if (!IsValid(CachedAiBehaviorComp)) // 检查缓存是否有效或需要重新获取
	{
		// 确保 OwnerCharacter 有效才能访问其组件
		if (!IsValid(CachedOwnerCharacter)) return false;
		CachedAiBehaviorComp = CachedOwnerCharacter->FindComponentByClass<UAiBehaviorComponent>();
		if (!IsValid(CachedAiBehaviorComp)) return false; // 获取后仍然无效则失败
	}

	// 尝试获取并缓存黑板组件
	if (!IsValid(CachedBlackboardComp)) // 检查缓存是否有效或需要重新获取
	{
		CachedBlackboardComp = OwnerComp.GetBlackboardComponent(); // 使用行为树组件的黑板
		if (!IsValid(CachedBlackboardComp)) return false; // 获取后仍然无效则失败
	}

	return true; // 所有必要的组件都已成功缓存或获取
}


void UBTService_DetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds); // 调用父类实现

	// --- 日志记录：获取用于日志的控制器和 Pawn ---
	AAIController* ControllerForLog = IsValid(CachedOwnerController) ? CachedOwnerController.Get() : OwnerComp.GetAIOwner();
	APawn* LogPawn = IsValid(CachedOwnerCharacter) ? CachedOwnerCharacter.Get() : (ControllerForLog ? ControllerForLog->GetPawn() : nullptr);
	UE_LOG(LogTemp, Verbose, TEXT("检测玩家服务 Tick：控制器：%s，Pawn：%s"),
		ControllerForLog ? *ControllerForLog->GetName() : TEXT("空"),
		LogPawn ? *LogPawn->GetName() : TEXT("空"));
	// -------------------------------------------

	// 1. 获取/验证必要的组件和黑板
	if (!CacheComponents(OwnerComp))
	{
		// 如果获取组件失败，记录日志并返回
		UE_LOG(LogTemp, Verbose, TEXT("检测玩家服务：获取或缓存所需组件失败。控制器：%s，Pawn：%s"),
			ControllerForLog ? *ControllerForLog->GetName() : TEXT("空"),
			LogPawn ? *LogPawn->GetName() : TEXT("空"));
		return;
	}

	// 如果角色已死亡，设置状态并返回
	if (CachedOwnerCharacter->IsDead()) // 假设 CachedOwnerCharacter 在 CacheComponents 后有效
	{
		// 检查黑板是否有效
		if(IsValid(CachedBlackboardComp))
		{
			CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr); // 清除目标
			CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Dead")); // 设置状态为死亡
			UE_LOG(LogTemp, Verbose, TEXT("检测玩家服务：拥有者 %s 已死亡，设置状态为死亡。"), *CachedOwnerCharacter->GetName());
		}
		// 可以考虑停止行为树，如果死亡逻辑尚未处理
		// OwnerComp.StopTree(EBTStopMode::Safe);
		return;
	}

	// 2. 获取当前状态和目标 (确保使用缓存的 Blackboard)
	FName CurrentStateName = CachedBlackboardComp->GetValueAsName(AIStateKey.SelectedKeyName); // 获取当前 AI 状态标签名
	AActor* CurrentTargetActor = Cast<AActor>(CachedBlackboardComp->GetValueAsObject(TargetActorKey.SelectedKeyName)); // 获取当前目标 Actor
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0); // 获取第一个玩家角色

	// 3. 检查玩家是否存在且有效
	if (!IsValid(PlayerCharacter))
	{
		// 如果没有有效玩家，且当前在追击或攻击状态，则清除目标并切换到 Idle 状态
		if (CurrentStateName == AI_STATE_TAG_NAME("AI.State.Chasing") || CurrentStateName == AI_STATE_TAG_NAME("AI.State.Attacking"))
		{
			CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
			// 可以根据行为类型决定是返回出生点还是待机，这里先设为 Idle
			CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Idle"));
			UE_LOG(LogTemp, Log, TEXT("%s：未找到玩家或玩家无效，进入 Idle 状态。"), *CachedOwnerCharacter->GetName());
		}
		// 如果当前是 Idle, Patrolling, Returning 状态，玩家消失无需改变状态
		return; // 没有玩家可检测，直接返回
	}

	// 4. 主要逻辑：根据当前状态决定行为
	// 获取检测结果
	bool bPlayerInDetectionRange = CachedAiBehaviorComp->IsInDetectionRange(PlayerCharacter); // 是否在侦测范围
	bool bPlayerInChaseRange = CachedAiBehaviorComp->IsInChaseRange(PlayerCharacter);       // 是否在追击范围
	bool bPlayerInAttackRange = CachedAiBehaviorComp->IsInAttackRange(PlayerCharacter);      // 是否在攻击范围
	bool bHasLineOfSightToPlayer = HasLineOfSight(CachedOwnerController, PlayerCharacter); // 是否有视线

	// 组合检测条件，方便使用
	bool bCanSensePlayer = bPlayerInDetectionRange && bHasLineOfSightToPlayer; // 能感知到玩家 (用于开始追击)
	bool bCanEngagePlayer = bPlayerInChaseRange && bHasLineOfSightToPlayer;   // 能与玩家交战 (用于保持追击/攻击)
	bool bCanAttackPlayer = bPlayerInAttackRange && bHasLineOfSightToPlayer;  // 能攻击玩家 (用于切换到攻击)

	// --- 根据当前状态进行逻辑判断和状态切换 ---
	if (CurrentStateName == AI_STATE_TAG_NAME("AI.State.Chasing"))
	{
		// 当前在追击状态
		if (CurrentTargetActor == PlayerCharacter) // 确认目标仍然是玩家
		{
			if (bCanAttackPlayer) // 如果能攻击玩家
			{
				// 切换到攻击状态
				CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Attacking"));
				UE_LOG(LogTemp, Log, TEXT("%s：目标进入攻击范围，切换到攻击状态。"), *CachedOwnerCharacter->GetName());
			}
			else if (!bCanEngagePlayer) // 如果不能交战 (超出追击范围或丢失视线)
			{
				// 目标丢失，切换到返回状态
				FString LostReason = !bPlayerInChaseRange ? TEXT("超出追击范围；") : TEXT("丢失视线；");
				UE_LOG(LogTemp, Log, TEXT("%s：追击时丢失目标 %s。原因：%s 返回出生点。"),
					*CachedOwnerCharacter->GetName(), *PlayerCharacter->GetName(), *LostReason);
				CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr); // 清除目标
				CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Returning"));
			}
			// else: 仍在追击范围内但不在攻击范围内，保持 Chasing 状态，无需操作
		}
		else // 如果目标不再是玩家 (理论上不应发生，除非外部逻辑改变了 TargetActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s：追击时目标意外改变。返回出生点。"), *CachedOwnerCharacter->GetName());
			CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
			CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Returning"));
		}
	}
	else if (CurrentStateName == AI_STATE_TAG_NAME("AI.State.Attacking"))
	{
		// 当前在攻击状态
		if (CurrentTargetActor == PlayerCharacter) // 确认目标仍然是玩家
		{
			if (!bCanAttackPlayer) // 如果不能攻击玩家了
			{
				if (bCanEngagePlayer) // 但仍在交战范围内
				{
					// 切换回追击状态
					CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Chasing"));
					UE_LOG(LogTemp, Log, TEXT("%s：目标离开攻击范围但仍在追击范围，切换回追击状态。"), *CachedOwnerCharacter->GetName());
				}
				else // 连交战范围都出了
				{
					// 目标丢失，切换到返回状态
					FString LostReason = !bPlayerInChaseRange ? TEXT("超出追击范围；") : TEXT("丢失视线；");
					UE_LOG(LogTemp, Log, TEXT("%s：攻击时丢失目标 %s。原因：%s 返回出生点。"),
						*CachedOwnerCharacter->GetName(), *PlayerCharacter->GetName(), *LostReason);
					CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr); // 清除目标
					CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Returning"));
				}
			}
			// else: 仍在攻击范围内，保持 Attacking 状态，由行为树的其他部分决定是否执行攻击动作
		}
		else // 如果目标不再是玩家
		{
			UE_LOG(LogTemp, Warning, TEXT("%s：攻击时目标意外改变。返回出生点。"), *CachedOwnerCharacter->GetName());
			CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
			CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Returning"));
		}
	}
	else // 非追击/攻击状态 (Idle, Patrolling, Returning 等)
	{
		// --- 日志记录：当前状态和检测结果 ---
		bool bPlayerDetected = bCanSensePlayer; // 使用组合条件判断是否检测到玩家
		UE_LOG(LogTemp, Verbose, TEXT("%s：处于非追击状态 (%s)。检测到玩家：%s (侦测范围：%s，视线：%s)"),
			*CachedOwnerCharacter->GetName(),
			*CurrentStateName.ToString(),
			bPlayerDetected ? TEXT("是") : TEXT("否"),
			bPlayerInDetectionRange ? TEXT("是") : TEXT("否"),
			bHasLineOfSightToPlayer ? TEXT("是") : TEXT("否"));
		// ------------------------------------

		if (bPlayerDetected) // 如果能感知到玩家
		{
			// 发现玩家！设置目标并切换到追击状态
			CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, PlayerCharacter);
			CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Chasing"));
			UE_LOG(LogTemp, Log, TEXT("%s：检测到玩家 %s，开始追击！"), *CachedOwnerCharacter->GetName(), *PlayerCharacter->GetName());
		}
		else // 未发现玩家或玩家不在视线/范围内
		{
			// 如果之前有目标 (例如刚从追击/攻击切换过来，但这一帧又丢失了)，则清除目标
			if (CurrentTargetActor != nullptr)
			{
				CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
				UE_LOG(LogTemp, Verbose, TEXT("%s：目标已清除 (之前是 %s)。"), *CachedOwnerCharacter->GetName(), *CurrentTargetActor->GetName());
				// 不需要改变状态，让行为树的其他部分处理 Idle/Patrolling/Returning 逻辑
			}
		}
	}
}

bool UBTService_DetectPlayer::HasLineOfSight(AAIController* OwnerController, const AActor* TargetActor) const
{
	// 检查输入是否有效
	if (!OwnerController || !TargetActor)
	{
		return false;
	}

	// 使用 AIController 内置的视线检查函数
	// 注意：这依赖于 AIController 的 PerceptionComponent 设置（如果使用的话）或默认实现
	bool bHasLoS = OwnerController->LineOfSightTo(TargetActor);

	// --- 可选：添加调试线 ---
	#if ENABLE_DRAW_DEBUG // 只在启用调试绘制时编译
	if (CachedOwnerCharacter) // 确保角色有效
	{
		FVector Start = CachedOwnerCharacter->GetActorLocation(); // 起点为角色位置
		FVector End = TargetActor->GetActorLocation(); // 终点为目标位置
		FColor LineColor = bHasLoS ? FColor::Green : FColor::Red; // 绿色表示有视线，红色表示无
		// 绘制调试线段
		DrawDebugLine(GetWorld(), Start, End, LineColor, false, Interval, 0, 1.0f); // false 表示不持久，Interval 为持续时间
	}
	#endif
	// -----------------------

	return bHasLoS; // 返回视线检查结果

	// --- 备选方案：使用简单的 LineTrace 进行视线检查 ---
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

	// 如果没有命中任何物体，或者命中的是目标 Actor 本身，则认为有视线
	return !bHit || HitResult.GetActor() == TargetActor;
	*/
}
