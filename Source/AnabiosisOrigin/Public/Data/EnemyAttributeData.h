/* 
 * Copyright (C) 2025 [Wang]
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 3 of the License, or 
 * (at any later version. 
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with this program.  If not, see https://www.gnu.org/licenses/. 
 */

 
/*
* 文件名: EnemyAttributeData.h
* 功能描述： 定义敌人属性数据表 (DataTable) 的行结构 (FEnemyAttributeData)。
*            包含敌人类型、行为、等级、战斗属性、AI 参数、战斗行为和奖励。
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Animation/AnimMontage.h" 
#include "EnemyAttributeData.generated.h"

/**
 * 敌人类型枚举
 */
UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	Normal      UMETA(DisplayName = "普通怪物"),
	Elite       UMETA(DisplayName = "精英怪物"),
	Boss        UMETA(DisplayName = "Boss"),
	MiniBoss    UMETA(DisplayName = "小Boss")
};

/**
 * 敌人行为模式枚举
 */
UENUM(BlueprintType)
enum class EEnemyBehaviorType : uint8
{
	Passive     UMETA(DisplayName = "被动"), // 不会主动攻击，除非受到攻击
	Aggressive  UMETA(DisplayName = "主动"), // 进入侦测范围就会主动攻击
	Territorial UMETA(DisplayName = "领地"), // 在特定区域内主动攻击，离开区域后可能停止追击
	Patrol      UMETA(DisplayName = "巡逻")  // 沿着预定路径移动，并可能具有其他行为模式
};

/**
 * 敌人属性数据行结构
 */
USTRUCT(BlueprintType)
struct FEnemyAttributeData : public FTableRowBase
{
	GENERATED_BODY()

	// --- 基本信息 ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	EEnemyType EnemyType = EEnemyType::Normal; // 敌人类型

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	EEnemyBehaviorType BehaviorType = EEnemyBehaviorType::Passive; // 行为类型

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", meta = (ClampMin = "1"))
	int32 Level = 1; // 等级

	// --- 战斗属性 (通常是初始值或基础值) ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ClampMin = "1.0"))
	float InitialHealth = 100.0f; // 初始生命值

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ClampMin = "1.0"))
	float InitialMaxHealth = 100.0f; // 初始最大生命值

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ClampMin = "0.0"))
	float AttackPower = 10.0f; // 攻击力

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ClampMin = "0.0"))
	float Defense = 5.0f; // 防御力

	// --- AI 行为参数 ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ToolTip = "发现玩家的距离"))
	float DetectionRange = 1000.0f; // 侦测范围

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ToolTip = "巡逻行为的半径 (如果适用)"))
	float PatrolRadius = 500.0f; // 巡逻半径

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ToolTip = "停止追击玩家的最大距离"))
	float ChaseRange = 1500.0f; // 追击范围

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ToolTip = "触发攻击行为所需的仇恨阈值 (如果使用仇恨系统)"))
	float AggroThreshold = 50.0f; // 仇恨阈值

	// --- 战斗行为参数 ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Behavior", meta = (ClampMin = "0.0", ToolTip = "发动攻击的距离"))
	float AttackRange = 150.0f; // 攻击范围

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Behavior", meta = (ClampMin = "0.1", ToolTip = "两次攻击之间的最小间隔时间"))
	float AttackInterval = 2.0f; // 攻击间隔

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Behavior", meta = (ToolTip = "是否可以使用特殊攻击 (需要 AI 逻辑支持)"))
	bool bCanUseSpecialAttack = false; // 是否能使用特殊攻击

	/** 受击时播放的动画蒙太奇 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Behavior")
	TObjectPtr<UAnimMontage> HitReactionMontage; // 受击反应蒙太奇

	/** 死亡时播放的动画蒙太奇 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Behavior")
	TObjectPtr<UAnimMontage> DeathMontage; // 死亡蒙太奇

	// --- 奖励系统 ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards", meta = (ClampMin = "0.0"))
	float ExperienceValue = 10.0f; // 经验值

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float LootChance = 0.5f; // 掉落几率

	FEnemyAttributeData() = default; // 使用默认构造函数
};

