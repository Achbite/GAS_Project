/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: AnabiosisOriginTypes.h
* 功能描述： 定义项目通用的枚举类型和结构体。
*            包含调试类别枚举 EAnabiosisDebugCategory 和玩家职业枚举 EAnabiosisPlayerClass。
* 结构：
* - 包含全局日志类别的声明。
* - 定义 UENUM 枚举类型。
*/

#pragma once

#include "CoreMinimal.h"
#include "AnabiosisOriginTypes.generated.h" // 需要包含生成的头文件

// 声明项目的全局日志类别
DECLARE_LOG_CATEGORY_EXTERN(LogAnabiosisOrigin, Log, All);

/**
 * @brief 定义调试信息的类别。
 */
UENUM(BlueprintType)
enum class EAnabiosisDebugCategory : uint8
{
	General UMETA(DisplayName = "常规"),
	Combat UMETA(DisplayName = "战斗"),
	AI UMETA(DisplayName = "人工智能"),
	Abilities UMETA(DisplayName = "能力"),
	Attributes UMETA(DisplayName = "属性"),
	All UMETA(DisplayName = "全部") // 特殊值，表示启用所有类别
};

/**
 * @brief 定义玩家的职业。
 */
UENUM(BlueprintType)
enum class EAnabiosisPlayerClass : uint8
{
	Warrior UMETA(DisplayName = "战士"),
	Mage UMETA(DisplayName = "法师"),
	Rogue UMETA(DisplayName = "盗贼")
	// 可以根据需要添加更多职业
};
