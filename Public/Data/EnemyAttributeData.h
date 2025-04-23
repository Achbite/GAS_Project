/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: EnemyAttributeData.h
* 功能描述： 定义用于从数据表加载敌人属性的数据结构 FEnemyAttributeData。
*            包含敌人的基础属性、战斗属性、AI 相关参数以及动画蒙太奇等。
* 结构：
* - 继承自 FTableRowBase，以便用于数据表。
* - 包含各种 UPROPERTY 定义的属性，可在编辑器中编辑数据表。
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h" // 包含 GameplayTagContainer
#include "AI/EAIState.h" // 包含 AI 状态枚举
#include "EnemyAttributeData.generated.h"

// 前向声明
class UAnimMontage;

/**
 * @brief 用于定义敌人属性的数据表行结构。
 */
USTRUCT(BlueprintType)
struct FEnemyAttributeData : public FTableRowBase
{
	GENERATED_BODY()

public:
	/** 敌人等级 (用于可能的缩放或显示) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Base")
	int32 Level = 1;

	/** 初始生命值 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Base")
	float InitialHealth = 100.0f;

	/** 最大生命值 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Base")
	float InitialMaxHealth = 100.0f;

	/** 攻击力 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Combat")
	float AttackPower = 10.0f;

	/** 防御力 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Combat")
	float Defense = 5.0f;

	/** 移动速度 (可选，如果需要从数据表配置) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Movement")
	float MovementSpeed = 300.0f;

	/** 受击反应动画蒙太奇 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> HitReactionMontage;

	/** 死亡动画蒙太奇 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> DeathMontage;

	// --- AI 相关参数 ---

	/** 敌人的行为类型 (例如：被动、巡逻、领地) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Behavior")
	EEnemyBehaviorType BehaviorType = EEnemyBehaviorType::Passive;

	/** 侦测范围 (发现玩家或其他目标的距离) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Ranges")
	float DetectionRange = 1000.0f;

	/** 巡逻半径 (如果行为类型是巡逻) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Ranges", meta = (EditCondition = "BehaviorType == EEnemyBehaviorType::Patrol || BehaviorType == EEnemyBehaviorType::Territorial", EditConditionHides))
	float PatrolRadius = 500.0f;

	/** 追击范围 (超出此范围将停止追击) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Ranges")
	float ChaseRange = 1500.0f;

	/** 攻击范围 (进入此范围可以尝试攻击) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Ranges")
	float AttackRange = 150.0f;

	/** 攻击间隔时间 (两次攻击之间的最小时间) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Combat")
	float AttackInterval = 2.0f;

	/** 仇恨阈值 (达到此仇恨值可能触发特定行为，例如变为主动攻击) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Aggro", meta = (EditCondition = "BehaviorType == EEnemyBehaviorType::Passive", EditConditionHides))
	float AggroThreshold = 50.0f;

	// --- 其他可选配置 ---

	/** 默认授予的能力列表 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;

	/** 初始化时应用的 GameplayEffect 列表 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> DefaultEffects;
};
