/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: BTService_DetectPlayer.cpp
* 功能描述： 实现行为树服务节点 UBTService_DetectPlayer 的逻辑。
*            周期性地检测玩家，判断距离、视线，并根据当前 AI 状态更新黑板中的目标和状态。
*/

#include "AI/Services/BTService_DetectPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EnemyBaseCharacter.h"
#include "AI/AiBehaviorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"

// --- Gameplay Tag 常量 ---
#define AI_STATE_TAG_NAME(TagName) FName(TagName)

UBTService_DetectPlayer::UBTService_DetectPlayer()
{
	NodeName = "Detect Player Service";
	Interval = 0.5f;
	RandomDeviation = 0.1f;

	TargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_DetectPlayer, TargetActorKey), AActor::StaticClass());
	AIStateKey.AddNameFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_DetectPlayer, AIStateKey));

	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = false;

	CachedAiBehaviorComp = nullptr;
	CachedOwnerCharacter = nullptr;
	CachedOwnerController = nullptr;
	CachedBlackboardComp = nullptr;
}

bool UBTService_DetectPlayer::CacheComponents(UBehaviorTreeComponent& OwnerComp)
{
	if (!IsValid(CachedOwnerController))
	{
		CachedOwnerController = OwnerComp.GetAIOwner();
		if (!IsValid(CachedOwnerController)) return false;
	}
	if (!IsValid(CachedOwnerCharacter))
	{
		CachedOwnerCharacter = Cast<AEnemyBaseCharacter>(CachedOwnerController->GetPawn());
		if (!IsValid(CachedOwnerCharacter)) return false;
	}
	if (!IsValid(CachedAiBehaviorComp))
	{
		if (!IsValid(CachedOwnerCharacter)) return false; // Need character to find component
		CachedAiBehaviorComp = CachedOwnerCharacter->FindComponentByClass<UAiBehaviorComponent>();
		if (!IsValid(CachedAiBehaviorComp)) return false;
	}
	if (!IsValid(CachedBlackboardComp))
	{
		CachedBlackboardComp = OwnerComp.GetBlackboardComponent();
		if (!IsValid(CachedBlackboardComp)) return false;
	}
	return true;
}


void UBTService_DetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Log entry point
	AAIController* ControllerForLog = IsValid(CachedOwnerController) ? CachedOwnerController.Get() : OwnerComp.GetAIOwner();
	APawn* LogPawn = IsValid(CachedOwnerCharacter) ? CachedOwnerCharacter.Get() : (ControllerForLog ? ControllerForLog->GetPawn() : nullptr);
	// UE_LOG(LogTemp, Verbose, TEXT("DetectPlayer Service Tick: Controller: %s, Pawn: %s"), ControllerForLog ? *ControllerForLog->GetName() : TEXT("NULL"), LogPawn ? *LogPawn->GetName() : TEXT("NULL"));

	// 1. Get/Validate Components
	if (!CacheComponents(OwnerComp))
	{
		// UE_LOG(LogTemp, Verbose, TEXT("DetectPlayer Service: Failed to get/cache required components. Controller: %s, Pawn: %s"), ControllerForLog ? *ControllerForLog->GetName() : TEXT("NULL"), LogPawn ? *LogPawn->GetName() : TEXT("NULL"));
		return;
	}

	// Handle dead state
	if (CachedOwnerCharacter->IsDead())
	{
		if(IsValid(CachedBlackboardComp))
		{
			CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
			CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Dead"));
			// UE_LOG(LogTemp, Verbose, TEXT("DetectPlayer Service: Owner %s is dead, setting state to Dead."), *CachedOwnerCharacter->GetName());
		}
		return;
	}

	// 2. Get Current State & Target
	FName CurrentStateName = CachedBlackboardComp->GetValueAsName(AIStateKey.SelectedKeyName);
	AActor* CurrentTargetActor = Cast<AActor>(CachedBlackboardComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// 3. Check Player Validity
	if (!IsValid(PlayerCharacter))
	{
		if (CurrentStateName == AI_STATE_TAG_NAME("AI.State.Chasing") || CurrentStateName == AI_STATE_TAG_NAME("AI.State.Attacking"))
		{
			CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
			CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Idle")); // Or Returning based on logic
			UE_LOG(LogTemp, Log, TEXT("%s: Player not found or invalid, entering Idle state."), *CachedOwnerCharacter->GetName());
		}
		return;
	}

	// 4. Main Logic: Detection & State Transitions
	bool bPlayerInDetectionRange = CachedAiBehaviorComp->IsInDetectionRange(PlayerCharacter);
	bool bPlayerInChaseRange = CachedAiBehaviorComp->IsInChaseRange(PlayerCharacter);
	bool bPlayerInAttackRange = CachedAiBehaviorComp->IsInAttackRange(PlayerCharacter);
	bool bHasLineOfSightToPlayer = HasLineOfSight(CachedOwnerController, PlayerCharacter);

	bool bCanSensePlayer = bPlayerInDetectionRange && bHasLineOfSightToPlayer;
	bool bCanEngagePlayer = bPlayerInChaseRange && bHasLineOfSightToPlayer;
	bool bCanAttackPlayer = bPlayerInAttackRange && bHasLineOfSightToPlayer;

	if (CurrentStateName == AI_STATE_TAG_NAME("AI.State.Chasing"))
	{
		if (CurrentTargetActor == PlayerCharacter)
		{
			if (bCanAttackPlayer)
			{
				CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Attacking"));
				UE_LOG(LogTemp, Log, TEXT("%s: Target entered attack range, switching to Attacking state."), *CachedOwnerCharacter->GetName());
			}
			else if (!bCanEngagePlayer)
			{
				FString LostReason = !bPlayerInChaseRange ? TEXT("out of chase range;") : TEXT("lost line of sight;");
				UE_LOG(LogTemp, Log, TEXT("%s: Lost target %s while chasing. Reason: %s Returning home."),
					*CachedOwnerCharacter->GetName(), *PlayerCharacter->GetName(), *LostReason);
				CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
				CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Returning"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: Target changed unexpectedly while chasing. Returning home."), *CachedOwnerCharacter->GetName());
			CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
			CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Returning"));
		}
	}
	else if (CurrentStateName == AI_STATE_TAG_NAME("AI.State.Attacking"))
	{
		if (CurrentTargetActor == PlayerCharacter)
		{
			if (!bCanAttackPlayer)
			{
				if (bCanEngagePlayer)
				{
					CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Chasing"));
					UE_LOG(LogTemp, Log, TEXT("%s: Target left attack range but still in chase range, switching back to Chasing state."), *CachedOwnerCharacter->GetName());
				}
				else
				{
					FString LostReason = !bPlayerInChaseRange ? TEXT("out of chase range;") : TEXT("lost line of sight;");
					UE_LOG(LogTemp, Log, TEXT("%s: Lost target %s while attacking. Reason: %s Returning home."),
						*CachedOwnerCharacter->GetName(), *PlayerCharacter->GetName(), *LostReason);
					CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
					CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Returning"));
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: Target changed unexpectedly while attacking. Returning home."), *CachedOwnerCharacter->GetName());
			CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
			CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Returning"));
		}
	}
	else // Idle, Patrolling, Returning, etc.
	{
		// UE_LOG(LogTemp, Verbose, TEXT("%s: In non-chasing state (%s). Player detected: %s (Range: %s, LoS: %s)"),
		// 	*CachedOwnerCharacter->GetName(),
		// 	*CurrentStateName.ToString(),
		// 	bCanSensePlayer ? TEXT("Yes") : TEXT("No"),
		// 	bPlayerInDetectionRange ? TEXT("Yes") : TEXT("No"),
		// 	bHasLineOfSightToPlayer ? TEXT("Yes") : TEXT("No"));

		if (bCanSensePlayer)
		{
			CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, PlayerCharacter);
			CachedBlackboardComp->SetValueAsName(AIStateKey.SelectedKeyName, AI_STATE_TAG_NAME("AI.State.Chasing"));
			UE_LOG(LogTemp, Log, TEXT("%s: Detected player %s, starting chase!"), *CachedOwnerCharacter->GetName(), *PlayerCharacter->GetName());
		}
		else
		{
			if (CurrentTargetActor != nullptr) // Clear target if we were previously targeting something but lost detection
			{
				CachedBlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
				// UE_LOG(LogTemp, Verbose, TEXT("%s: Target cleared (was %s)."), *CachedOwnerCharacter->GetName(), *CurrentTargetActor->GetName());
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

	bool bHasLoS = OwnerController->LineOfSightTo(TargetActor);

	#if ENABLE_DRAW_DEBUG
	if (CachedOwnerCharacter)
	{
		FVector Start = CachedOwnerCharacter->GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		FColor LineColor = bHasLoS ? FColor::Green : FColor::Red;
		DrawDebugLine(GetWorld(), Start, End, LineColor, false, Interval, 0, 1.0f);
	}
	#endif

	return bHasLoS;
}
