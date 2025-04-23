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
* 文件名: AnabiosisAttributeSet.h
* 功能描述： 定义玩家角色的属性集 (AttributeSet)。包含基础属性、状态属性和战斗属性。
*/

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AnabiosisAttributeSet.generated.h"

// 定义属性访问器宏
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ANABIOSISORIGIN_API UAnabiosisAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAnabiosisAttributeSet();

	// --- 基础属性 ---
	UPROPERTY(BlueprintReadOnly, Category = "AttackComponent|Base")
	FGameplayAttributeData Strength; // 力量
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Strength)

	UPROPERTY(BlueprintReadOnly, Category = "AttackComponent|Base")
	FGameplayAttributeData Agility; // 敏捷
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Agility)

	UPROPERTY(BlueprintReadOnly, Category = "AttackComponent|Base")
	FGameplayAttributeData Constitution; // 体质
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Constitution)

	UPROPERTY(BlueprintReadOnly, Category = "AttackComponent|Base")
	FGameplayAttributeData Intelligence; // 智力
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Intelligence)

	// --- 状态属性 ---
	UPROPERTY(BlueprintReadOnly, Category = "AttackComponent|Status")
	FGameplayAttributeData Health; // 当前生命值
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "AttackComponent|Status")
	FGameplayAttributeData MaxHealth; // 最大生命值
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "AttackComponent|Status")
	FGameplayAttributeData Mana; // 当前法力值
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Mana)

	UPROPERTY(BlueprintReadOnly, Category = "AttackComponent|Status")
	FGameplayAttributeData MaxMana; // 最大法力值
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, MaxMana)

	// --- 战斗属性 ---
	UPROPERTY(BlueprintReadOnly, Category = "AttackComponent|Combat")
	FGameplayAttributeData AttackPower; // 攻击力
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category = "AttackComponent|Combat")
	FGameplayAttributeData Defense; // 防御力
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Defense)

	UPROPERTY(BlueprintReadOnly, Category = "AttackComponent|Combat")
	FGameplayAttributeData CriticalChance; // 暴击率
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, CriticalChance)

	UPROPERTY(BlueprintReadOnly, Category = "AttackComponent|Combat")
	FGameplayAttributeData CriticalMultiplier; // 暴击倍率
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, CriticalMultiplier)

	//~ Begin UAttributeSet Interface
	/** 在属性值改变生效前调用，用于 Clamp 或调整 */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	/** 在 GameplayEffect 执行后调用，用于 Clamp 当前值 */
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	//~ End UAttributeSet Interface

protected:
	/** 当最大值属性改变时，调整相关当前值属性 */
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
};

