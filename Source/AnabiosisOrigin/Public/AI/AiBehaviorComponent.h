/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: AiBehaviorComponent.h
* 功能描述： 定义敌人 AI 行为组件。负责管理敌人的行为模式、状态转换和基本 AI 逻辑（如侦测、追击、攻击）。
*            该组件从 AEnemyBaseCharacter 获取初始化参数。
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/EnemyAttributeData.h" // 包含敌人属性数据定义
#include "GameplayTagContainer.h" // 包含 GameplayTag 头文件
#include "AiBehaviorComponent.generated.h"

// 前向声明
class AEnemyBaseCharacter;
class UEnemyAttributeSet;
class ACharacter;
class AAIController; // 使用基类前向声明
class UBlackboardComponent;
class UBehaviorTreeComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANABIOSISORIGIN_API UAiBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAiBehaviorComponent();

	/**
	 * @brief 初始化 AI 行为组件。
	 * @param OwningEnemy 所属的敌人角色。
	 * @param AttributeData 从数据表加载的属性数据。
	 */
	virtual void InitializeBehavior(AEnemyBaseCharacter* OwningEnemy, const FEnemyAttributeData& AttributeData);

	/** 获取 Blackboard 组件 (需要 Controller 有效) */
	UFUNCTION(BlueprintPure, Category = "AI|Blackboard")
	UBlackboardComponent* GetBlackboardComponent() const;

	/** 设置当前目标 Actor (并更新 Blackboard) */
	UFUNCTION(BlueprintCallable, Category = "AI|Targeting")
	void SetTargetActor(ACharacter* NewTarget);

	// --- 公开的 AI 逻辑函数 (范围检查) ---
	/** 检查目标是否在攻击范围内 */
	UFUNCTION(BlueprintPure, Category = "AI|Checks")
	virtual bool IsInAttackRange(const ACharacter* TargetActor) const;

	/** 检查目标是否在追击范围内 */
	UFUNCTION(BlueprintPure, Category = "AI|Checks")
	virtual bool IsInChaseRange(const ACharacter* TargetActor) const;

	/** 检查目标是否在侦测范围内 */
	UFUNCTION(BlueprintPure, Category = "AI|Checks")
	virtual bool IsInDetectionRange(const ACharacter* TargetActor) const;

protected:
	//~ Begin UActorComponent Interface
	virtual void BeginPlay() override;
	//~ End UActorComponent Interface

	// --- 内部引用 ---
	/** 缓存的所属敌人角色指针 */
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "AI|References")
	TObjectPtr<AEnemyBaseCharacter> OwnerEnemy;

	/** 缓存的所属敌人角色的属性集指针 */
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "AI|References")
	TObjectPtr<UEnemyAttributeSet> OwnerAttributeSet;

	/** 缓存的所属敌人角色的 AI 控制器指针 */
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "AI|References")
	TObjectPtr<AAIController> OwnerController;

	// --- AI 状态 ---
	/** 当前 AI 状态标签 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|State")
	FGameplayTag CurrentAIStateTag;

	/** 当前追踪的目标 Actor */
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "AI|Targeting")
	TObjectPtr<ACharacter> CurrentTarget;

	/** 标记组件是否已成功初始化 */
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "AI|State")
	bool bIsInitialized;

	// --- AI 参数 (从 AttributeData 初始化) ---
	/** 敌人的行为模式 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters")
	EEnemyBehaviorType BehaviorType;

	/** 侦测范围的平方，用于距离比较 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters")
	float DetectionRangeSquared;

	/** 巡逻半径 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters")
	float PatrolRadius;

	/** 追击范围的平方，用于距离比较 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters")
	float ChaseRangeSquared;

	/** 攻击范围的平方，用于距离比较 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters")
	float AttackRangeSquared;

	/** 攻击间隔时间 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters")
	float AttackInterval;

	/** 仇恨阈值 (如果使用) */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters")
	float AggroThreshold;

	// --- 内部状态变量 ---
	/** 巡逻的原点/家位置 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Patrol")
	FVector PatrolOrigin;

	/** 下一个巡逻目标点 */
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "AI|Patrol")
	FVector NextPatrolLocation;

	// --- AI 逻辑函数 ---
	/** 设置新的 AI 状态 GameplayTag (并更新 Blackboard) */
	virtual void SetAIStateTag(const FGameplayTag& NewStateTag);

	/** 获取一个随机的巡逻点 */
	virtual FVector GetRandomPatrolPoint() const;

	/** 当所属 Actor 死亡时调用的处理函数 (绑定到 OnDeathDelegate) */
	UFUNCTION()
	virtual void OnOwnerDeath();
};
