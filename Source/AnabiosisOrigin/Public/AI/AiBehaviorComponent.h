/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: AiBehaviorComponent.h
* 功能描述： 定义敌人 AI 行为组件。负责管理敌人的行为模式、状态转换和基本 AI 逻辑（如侦测、追击、攻击）。
*            该组件从 AEnemyBaseCharacter 获取初始化参数。
* 结构：
* - UAiBehaviorComponent：AI 行为组件类。
*   - InitializeBehavior：根据敌人属性数据初始化组件。
*   - GetBlackboardComponent：获取关联的黑板组件。
*   - SetTargetActor：设置当前目标。
*   - IsInAttackRange, IsInChaseRange, IsInDetectionRange：范围检查函数。
*   - 内部引用：缓存指向拥有者、属性集、控制器的指针。
*   - AI 状态：管理当前状态标签和目标。
*   - AI 参数：存储从数据初始化的行为参数（如范围）。
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
	 * @param AttributeData 从数据表加载的属性数据，用于设置侦测范围等参数。
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
	/** 当前 AI 状态标签 (通过 Blackboard 管理，此处可能冗余，待确认) */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|State")
	FGameplayTag CurrentAIStateTag;

	/** 当前追踪的目标 Actor (通过 Blackboard 管理，此处可能冗余，待确认) */
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "AI|Targeting")
	TObjectPtr<ACharacter> CurrentTarget;

	/** 标记组件是否已成功初始化 */
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "AI|State")
	bool bIsInitialized;

	// --- AI 参数 (从 AttributeData 初始化) ---
	/** 敌人的行为模式 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters")
	EEnemyBehaviorType BehaviorType;

	/** 侦测范围的平方，用于距离比较，提高效率 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters")
	float DetectionRangeSquared;

	/** 追击范围的平方，用于距离比较 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters")
	float ChaseRangeSquared; // 新增

	/** 攻击范围的平方，用于距离比较 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters")
	float AttackRangeSquared; // 新增

	/** 巡逻半径 (如果行为是巡逻) */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Parameters")
	float PatrolRadius; // 重命名并添加注释
};
