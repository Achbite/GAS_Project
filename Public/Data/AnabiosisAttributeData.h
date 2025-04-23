/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: AnabiosisAttributeData.h
* 功能描述： 定义用于从数据表加载玩家角色属性的数据结构 FAnabiosisAttributeData。
*            包含玩家的基础属性、战斗属性和动画蒙太奇等。
* 结构：
* - 继承自 FTableRowBase，以便用于数据表。
* - 包含各种 UPROPERTY 定义的属性，可在编辑器中编辑数据表。
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AnabiosisAttributeData.generated.h"

// 前向声明
class UAnimMontage;

/**
 * @brief 用于定义玩家角色属性的数据表行结构。
 */
USTRUCT(BlueprintType)
struct FAnabiosisAttributeData : public FTableRowBase
{
	GENERATED_BODY()

public:
	/** 角色等级 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Base")
	int32 Level = 1;

	/** 当前生命值 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Base")
	float Health = 100.0f;

	/** 最大生命值 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Base")
	float MaxHealth = 100.0f;

	/** 当前法力值 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Base")
	float Mana = 100.0f;

	/** 最大法力值 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Base")
	float MaxMana = 100.0f;

	/** 力量 (影响物理攻击等) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Primary")
	float Strength = 10.0f;

	/** 敏捷 (影响攻击速度、闪避等) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Primary")
	float Agility = 10.0f;

	/** 体质 (影响生命值等) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Primary")
	float Constitution = 10.0f;

	/** 智力 (影响法术强度、法力值等) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Primary")
	float Intelligence = 10.0f;

	/** 攻击力 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Combat")
	float AttackPower = 10.0f;

	/** 防御力 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Combat")
	float Defense = 5.0f;

	/** 暴击几率 (0.0 到 1.0) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Combat", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float CriticalChance = 0.05f;

	/** 暴击伤害倍率 (>= 1.0) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Combat", meta = (ClampMin = "1.0"))
	float CriticalMultiplier = 1.5f;

	/** 移动速度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Movement")
	float MovementSpeed = 600.0f;

	/** 死亡动画蒙太奇 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> DeathMontage;

	// 可以根据需要添加更多属性，例如抗性、资源再生率等
};
