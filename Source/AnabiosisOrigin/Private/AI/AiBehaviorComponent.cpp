// ... (Copyright comments) ...

/*
* 文件名: AiBehaviorComponent.cpp
* 功能描述： 实现 UAiBehaviorComponent 的具体逻辑，包括初始化、状态更新和行为执行。
*/

#include "AI/AiBehaviorComponent.h"
#include "Characters/EnemyBaseCharacter.h"
#include "Attributes/EnemyAttributeSet.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "AIController.h" // 确保包含基类
#include "AI/EnemyAIController.h" // 包含子类以便 Cast
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h" // 确保包含 Float Key 类型
#include "GameFramework/WorldSettings.h" // Include for GetTimeSeconds

// --- Blackboard Key Names ---
const FName BlackboardKey_AIState = FName("AIState");
const FName BlackboardKey_TargetActor = FName("TargetActor");
const FName BlackboardKey_PatrolLocation = FName("PatrolLocation");
const FName BlackboardKey_HomeLocation = FName("HomeLocation");
const FName BlackboardKey_AttackInterval = FName("AttackInterval"); // 添加 AttackInterval 键名

// --- Gameplay Tag Constants ---
#define AI_STATE_TAG(TagName) FGameplayTag::RequestGameplayTag(FName(TagName))

UAiBehaviorComponent::UAiBehaviorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	// 初始化默认值
	OwnerEnemy = nullptr;
	OwnerAttributeSet = nullptr;
	CurrentAIStateTag = AI_STATE_TAG("AI.State.Idle");
	CurrentTarget = nullptr;
	BehaviorType = EEnemyBehaviorType::Passive;
	DetectionRangeSquared = FMath::Square(1000.0f);
	PatrolRadius = 500.0f;
	ChaseRangeSquared = FMath::Square(1500.0f);
	AttackRangeSquared = FMath::Square(150.0f);
	AttackInterval = 2.0f;
	AggroThreshold = 50.0f;
	bIsInitialized = false;
	LastAttackTime = -AttackInterval;
	PatrolOrigin = FVector::ZeroVector;
	NextPatrolLocation = FVector::ZeroVector;
	OwnerController = nullptr;
}

void UAiBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();
	if (!OwnerEnemy)
	{
		OwnerEnemy = Cast<AEnemyBaseCharacter>(GetOwner());
	}
}

void UAiBehaviorComponent::InitializeBehavior(AEnemyBaseCharacter* OwningEnemy, const FEnemyAttributeData& AttributeData)
{
	// 检查 OwningEnemy 是否有效
	if (!OwningEnemy)
	{
		UE_LOG(LogTemp, Error, TEXT("UAiBehaviorComponent::InitializeBehavior: Invalid OwningEnemy."));
		return;
	}
	if (bIsInitialized)
	{
		UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::InitializeBehavior: Already initialized for %s."), *OwningEnemy->GetName());
		return;
	}

	OwnerEnemy = OwningEnemy;
	OwnerController = Cast<AAIController>(OwnerEnemy->GetController());
	OwnerAttributeSet = OwnerEnemy->GetAttributeSet();
	UAbilitySystemComponent* OwnerASC = OwnerEnemy->GetAbilitySystemComponent();

	// --- 添加日志 ---
	UE_LOG(LogTemp, Log, TEXT("UAiBehaviorComponent::InitializeBehavior for %s:"), *OwnerEnemy->GetName());
	UE_LOG(LogTemp, Log, TEXT("  - OwnerController: %s"), OwnerController ? *OwnerController->GetName() : TEXT("NULL"));
	UE_LOG(LogTemp, Log, TEXT("  - OwnerAttributeSet: %s"), OwnerAttributeSet ? TEXT("Valid") : TEXT("NULL"));
	UE_LOG(LogTemp, Log, TEXT("  - OwnerASC: %s"), OwnerASC ? TEXT("Valid") : TEXT("NULL"));
	// ---------------

	AEnemyAIController* SpecificController = Cast<AEnemyAIController>(OwnerController);
	if (!SpecificController)
	{
		UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::InitializeBehavior: OwnerController is NULL or not AEnemyAIController for %s. Behavior Tree might not function correctly yet."), *OwnerEnemy->GetName());
	}
	if (!OwnerAttributeSet)
	{
		UE_LOG(LogTemp, Error, TEXT("UAiBehaviorComponent::InitializeBehavior: OwnerAttributeSet is NULL for %s."), *OwnerEnemy->GetName());
		return;
	}
	if (!OwnerASC)
	{
		UE_LOG(LogTemp, Error, TEXT("UAiBehaviorComponent::InitializeBehavior: Owner AbilitySystemComponent is NULL for %s."), *OwnerEnemy->GetName());
		return;
	}

	// 从 AttributeData 设置 AI 参数
	BehaviorType = AttributeData.BehaviorType;
	DetectionRangeSquared = FMath::Square(AttributeData.DetectionRange);
	PatrolRadius = AttributeData.PatrolRadius;
	ChaseRangeSquared = FMath::Square(AttributeData.ChaseRange);
	AttackRangeSquared = FMath::Square(AttributeData.AttackRange);
	AttackInterval = AttributeData.AttackInterval;
	AggroThreshold = AttributeData.AggroThreshold;

	// 设置巡逻原点 (HomeLocation) 和 AttackInterval
	PatrolOrigin = OwnerEnemy->GetActorLocation();
	NextPatrolLocation = PatrolOrigin; // 初始巡逻目标

	// --- 添加日志 ---
	UBlackboardComponent* BBComp = GetBlackboardComponent();
	UE_LOG(LogTemp, Log, TEXT("  - Attempting to get BlackboardComponent: %s"), BBComp ? TEXT("Success") : TEXT("Failed"));
	// ---------------
	if (BBComp)
	{
		BBComp->SetValueAsVector(BlackboardKey_HomeLocation, PatrolOrigin);
		BBComp->SetValueAsFloat(BlackboardKey_AttackInterval, AttackInterval); // 使用 SetValueAsFloat
		// --- 添加日志 ---
		UE_LOG(LogTemp, Log, TEXT("  - Set Blackboard Key '%s' to %s"), *BlackboardKey_HomeLocation.ToString(), *PatrolOrigin.ToString());
		UE_LOG(LogTemp, Log, TEXT("  - Set Blackboard Key '%s' to %.2f"), *BlackboardKey_AttackInterval.ToString(), AttackInterval);
		// ---------------
	}

	// --- 绑定主人死亡事件 ---
	if (OwnerEnemy)
	{
		OwnerEnemy->OnDeathDelegate.AddDynamic(this, &UAiBehaviorComponent::OnOwnerDeath);
		UE_LOG(LogTemp, Log, TEXT("UAiBehaviorComponent bound OnOwnerDeath delegate for %s."), *OwnerEnemy->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UAiBehaviorComponent::InitializeBehavior: OwnerEnemy is NULL, cannot bind death delegate."));
	}
	// ------------------------

	bIsInitialized = true;

	// 根据行为类型设置初始状态 (更新 Blackboard)
	FGameplayTag InitialStateTag; // 临时变量存储初始状态
	if (BehaviorType == EEnemyBehaviorType::Patrol || BehaviorType == EEnemyBehaviorType::Territorial)
	{
		InitialStateTag = AI_STATE_TAG("AI.State.Patrolling");
		if (BBComp) // 再次检查 BBComp
		{
			FVector InitialPatrolPoint = GetRandomPatrolPoint();
			BBComp->SetValueAsVector(BlackboardKey_PatrolLocation, InitialPatrolPoint);
			// --- 添加日志 ---
			UE_LOG(LogTemp, Log, TEXT("  - Set Blackboard Key '%s' to %s"), *BlackboardKey_PatrolLocation.ToString(), *InitialPatrolPoint.ToString());
			// ---------------
		}
	}
	else
	{
		InitialStateTag = AI_STATE_TAG("AI.State.Idle");
	}
	SetAIStateTag(InitialStateTag); // 设置初始状态并更新 Blackboard

	// --- 修改日志以显示尝试设置的状态 ---
	UE_LOG(LogTemp, Log, TEXT("UAiBehaviorComponent initialized for %s. Behavior: %s, Attempted Initial State Tag: %s, AttackInterval (Set): %.2f"),
		*OwnerEnemy->GetName(),
		*UEnum::GetValueAsString(BehaviorType),
		*InitialStateTag.ToString(), // 显示尝试设置的状态标签
		AttackInterval);
	// -----------------------------------
}

void UAiBehaviorComponent::SetTargetActor(ACharacter* NewTarget)
{
	if (CurrentTarget != NewTarget)
	{
		CurrentTarget = NewTarget;
		if (UBlackboardComponent* BBComp = GetBlackboardComponent())
		{
			BBComp->SetValueAsObject(BlackboardKey_TargetActor, NewTarget);
			UE_LOG(LogTemp, Log, TEXT("UAiBehaviorComponent: Set TargetActor in Blackboard to %s"), NewTarget ? *NewTarget->GetName() : TEXT("NULL"));
		}
		else if (OwnerController)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::SetTargetActor: BlackboardComponent is NULL for %s."), *OwnerEnemy->GetName());
		}
	}
}

void UAiBehaviorComponent::UpdateAIState(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::UpdateAIState not implemented."));
	// Add state update logic if Tick is enabled
}

bool UAiBehaviorComponent::CanSeeTarget(const ACharacter* TargetActor) const
{
	// UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::CanSeeTarget not implemented."));
	// Add line of sight check logic here
	if (!OwnerEnemy || !TargetActor)
	{
		return false;
	}

	// Simple distance check for now, replace with actual LoS check
	// return FVector::DistSquared(OwnerEnemy->GetActorLocation(), TargetActor->GetActorLocation()) <= DetectionRangeSquared;
	return false; // Placeholder
}

ACharacter* UAiBehaviorComponent::FindTargetInRange()
{
	// UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::FindTargetInRange not implemented."));
	// Add logic to find player or other targets within detection range
	return nullptr; // Placeholder
}

void UAiBehaviorComponent::HandleIdleState(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::HandleIdleState not implemented."));
	// Logic for when AI is idle (e.g., look for targets)
}

void UAiBehaviorComponent::HandlePatrollingState(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::HandlePatrollingState not implemented."));
	// Logic for when AI is patrolling (e.g., move to next point, look for targets)
}

void UAiBehaviorComponent::HandleChasingState(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::HandleChasingState not implemented."));
	// Logic for when AI is chasing a target
}

void UAiBehaviorComponent::HandleAttackingState(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::HandleAttackingState not implemented."));
	// Logic for when AI is attacking
}

void UAiBehaviorComponent::HandleSearchingState(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::HandleSearchingState not implemented."));
	// Logic for when AI is searching for a lost target
}

void UAiBehaviorComponent::HandleReturningState(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::HandleReturningState not implemented."));
	// Logic for when AI is returning to its home location
}

FVector UAiBehaviorComponent::GetRandomPatrolPoint() const
{
	// UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::GetRandomPatrolPoint not fully implemented."));
	if (!OwnerEnemy)
	{
		return FVector::ZeroVector;
	}

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (NavSys)
	{
		FNavLocation RandomPoint;
		// Use PatrolOrigin as the center for finding a random point
		bool bFound = NavSys->GetRandomPointInNavigableRadius(PatrolOrigin, PatrolRadius, RandomPoint);
		if (bFound)
		{
			return RandomPoint.Location;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::GetRandomPatrolPoint: Failed to find random point in navigable radius around %s."), *PatrolOrigin.ToString());
		}
	}
	// Fallback to a point near the origin if NavSys fails
	return PatrolOrigin + FMath::VRand() * PatrolRadius * 0.5f;
}

bool UAiBehaviorComponent::IsInAttackRange(const ACharacter* TargetActor) const
{
	if (!OwnerEnemy || !TargetActor) return false;
	// 使用 AttackRangeSquared 进行比较
	return FVector::DistSquared(OwnerEnemy->GetActorLocation(), TargetActor->GetActorLocation()) <= AttackRangeSquared;
}

bool UAiBehaviorComponent::IsInChaseRange(const ACharacter* TargetActor) const
{
	if (!OwnerEnemy || !TargetActor) return false;
	return FVector::DistSquared(OwnerEnemy->GetActorLocation(), TargetActor->GetActorLocation()) <= ChaseRangeSquared;
}

bool UAiBehaviorComponent::IsInDetectionRange(const ACharacter* TargetActor) const
{
	if (!OwnerEnemy || !TargetActor) return false;
	return FVector::DistSquared(OwnerEnemy->GetActorLocation(), TargetActor->GetActorLocation()) <= DetectionRangeSquared;
}

bool UAiBehaviorComponent::CanAttack() const
{
	// 检查是否初始化、是否眩晕、是否有攻击能力，以及攻击间隔是否已过
	if (!bIsInitialized || !OwnerEnemy || OwnerEnemy->IsStunned() || !MeleeAttackAbility)
	{
		return false;
	}
	// 使用 GetWorld()->GetTimeSeconds() 获取当前游戏时间
	return GetWorld() && (GetWorld()->GetTimeSeconds() >= LastAttackTime + AttackInterval);
}

bool UAiBehaviorComponent::TryExecuteMeleeAttack()
{
	if (!CanAttack())
	{
		UE_LOG(LogTemp, Verbose, TEXT("%s cannot attack now (Cooldown or Stunned)."), OwnerEnemy ? *OwnerEnemy->GetName() : TEXT("Unknown"));
		return false;
	}

	UAbilitySystemComponent* OwnerASC = OwnerEnemy ? OwnerEnemy->GetAbilitySystemComponent() : nullptr;
	if (!OwnerASC)
	{
		UE_LOG(LogTemp, Error, TEXT("%s failed to get ASC for attack."), OwnerEnemy ? *OwnerEnemy->GetName() : TEXT("Unknown"));
		return false;
	}

	// 尝试按 Tag 激活能力
	FGameplayTagContainer AttackAbilityTagContainer;
	AttackAbilityTagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Action.MeleeAttack"))); // 使用我们定义的 Tag

	bool bActivated = OwnerASC->TryActivateAbilitiesByTag(AttackAbilityTagContainer);

	if (bActivated)
	{
		LastAttackTime = GetWorld()->GetTimeSeconds(); // 更新上次攻击时间
		UE_LOG(LogTemp, Log, TEXT("%s executed melee attack ability."), *OwnerEnemy->GetName());
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s failed to activate melee attack ability by tag."), *OwnerEnemy->GetName());
		// 可能是能力正在冷却、资源不足或被其他 Tag 阻塞
		return false;
	}
}

void UAiBehaviorComponent::SetAIStateTag(const FGameplayTag& NewStateTag)
{
	if (CurrentAIStateTag != NewStateTag)
	{
		CurrentAIStateTag = NewStateTag;

		// 更新 Blackboard 中的状态值
		UBlackboardComponent* BBComp = GetBlackboardComponent();
		// --- 添加日志 ---
		UE_LOG(LogTemp, Verbose, TEXT("UAiBehaviorComponent::SetAIStateTag for %s:"), OwnerEnemy ? *OwnerEnemy->GetName() : TEXT("Unknown"));
		UE_LOG(LogTemp, Verbose, TEXT("  - New State Tag: %s"), *NewStateTag.ToString());
		UE_LOG(LogTemp, Verbose, TEXT("  - Getting BlackboardComponent: %s"), BBComp ? TEXT("Success") : TEXT("Failed"));
		// ---------------
		if (BBComp)
		{
			BBComp->SetValueAsName(BlackboardKey_AIState, NewStateTag.GetTagName());
			// --- 添加日志 ---
			UE_LOG(LogTemp, Verbose, TEXT("  - Set Blackboard Key '%s' to Name: %s"), *BlackboardKey_AIState.ToString(), *NewStateTag.GetTagName().ToString());
			// ---------------
		}
		else if (OwnerController) // 只有在 Controller 有效时才记录 Blackboard 为 NULL 的警告
		{
			UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::SetAIStateTag: BlackboardComponent is NULL for %s when trying to set state %s."), OwnerEnemy ? *OwnerEnemy->GetName() : TEXT("Unknown"), *NewStateTag.ToString());
		}
	}
	// --- 添加日志 ---
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("UAiBehaviorComponent::SetAIStateTag for %s: State %s is already set."), OwnerEnemy ? *OwnerEnemy->GetName() : TEXT("Unknown"), *NewStateTag.ToString());
	}
	// ---------------
}

UBlackboardComponent* UAiBehaviorComponent::GetBlackboardComponent() const
{
	if (OwnerController)
	{
		return OwnerController->GetBlackboardComponent();
	}
	return nullptr;
}

void UAiBehaviorComponent::OnOwnerDeath()
{
	UE_LOG(LogTemp, Log, TEXT("UAiBehaviorComponent::OnOwnerDeath received for %s."), OwnerEnemy ? *OwnerEnemy->GetName() : TEXT("Unknown"));
	SetAIStateTag(AI_STATE_TAG("AI.State.Dead"));
	SetComponentTickEnabled(false);

	if (OwnerController)
	{
		UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(OwnerController->GetBrainComponent());
		if (BTComponent)
		{
			BTComponent->StopTree(EBTStopMode::Safe);
			UE_LOG(LogTemp, Log, TEXT("  Behavior Tree stopped for %s."), OwnerEnemy ? *OwnerEnemy->GetName() : TEXT("Unknown"));
		}
	}

	OwnerAttributeSet = nullptr;
	CurrentTarget = nullptr;
	OwnerController = nullptr;
}
