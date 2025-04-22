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
* 文件名: EnemyAttributeSet.h
* 功能描述： 定义敌人 AI 角色的属性集 (AttributeSet)。包含战斗属性和 AI 相关属性。
*/

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EnemyAttributeSet.generated.h"

// 定义属性访问器宏
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ANABIOSISORIGIN_API UEnemyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UEnemyAttributeSet();

	// --- 基础/状态属性 ---
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Base")
	FGameplayAttributeData Health; // 当前生命值
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Base")
	FGameplayAttributeData MaxHealth; // 最大生命值
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, MaxHealth)

	// --- 战斗属性 ---
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Combat")
	FGameplayAttributeData AttackPower; // 攻击力
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Combat")
	FGameplayAttributeData Defense; // 防御力
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Defense)

	// --- AI 相关属性 ---
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|AI")
	FGameplayAttributeData DetectionRange; // 侦测范围
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, DetectionRange)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|AI")
	FGameplayAttributeData AggroValue; // 仇恨值
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, AggroValue)

	//~ Begin UAttributeSet Interface
	/** 在属性值改变生效前调用，用于 Clamp 或调整 */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	/** 在 GameplayEffect 执行后调用，用于 Clamp 当前值 */
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	//~ End UAttributeSet Interface

	/** 从数据表初始化属性值 */
	void InitializeFromDataTable(const UDataTable* DataTable, const FName& RowName);

protected:
	/** 当最大值属性改变时，调整相关当前值属性 */
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
};

