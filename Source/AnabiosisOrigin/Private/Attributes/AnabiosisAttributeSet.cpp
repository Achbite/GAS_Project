/* 
 * Copyright (C) 2024 [Wang] 
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
* 文件名: AnabiosisAttributeSet.cpp
* 功能描述： 实现玩家属性集的具体逻辑，包括默认值、属性调整和 Clamp。
*/

#include "Attributes/AnabiosisAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemComponent.h" 

UAnabiosisAttributeSet::UAnabiosisAttributeSet()
{
	// 初始化属性默认值
	Strength.SetBaseValue(10.0f); Strength.SetCurrentValue(10.0f);
	Agility.SetBaseValue(10.0f); Agility.SetCurrentValue(10.0f);
	Constitution.SetBaseValue(10.0f); Constitution.SetCurrentValue(10.0f);
	Intelligence.SetBaseValue(10.0f); Intelligence.SetCurrentValue(10.0f); 

	Health.SetBaseValue(100.0f); Health.SetCurrentValue(100.0f);
	MaxHealth.SetBaseValue(100.0f); MaxHealth.SetCurrentValue(100.0f);
	Mana.SetBaseValue(100.0f); Mana.SetCurrentValue(100.0f);       
	MaxMana.SetBaseValue(100.0f); MaxMana.SetCurrentValue(100.0f); 

	AttackPower.SetBaseValue(10.0f); AttackPower.SetCurrentValue(10.0f);
	Defense.SetBaseValue(5.0f); Defense.SetCurrentValue(5.0f);             
	CriticalChance.SetBaseValue(0.05f); CriticalChance.SetCurrentValue(0.05f); 
	CriticalMultiplier.SetBaseValue(1.5f); CriticalMultiplier.SetCurrentValue(1.5f); 
}

void UAnabiosisAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// 在属性值改变生效前进行调整 (例如，当 MaxHealth 改变时调整 Health)
	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	else if (Attribute == GetMaxManaAttribute()) 
	{
		AdjustAttributeForMaxChange(Mana, MaxMana, NewValue, GetManaAttribute());
	}
	// Clamp 暴击率在 [0, 1] 区间
	else if (Attribute == GetCriticalChanceAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, 1.0f);
	}
	// Clamp 暴击倍率 >= 1
	else if (Attribute == GetCriticalMultiplierAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.0f);
	}
}

void UAnabiosisAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// 在 GameplayEffect 执行后进行 Clamp (确保当前值不超过最大值)
	// 注意：直接通过 TakeDamage 修改属性不会触发此函数
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute()) 
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
}

void UAnabiosisAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	// 如果当前值大于新的最大值，则将当前值调整为新的最大值
	if (ASC && !FMath::IsNearlyZero(CurrentMaxValue) && AffectedAttribute.GetCurrentValue() > NewMaxValue)
	{
		// 同时设置基础值和当前值，以防基础值也需要调整
		// 注意：这可能不是所有情况都期望的行为，取决于你的设计
		ASC->SetNumericAttributeBase(AffectedAttributeProperty, NewMaxValue); 
		AffectedAttribute.SetCurrentValue(NewMaxValue); 
	}
}