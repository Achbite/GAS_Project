/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: AiBehaviorComponent.h
* 功能描述： 定义敌人 AI 行为组件 UAiBehaviorComponent。
*            负责管理敌人的行为模式、状态转换和基本 AI 逻辑（如侦测、追击、攻击范围判断、攻击执行）。
*            该组件从 AEnemyBaseCharacter 获取初始化参数，并与行为树和黑板交互。
* 结构：
* - 继承自 UActorComponent。
* - 缓存拥有者角色、控制器、属性集等引用。
* - 存储 AI 参数（行为类型、各种范围、攻击间隔等）。
* - 提供初始化函数 InitializeBehavior。
* - 提供状态管理函数 SetAIStateTag。
* - 提供目标设置函数 SetTargetActor。
* - 提供行为判断函数（IsInAttackRange, IsInChaseRange, IsInDetectionRange, CanAttack）。
* - 提供行为执行函数 TryExecuteMeleeAttack。
* - 处理拥有者死亡事件 OnOwnerDeath。
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/EnemyAttributeData.h" // 包含敌人属性数据结构
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h" // 包含 GameplayAbility 以便使用 TSubclassOf
#include "AiBehaviorComponent.generated.h"

// 前向声明
class AEnemyBaseCharacter;
class UEnemyAttributeSet;
class ACharacter;
class AAIController; // 使用基类前向声明
class UBlackboardComponent;
class UBehaviorTreeComponent;

/**
 * @brief 敌人 AI 行为组件，管理 AI 的状态和核心逻辑。
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANABIOSISORIGIN_API UAiBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** 构造函数 */
	UAiBehaviorComponent();

	/**
	 * @brief 初始化 AI 行为组件。
	 * @param OwningEnemy 拥有此组件的敌人角色。
	 * @param AttributeData 从数据表加载的属性数据。
	 */
	UFUNCTION(BlueprintCallable, Category = "AI|Initialization")
	void InitializeBehavior(AEnemyBaseCharacter* OwningEnemy, const FEnemyAttributeData& AttributeData);

	/**
	 * @brief 设置当前 AI 状态标签，并更新黑板。
	 * @param NewStateTag 新的状态标签。
	 */
	UFUNCTION(BlueprintCallable, Category = "AI|State")
	void SetAIStateTag(const FGameplayTag& NewStateTag);

	/**
	 * @brief 获取当前的 AI 状态标签。
	 */
	UFUNCTION(BlueprintPure, Category = "AI|State")
	FGameplayTag GetCurrentAIStateTag() const { return CurrentAIStateTag; }

	/**
	 * @brief 设置当前目标 Actor (并更新 Blackboard)。
	 * @param NewTarget 新的目标角色。
	 */
	UFUNCTION(BlueprintCallable, Category = "AI|Targeting")
	void SetTargetActor(ACharacter* NewTarget);

	/**
	 * @brief 获取当前目标 Actor。
	 */
	UFUNCTION(BlueprintPure, Category = "AI|Targeting")
	ACharacter* GetCurrentTarget() const { return CurrentTarget; }

	/**
	 * @brief 尝试执行近战攻击能力。
	 * @return 如果成功激活攻击能力，则返回 true。
	 */
	UFUNCTION(BlueprintCallable, Category = "AI|Actions")
	bool TryExecuteMeleeAttack();

	/**
	 * @brief 检查是否可以执行攻击 (基于冷却时间、眩晕状态等)。
	 * @return 如果可以攻击，则返回 true。
	 */
	UFUNCTION(BlueprintPure, Category = "AI|Checks")
	bool CanAttack() const;

	// --- 公开的 AI 逻辑检查函数 ---

	/**
	 * @brief 检查目标 Actor 是否在攻击范围内。
	 * @param TargetActor 要检查的目标 Actor。
	 * @return 如果在攻击范围内，则返回 true。
	 */
	UFUNCTION(BlueprintPure, Category = "AI|Checks")
	bool IsInAttackRange(const ACharacter* TargetActor) const;

	/**
	 * @brief 检查目标 Actor 是否在追击范围内。
	 * @param TargetActor 要检查的目标 Actor。
	 * @return 如果在追击范围内，则返回 true。
	 */
	UFUNCTION(BlueprintPure, Category = "AI|Checks")
	bool IsInChaseRange(const ACharacter* TargetActor) const;

	/**
	 * @brief 检查目标 Actor 是否在侦测范围内。
	 * @param TargetActor 要检查的目标 Actor。
	 * @return 如果在侦测范围内，则返回 true。
	 */
	UFUNCTION(BlueprintPure, Category = "AI|Checks")
	bool IsInDetectionRange(const ACharacter* TargetActor) const;

	/**
	 * @brief 获取黑板组件。
	 */
	UFUNCTION(BlueprintPure, Category = "AI|Internal")
	UBlackboardComponent* GetBlackboardComponent() const;

protected:
	/** 组件开始运行时调用 */
	virtual void BeginPlay() override;

	// --- 缓存的引用 ---
	/** 拥有此组件的敌人角色 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|References", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AEnemyBaseCharacter> OwnerEnemy;

	/** 拥有者的 AI 控制器 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|References", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AAIController> OwnerController;

	/** 拥有者的属性集 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|References", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<const UEnemyAttributeSet> OwnerAttributeSet; // 使用 const 指针，因为行为组件不应修改属性集

	// --- AI 状态 ---
	/** 当前 AI 状态对应的 GameplayTag */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|State", meta = (AllowPrivateAccess = "true"))
	FGameplayTag CurrentAIStateTag;

	/** 当前锁定的目标 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|State", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACharacter> CurrentTarget;

	/** 用于近战攻击的 Gameplay Ability */
	UPROPERTY(EditDefaultsOnly, Category = "AI|Combat")
	TSubclassOf<UGameplayAbility> MeleeAttackAbility;

	// --- AI 参数 (从 AttributeData 初始化) ---
	/** AI 行为类型 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters", meta = (AllowPrivateAccess = "true"))
	EEnemyBehaviorType BehaviorType;

	/** 侦测范围的平方，用于优化距离计算 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters", meta = (AllowPrivateAccess = "true"))
	float DetectionRangeSquared;

	/** 巡逻半径 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters", meta = (AllowPrivateAccess = "true"))
	float PatrolRadius;

	/** 追击范围的平方 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters", meta = (AllowPrivateAccess = "true"))
	float ChaseRangeSquared;

	/** 攻击范围的平方 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters", meta = (AllowPrivateAccess = "true"))
	float AttackRangeSquared;

	/** 攻击间隔时间 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters", meta = (AllowPrivateAccess = "true"))
	float AttackInterval;

	/** 仇恨阈值 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters", meta = (AllowPrivateAccess = "true"))
	float AggroThreshold;

	// --- 内部状态变量 ---
	/** 组件是否已成功初始化 */
	UPROPERTY(Transient)
	bool bIsInitialized;

	/** 上次攻击的时间戳 */
	UPROPERTY(Transient)
	float LastAttackTime;

	/** 巡逻的中心点 (通常是出生点) */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Internal", meta = (AllowPrivateAccess = "true"))
	FVector PatrolOrigin;

	/** 下一个巡逻目标点 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Internal", meta = (AllowPrivateAccess = "true"))
	FVector NextPatrolLocation;

	// --- AI 逻辑函数 (占位符，具体逻辑在行为树或服务中实现) ---
	/** 更新 AI 状态 (如果启用 Tick) */
	void UpdateAIState(float DeltaTime);
	/** 检查是否能看到目标 */
	bool CanSeeTarget(const ACharacter* TargetActor) const;
	/** 在范围内查找目标 */
	ACharacter* FindTargetInRange();
	/** 处理待机状态 */
	void HandleIdleState(float DeltaTime);
	/** 处理巡逻状态 */
	void HandlePatrollingState(float DeltaTime);
	/** 处理追击状态 */
	void HandleChasingState(float DeltaTime);
	/** 处理攻击状态 */
	void HandleAttackingState(float DeltaTime);
	/** 处理搜索状态 */
	void HandleSearchingState(float DeltaTime);
	/** 处理返回状态 */
	void HandleReturningState(float DeltaTime);
	/** 获取随机巡逻点 */
	FVector GetRandomPatrolPoint() const;

	/** 当拥有者角色死亡时调用 */
	UFUNCTION()
	void OnOwnerDeath();
};
