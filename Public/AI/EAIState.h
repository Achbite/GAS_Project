/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: EAIState.h
* 功能描述： 定义 AI 状态的枚举 EAIState 和敌人行为类型的枚举 EEnemyBehaviorType。
*            这些枚举用于管理和区分 AI 的不同状态和行为模式。
* 结构：
* - 定义 UENUM 枚举类型 EAIState，表示 AI 的具体状态。
* - 定义 UENUM 枚举类型 EEnemyBehaviorType，表示 AI 的宏观行为模式。
*/

#pragma once

#include "CoreMinimal.h"
#include "EAIState.generated.h" // 需要包含生成的头文件

/**
 * @brief 定义 AI 的不同状态。
 * @deprecated 推荐使用 GameplayTag (例如 AI.State.Idle) 来管理 AI 状态，此枚举可能不再需要。
 */
UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle UMETA(DisplayName = "待机"),
	Patrolling UMETA(DisplayName = "巡逻"),
	Chasing UMETA(DisplayName = "追击"),
	Attacking UMETA(DisplayName = "攻击"),
	Searching UMETA(DisplayName = "搜索"),
	Returning UMETA(DisplayName = "返回"),
	Dead UMETA(DisplayName = "死亡")
};

/**
 * @brief 定义敌人的行为类型。
 */
UENUM(BlueprintType)
enum class EEnemyBehaviorType : uint8
{
	Passive UMETA(DisplayName = "被动型"),      // 除非受到攻击，否则不会主动攻击
	Aggressive UMETA(DisplayName = "主动攻击型"), // 发现目标后立即攻击
	Patrol UMETA(DisplayName = "巡逻型"),       // 沿路径巡逻，发现目标后攻击
	Territorial UMETA(DisplayName = "领地型")    // 在指定区域内活动，离开区域后可能返回
};
