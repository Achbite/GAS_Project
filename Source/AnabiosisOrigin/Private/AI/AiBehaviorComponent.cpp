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
		UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::InitializeBehavior: Already initialized."));
		return;
	}

	OwnerEnemy = OwningEnemy;
	OwnerController = Cast<AAIController>(OwnerEnemy->GetController());
	OwnerAttributeSet = OwnerEnemy->GetAttributeSet();
	UAbilitySystemComponent* OwnerASC = OwnerEnemy->GetAbilitySystemComponent();

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
	if (UBlackboardComponent* BBComp = GetBlackboardComponent())
	{
		BBComp->SetValueAsVector(BlackboardKey_HomeLocation, PatrolOrigin);
		// --- 设置 AttackInterval 到 Blackboard ---
		BBComp->SetValueAsFloat(BlackboardKey_AttackInterval, AttackInterval); // 使用 SetValueAsFloat
		// --------------------------------------
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
	if (BehaviorType == EEnemyBehaviorType::Patrol || BehaviorType == EEnemyBehaviorType::Territorial)
	{
		SetAIStateTag(AI_STATE_TAG("AI.State.Patrolling"));
		if (UBlackboardComponent* BBComp = GetBlackboardComponent())
		{
			BBComp->SetValueAsVector(BlackboardKey_PatrolLocation, GetRandomPatrolPoint());
		}
	}
	else
	{
		SetAIStateTag(AI_STATE_TAG("AI.State.Idle"));
	}

	// 更新日志以包含 AttackInterval
	UE_LOG(LogTemp, Log, TEXT("UAiBehaviorComponent initialized for %s. Behavior: %s, Initial State Tag (BB): %s, AttackInterval (BB): %.2f"),
		*OwnerEnemy->GetName(),
		*UEnum::GetValueAsString(BehaviorType),
		*CurrentAIStateTag.ToString(),
		AttackInterval);
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
	// UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::IsInAttackRange not implemented."));
	if (!OwnerEnemy || !TargetActor) return false;
	return FVector::DistSquared(OwnerEnemy->GetActorLocation(), TargetActor->GetActorLocation()) <= AttackRangeSquared;
}

bool UAiBehaviorComponent::IsInChaseRange(const ACharacter* TargetActor) const
{
	// UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::IsInChaseRange not implemented."));
	if (!OwnerEnemy || !TargetActor) return false;
	return FVector::DistSquared(OwnerEnemy->GetActorLocation(), TargetActor->GetActorLocation()) <= ChaseRangeSquared;
}

bool UAiBehaviorComponent::IsInDetectionRange(const ACharacter* TargetActor) const
{
	// UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::IsInDetectionRange not implemented."));
	if (!OwnerEnemy || !TargetActor) return false;
	return FVector::DistSquared(OwnerEnemy->GetActorLocation(), TargetActor->GetActorLocation()) <= DetectionRangeSquared;
}

void UAiBehaviorComponent::SetAIStateTag(const FGameplayTag& NewStateTag)
{
	if (CurrentAIStateTag != NewStateTag)
	{
		CurrentAIStateTag = NewStateTag;

		// 更新 Blackboard 中的状态值
		if (UBlackboardComponent* BBComp = GetBlackboardComponent())
		{
			// --- 改用 SetValueAsName ---
			// 注意：需要在 Blackboard 资源中将 AIState 键的类型从 GameplayTag 改为 Name
			BBComp->SetValueAsName(BlackboardKey_AIState, NewStateTag.GetTagName());
			// ---------------------------
		}
		else if (OwnerController)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAiBehaviorComponent::SetAIStateTag: BlackboardComponent is NULL for %s."), *OwnerEnemy->GetName());
		}
	}
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
