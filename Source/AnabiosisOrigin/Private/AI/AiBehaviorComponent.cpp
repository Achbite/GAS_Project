/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: AiBehaviorComponent.cpp
* 功能描述： 实现 UAiBehaviorComponent 的具体逻辑。
*            包括初始化、状态更新、行为判断和执行。
* 结构：
* - 定义黑板键名和 GameplayTag 宏。
* - 构造函数：初始化默认值。
* - BeginPlay：获取拥有者角色。
* - InitializeBehavior：核心初始化函数，从数据表设置参数，设置黑板初始值，绑定死亡委托。
* - SetTargetActor：设置目标并更新黑板。
* - UpdateAIState, CanSeeTarget, FindTargetInRange, Handle...State：占位函数，具体逻辑在行为树或服务中。
* - GetRandomPatrolPoint：获取导航网格上的随机巡逻点。
* - IsInAttackRange, IsInChaseRange, IsInDetectionRange：范围检查函数。
* - CanAttack：检查是否满足攻击条件。
* - TryExecuteMeleeAttack：尝试激活近战攻击能力。
* - SetAIStateTag：设置 AI 状态标签并更新黑板。
* - GetBlackboardComponent：获取黑板组件的辅助函数。
* - OnOwnerDeath：处理拥有者死亡事件，停止行为树，清理状态。
*/

#include "AI/AiBehaviorComponent.h"
#include "Characters/EnemyBaseCharacter.h"
#include "Attributes/EnemyAttributeSet.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationSystem.h" // 包含导航系统
#include "Kismet/GameplayStatics.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h" // 包含 GameplayTag 管理器
#include "BehaviorTree/BlackboardComponent.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "AIController.h" // 确保包含 AI 控制器基类
#include "AI/EnemyAIController.h" // 包含敌人 AI 控制器子类以便 Cast
#include "BehaviorTree/BehaviorTreeComponent.h" // 包含行为树组件
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h" // 确保包含 Float Key 类型
#include "GameFramework/WorldSettings.h" // 包含 WorldSettings 以获取游戏时间

// --- 黑板键名常量 ---
const FName BlackboardKey_AIState = FName("AIState");             // AI 状态键
const FName BlackboardKey_TargetActor = FName("TargetActor");       // 目标 Actor 键
const FName BlackboardKey_PatrolLocation = FName("PatrolLocation"); // 巡逻目标点键
const FName BlackboardKey_HomeLocation = FName("HomeLocation");     // 出生点/家位置键
const FName BlackboardKey_AttackInterval = FName("AttackInterval"); // 攻击间隔键

// --- Gameplay Tag 常量宏 ---
// 通过标签名获取 GameplayTag
#define AI_STATE_TAG(TagName) FGameplayTag::RequestGameplayTag(FName(TagName))

UAiBehaviorComponent::UAiBehaviorComponent()
{
	// 默认禁用 Tick
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	// 初始化指针和默认值
	OwnerEnemy = nullptr;
	OwnerAttributeSet = nullptr;
	CurrentAIStateTag = AI_STATE_TAG("AI.State.Idle"); // 默认状态为 Idle
	CurrentTarget = nullptr;
	BehaviorType = EEnemyBehaviorType::Passive; // 默认行为为被动
	// 初始化范围参数 (平方值用于优化距离比较)
	DetectionRangeSquared = FMath::Square(1000.0f);
	PatrolRadius = 500.0f;
	ChaseRangeSquared = FMath::Square(1500.0f);
	AttackRangeSquared = FMath::Square(150.0f);
	AttackInterval = 2.0f; // 默认攻击间隔
	AggroThreshold = 50.0f;
	bIsInitialized = false; // 初始未初始化
	LastAttackTime = -AttackInterval; // 初始化上次攻击时间，确保第一次可以攻击
	PatrolOrigin = FVector::ZeroVector;
	NextPatrolLocation = FVector::ZeroVector;
	OwnerController = nullptr;
}

void UAiBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();
	// 如果 OwnerEnemy 尚未设置，尝试在 BeginPlay 时获取
	if (!OwnerEnemy)
	{
		OwnerEnemy = Cast<AEnemyBaseCharacter>(GetOwner());
	}
}

void UAiBehaviorComponent::InitializeBehavior(AEnemyBaseCharacter* OwningEnemy, const FEnemyAttributeData& AttributeData)
{
	// 检查传入的 OwningEnemy 是否有效
	if (!OwningEnemy)
	{
		UE_LOG(LogTemp, Error, TEXT("AI行为组件初始化：无效的 OwningEnemy。"));
		return;
	}
	// 防止重复初始化
	if (bIsInitialized)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI行为组件初始化：%s 已初始化。"), *OwningEnemy->GetName());
		return;
	}

	// 缓存拥有者和相关组件
	OwnerEnemy = OwningEnemy;
	OwnerController = Cast<AAIController>(OwnerEnemy->GetController());
	OwnerAttributeSet = OwnerEnemy->GetAttributeSet();
	UAbilitySystemComponent* OwnerASC = OwnerEnemy->GetAbilitySystemComponent();

	// 记录初始化信息
	UE_LOG(LogTemp, Log, TEXT("AI行为组件初始化：%s"), *OwnerEnemy->GetName());
	UE_LOG(LogTemp, Log, TEXT("  - 拥有者控制器：%s"), OwnerController ? *OwnerController->GetName() : TEXT("空"));
	UE_LOG(LogTemp, Log, TEXT("  - 拥有者属性集：%s"), OwnerAttributeSet ? TEXT("有效") : TEXT("空"));
	UE_LOG(LogTemp, Log, TEXT("  - 拥有者 ASC：%s"), OwnerASC ? TEXT("有效") : TEXT("空"));

	// 检查必要的组件是否有效
	AEnemyAIController* SpecificController = Cast<AEnemyAIController>(OwnerController);
	if (!SpecificController)
	{
		// 如果控制器无效或不是预期类型，记录警告
		UE_LOG(LogTemp, Warning, TEXT("AI行为组件初始化：%s 的拥有者控制器为空或不是 AEnemyAIController。行为树可能尚未正常工作。"), *OwnerEnemy->GetName());
	}
	if (!OwnerAttributeSet)
	{
		UE_LOG(LogTemp, Error, TEXT("AI行为组件初始化：%s 的拥有者属性集为空。"), *OwnerEnemy->GetName());
		return; // 属性集是必需的
	}
	if (!OwnerASC)
	{
		UE_LOG(LogTemp, Error, TEXT("AI行为组件初始化：%s 的拥有者能力系统组件为空。"), *OwnerEnemy->GetName());
		return; // ASC 是必需的
	}

	// 从传入的 AttributeData 设置 AI 参数
	BehaviorType = AttributeData.BehaviorType;
	DetectionRangeSquared = FMath::Square(AttributeData.DetectionRange);
	PatrolRadius = AttributeData.PatrolRadius;
	ChaseRangeSquared = FMath::Square(AttributeData.ChaseRange);
	AttackRangeSquared = FMath::Square(AttributeData.AttackRange);
	AttackInterval = AttributeData.AttackInterval;
	AggroThreshold = AttributeData.AggroThreshold;

	// 设置巡逻原点 (HomeLocation) 为当前 Actor 位置
	PatrolOrigin = OwnerEnemy->GetActorLocation();
	NextPatrolLocation = PatrolOrigin; // 初始巡逻目标点设为原点

	// 获取黑板组件并设置初始值
	UBlackboardComponent* BBComp = GetBlackboardComponent();
	UE_LOG(LogTemp, Log, TEXT("  - 尝试获取黑板组件：%s"), BBComp ? TEXT("成功") : TEXT("失败"));
	if (BBComp)
	{
		BBComp->SetValueAsVector(BlackboardKey_HomeLocation, PatrolOrigin); // 设置家位置
		BBComp->SetValueAsFloat(BlackboardKey_AttackInterval, AttackInterval); // 设置攻击间隔
		UE_LOG(LogTemp, Log, TEXT("  - 设置黑板键 '%s' 为 %s"), *BlackboardKey_HomeLocation.ToString(), *PatrolOrigin.ToString());
		UE_LOG(LogTemp, Log, TEXT("  - 设置黑板键 '%s' 为 %.2f"), *BlackboardKey_AttackInterval.ToString(), AttackInterval);
	}

	// 绑定拥有者死亡委托到 OnOwnerDeath 函数
	if (OwnerEnemy)
	{
		OwnerEnemy->OnDeathDelegate.AddDynamic(this, &UAiBehaviorComponent::OnOwnerDeath);
		UE_LOG(LogTemp, Log, TEXT("AI行为组件为 %s 绑定了 OnOwnerDeath 委托。"), *OwnerEnemy->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI行为组件初始化：OwnerEnemy 为空，无法绑定死亡委托。"));
	}

	// 标记为已初始化
	bIsInitialized = true;

	// 根据行为类型设置初始状态并更新黑板
	FGameplayTag InitialStateTag; // 临时变量存储要设置的初始状态标签
	if (BehaviorType == EEnemyBehaviorType::Patrol || BehaviorType == EEnemyBehaviorType::Territorial)
	{
		InitialStateTag = AI_STATE_TAG("AI.State.Patrolling"); // 巡逻或领地型初始为巡逻状态
		if (BBComp) // 再次检查黑板组件
		{
			FVector InitialPatrolPoint = GetRandomPatrolPoint(); // 获取第一个随机巡逻点
			BBComp->SetValueAsVector(BlackboardKey_PatrolLocation, InitialPatrolPoint); // 设置到黑板
			UE_LOG(LogTemp, Log, TEXT("  - 设置黑板键 '%s' 为 %s"), *BlackboardKey_PatrolLocation.ToString(), *InitialPatrolPoint.ToString());
		}
	}
	else // 其他行为类型 (如 Passive, Aggressive) 初始为待机状态
	{
		InitialStateTag = AI_STATE_TAG("AI.State.Idle");
	}
	SetAIStateTag(InitialStateTag); // 设置初始状态标签并更新黑板

	// 记录最终的初始化信息
	UE_LOG(LogTemp, Log, TEXT("AI行为组件为 %s 初始化完成。行为类型：%s，尝试设置的初始状态标签：%s，攻击间隔 (已设置)：%.2f"),
		*OwnerEnemy->GetName(),
		*UEnum::GetValueAsString(BehaviorType), // 获取行为类型枚举的字符串表示
		*InitialStateTag.ToString(), // 显示尝试设置的状态标签
		AttackInterval);
}

void UAiBehaviorComponent::SetTargetActor(ACharacter* NewTarget)
{
	// 只有当目标确实改变时才更新
	if (CurrentTarget != NewTarget)
	{
		CurrentTarget = NewTarget; // 更新缓存的目标
		// 获取黑板组件并设置目标 Actor
		if (UBlackboardComponent* BBComp = GetBlackboardComponent())
		{
			BBComp->SetValueAsObject(BlackboardKey_TargetActor, NewTarget);
			UE_LOG(LogTemp, Log, TEXT("AI行为组件：在黑板中设置 TargetActor 为 %s"), NewTarget ? *NewTarget->GetName() : TEXT("空"));
		}
		else if (OwnerController) // 只有在控制器有效时才记录黑板为空的警告
		{
			UE_LOG(LogTemp, Warning, TEXT("AI行为组件 SetTargetActor：%s 的黑板组件为空。"), *OwnerEnemy->GetName());
		}
	}
}

// --- 以下 Handle...State 函数是占位符，具体逻辑应在行为树或服务中实现 ---
void UAiBehaviorComponent::UpdateAIState(float DeltaTime) {}
bool UAiBehaviorComponent::CanSeeTarget(const ACharacter* TargetActor) const { return false; }
ACharacter* UAiBehaviorComponent::FindTargetInRange() { return nullptr; }
void UAiBehaviorComponent::HandleIdleState(float DeltaTime) {}
void UAiBehaviorComponent::HandlePatrollingState(float DeltaTime) {}
void UAiBehaviorComponent::HandleChasingState(float DeltaTime) {}
void UAiBehaviorComponent::HandleAttackingState(float DeltaTime) {}
void UAiBehaviorComponent::HandleSearchingState(float DeltaTime) {}
void UAiBehaviorComponent::HandleReturningState(float DeltaTime) {}
// --------------------------------------------------------------------

FVector UAiBehaviorComponent::GetRandomPatrolPoint() const
{
	// 检查拥有者是否有效
	if (!OwnerEnemy)
	{
		return FVector::ZeroVector;
	}

	// 获取导航系统
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (NavSys)
	{
		FNavLocation RandomPoint;
		// 在巡逻原点周围的 PatrolRadius 半径内查找随机可导航点
		bool bFound = NavSys->GetRandomPointInNavigableRadius(PatrolOrigin, PatrolRadius, RandomPoint);
		if (bFound)
		{
			return RandomPoint.Location; // 返回找到的点
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AI行为组件 GetRandomPatrolPoint：在 %s 周围的可导航半径内未能找到随机点。"), *PatrolOrigin.ToString());
		}
	}
	// 如果导航系统查找失败，返回一个靠近原点的随机点作为备选
	return PatrolOrigin + FMath::VRand() * PatrolRadius * 0.5f;
}

bool UAiBehaviorComponent::IsInAttackRange(const ACharacter* TargetActor) const
{
	if (!OwnerEnemy || !TargetActor) return false;
	// 使用距离平方进行比较以优化性能
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
	// 检查是否已初始化、拥有者是否有效、是否处于眩晕状态、是否有近战攻击能力
	if (!bIsInitialized || !OwnerEnemy || OwnerEnemy->IsStunned() || !MeleeAttackAbility)
	{
		return false;
	}
	// 检查攻击间隔是否已过
	// 使用 GetWorld()->GetTimeSeconds() 获取当前游戏时间
	return GetWorld() && (GetWorld()->GetTimeSeconds() >= LastAttackTime + AttackInterval);
}

bool UAiBehaviorComponent::TryExecuteMeleeAttack()
{
	// 检查是否满足攻击条件
	if (!CanAttack())
	{
		UE_LOG(LogTemp, Verbose, TEXT("%s 现在无法攻击 (冷却中或眩晕)。"), OwnerEnemy ? *OwnerEnemy->GetName() : TEXT("未知"));
		return false;
	}

	// 获取拥有者的能力系统组件
	UAbilitySystemComponent* OwnerASC = OwnerEnemy ? OwnerEnemy->GetAbilitySystemComponent() : nullptr;
	if (!OwnerASC)
	{
		UE_LOG(LogTemp, Error, TEXT("%s 攻击失败：无法获取 ASC。"), OwnerEnemy ? *OwnerEnemy->GetName() : TEXT("未知"));
		return false;
	}

	// 尝试通过标签激活近战攻击能力
	FGameplayTagContainer AttackAbilityTagContainer;
	AttackAbilityTagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Action.MeleeAttack"))); // 使用预定义的近战攻击标签

	bool bActivated = OwnerASC->TryActivateAbilitiesByTag(AttackAbilityTagContainer);

	if (bActivated)
	{
		LastAttackTime = GetWorld()->GetTimeSeconds(); // 更新上次攻击时间戳
		UE_LOG(LogTemp, Log, TEXT("%s 执行了近战攻击能力。"), *OwnerEnemy->GetName());
		return true; // 激活成功
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s 通过标签激活近战攻击能力失败。"), *OwnerEnemy->GetName());
		// 可能的原因：能力正在冷却、资源不足、被其他标签阻塞等
		return false; // 激活失败
	}
}

void UAiBehaviorComponent::SetAIStateTag(const FGameplayTag& NewStateTag)
{
	// 只有当状态确实改变时才更新
	if (CurrentAIStateTag != NewStateTag)
	{
		CurrentAIStateTag = NewStateTag; // 更新缓存的状态标签

		// 更新 Blackboard 中的状态值
		UBlackboardComponent* BBComp = GetBlackboardComponent();
		// 记录状态切换信息
		UE_LOG(LogTemp, Verbose, TEXT("AI行为组件 SetAIStateTag：%s"), OwnerEnemy ? *OwnerEnemy->GetName() : TEXT("未知"));
		UE_LOG(LogTemp, Verbose, TEXT("  - 新状态标签：%s"), *NewStateTag.ToString());
		UE_LOG(LogTemp, Verbose, TEXT("  - 获取黑板组件：%s"), BBComp ? TEXT("成功") : TEXT("失败"));
		if (BBComp)
		{
			// 将 GameplayTag 的 Name 设置到黑板键
			BBComp->SetValueAsName(BlackboardKey_AIState, NewStateTag.GetTagName());
			UE_LOG(LogTemp, Verbose, TEXT("  - 设置黑板键 '%s' 为 Name：%s"), *BlackboardKey_AIState.ToString(), *NewStateTag.GetTagName().ToString());
		}
		else if (OwnerController) // 只有在控制器有效时才记录黑板为空的警告
		{
			UE_LOG(LogTemp, Warning, TEXT("AI行为组件 SetAIStateTag：%s 的黑板组件为空，尝试设置状态 %s。"), OwnerEnemy ? *OwnerEnemy->GetName() : TEXT("未知"), *NewStateTag.ToString());
		}
	}
	else // 如果状态未改变，也记录日志（可选）
	{
		UE_LOG(LogTemp, Verbose, TEXT("AI行为组件 SetAIStateTag：%s 的状态 %s 已设置。"), OwnerEnemy ? *OwnerEnemy->GetName() : TEXT("未知"), *NewStateTag.ToString());
	}
}

UBlackboardComponent* UAiBehaviorComponent::GetBlackboardComponent() const
{
	// 从缓存的 AI 控制器获取黑板组件
	if (OwnerController)
	{
		return OwnerController->GetBlackboardComponent();
	}
	return nullptr; // 如果控制器无效，返回空
}

void UAiBehaviorComponent::OnOwnerDeath()
{
	// 记录拥有者死亡事件
	UE_LOG(LogTemp, Log, TEXT("AI行为组件：接收到 %s 的死亡通知。"), OwnerEnemy ? *OwnerEnemy->GetName() : TEXT("未知"));
	// 设置状态为死亡
	SetAIStateTag(AI_STATE_TAG("AI.State.Dead"));
	// 禁用组件 Tick (如果之前启用了)
	SetComponentTickEnabled(false);

	// 停止行为树
	if (OwnerController)
	{
		// 获取大脑组件（通常是行为树组件）
		UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(OwnerController->GetBrainComponent());
		if (BTComponent)
		{
			BTComponent->StopTree(EBTStopMode::Safe); // 安全停止行为树
			UE_LOG(LogTemp, Log, TEXT("  %s 的行为树已停止。"), OwnerEnemy ? *OwnerEnemy->GetName() : TEXT("未知"));
		}
	}

	// 清理缓存的引用
	OwnerAttributeSet = nullptr;
	CurrentTarget = nullptr;
	OwnerController = nullptr;
	// OwnerEnemy 指针保留，因为委托可能仍在调用
}
