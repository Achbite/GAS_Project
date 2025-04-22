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
 * Copyright (C) 2024 [Wang] 
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 3 of the License, or 
 * (at your option) any later version. 
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
* 文件名: AnabiosisAttributeData.h
* 功能描述： 定义玩家属性数据表 (DataTable) 的行结构 (FAnabiosisAttributeData)。
*            包含玩家职业、等级、基础属性、战斗属性及成长相关系数。
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AnabiosisAttributeData.generated.h"

/**
 * 玩家职业枚举
 */
UENUM(BlueprintType)
enum class EAnabiosisPlayerClass : uint8
{
	Warrior     UMETA(DisplayName = "战士"),
	Assassin    UMETA(DisplayName = "刺客"),
	Mage        UMETA(DisplayName = "法师")
};

/**
 * 玩家属性数据行结构
 */
USTRUCT(BlueprintType)
struct FAnabiosisAttributeData : public FTableRowBase
{
	GENERATED_BODY()

	// --- 基本信息 ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	EAnabiosisPlayerClass PlayerClass = EAnabiosisPlayerClass::Warrior; // 玩家职业

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", meta = (ClampMin = "1", ClampMax = "99"))
	int32 Level = 1; // 等级

	// --- 基础属性 ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attributes", meta = (ClampMin = "1"))
	float Strength = 10.0f; // 力量

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attributes", meta = (ClampMin = "1"))
	float Agility = 10.0f; // 敏捷

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attributes", meta = (ClampMin = "1"))
	float Constitution = 10.0f; // 体质

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attributes", meta = (ClampMin = "1"))
	float Intelligence = 10.0f; // 智力

	// --- 战斗属性 (通常是初始值或基础值) ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Attributes", meta = (ClampMin = "0"))
	float Health = 100.0f; // 当前生命值

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Attributes", meta = (ClampMin = "0"))
	float MaxHealth = 100.0f; // 最大生命值

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Attributes", meta = (ClampMin = "0"))
	float Mana = 100.0f; // 当前法力值

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Attributes", meta = (ClampMin = "0"))
	float MaxMana = 100.0f; // 最大法力值

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Attributes", meta = (ClampMin = "0"))
	float AttackPower = 10.0f; // 攻击力

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Attributes", meta = (ClampMin = "0"))
	float Defense = 5.0f; // 防御力

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Attributes", meta = (ClampMin = "0.0", ClampMax = "1.0")) // ClampMax 设为 1.0
	float CriticalChance = 0.05f; // 暴击率

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Attributes", meta = (ClampMin = "1.0")) // 暴击倍率至少为 1
	float CriticalMultiplier = 1.5f; // 暴击倍率

	// --- 衍生属性系数 (可选，如果属性计算在 GE 中处理，则可能不需要) ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Coefficients", meta = (ClampMin = "0"))
	float AttackPowerPerStrength = 2.0f; // 每点力量增加的攻击力

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Coefficients", meta = (ClampMin = "0"))
	float MovementSpeedPerAgility = 0.5f; // 每点敏捷增加的移动速度 (注意：移动速度通常不由 AttributeSet 直接管理)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Coefficients", meta = (ClampMin = "0"))
	float HealthPerConstitution = 10.0f; // 每点体质增加的生命值

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Coefficients", meta = (ClampMin = "0"))
	float ManaPerIntelligence = 10.0f; // 每点智力增加的法力值

	// --- 成长属性 (可选，升级逻辑可以在其他地方处理) ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth", meta = (ClampMin = "1.0"))
	float AttributeGrowthRate = 1.1f; // 基础属性成长率

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth", meta = (ClampMin = "1.0"))
	float HealthGrowthRate = 1.2f; // 生命值成长率

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth", meta = (ClampMin = "1.0"))
	float ManaGrowthRate = 1.15f; // 法力值成长率

	// --- 动画 ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> DeathMontage; // 死亡蒙太奇

	FAnabiosisAttributeData() = default; // 使用默认构造函数
};

