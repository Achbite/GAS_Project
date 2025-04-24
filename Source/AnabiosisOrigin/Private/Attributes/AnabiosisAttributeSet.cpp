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
* 文件名: AnabiosisAttributeSet.cpp
* 功能描述： 实现玩家属性集 UAnabiosisAttributeSet 的逻辑。
*            负责定义属性的默认值，并在属性变化前后进行 Clamp 或调整。
* 结构：
* - 构造函数：设置各属性的初始基础值和当前值。
* - PreAttributeChange：在属性值被修改前调用，用于 Clamp 或基于最大值调整当前值。
* - PostGameplayEffectExecute：在 GameplayEffect 执行后调用，用于 Clamp 生命值和法力值。
* - AdjustAttributeForMaxChange：辅助函数，当最大值属性变化时，调整关联的当前值属性。
*/

#include "Attributes/AnabiosisAttributeSet.h"
#include "GameplayEffectExtension.h" // 用于 FGameplayEffectModCallbackData
#include "AbilitySystemComponent.h"
#include "Characters/AnabiosisOriginCharacter.h" // 包含角色头文件以备将来使用

UAnabiosisAttributeSet::UAnabiosisAttributeSet()
{
	// 初始化基础属性
	Strength.SetBaseValue(10.0f); Strength.SetCurrentValue(10.0f);
	Agility.SetBaseValue(10.0f); Agility.SetCurrentValue(10.0f);
	Constitution.SetBaseValue(10.0f); Constitution.SetCurrentValue(10.0f);
	Intelligence.SetBaseValue(10.0f); Intelligence.SetCurrentValue(10.0f);

	// 初始化资源属性
	Health.SetBaseValue(100.0f); Health.SetCurrentValue(100.0f);
	MaxHealth.SetBaseValue(100.0f); MaxHealth.SetCurrentValue(100.0f);
	Mana.SetBaseValue(100.0f); Mana.SetCurrentValue(100.0f);
	MaxMana.SetBaseValue(100.0f); MaxMana.SetCurrentValue(100.0f);

	// 初始化战斗属性
	AttackPower.SetBaseValue(10.0f); AttackPower.SetCurrentValue(10.0f);
	Defense.SetBaseValue(5.0f); Defense.SetCurrentValue(5.0f);
	CriticalChance.SetBaseValue(0.05f); CriticalChance.SetCurrentValue(0.05f); // 暴击率 [0, 1]
	CriticalMultiplier.SetBaseValue(1.5f); CriticalMultiplier.SetCurrentValue(1.5f); // 暴击倍率 >= 1
}

void UAnabiosisAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// 在属性值改变生效前进行调整或 Clamp
	if (Attribute == GetMaxHealthAttribute())
	{
		// 当最大生命值改变时，调整当前生命值
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		// 当最大法力值改变时，调整当前法力值
		AdjustAttributeForMaxChange(Mana, MaxMana, NewValue, GetManaAttribute());
	}
	else if (Attribute == GetCriticalChanceAttribute())
	{
		// Clamp 暴击率在 [0, 1] 区间
		NewValue = FMath::Clamp(NewValue, 0.0f, 1.0f);
	}
	else if (Attribute == GetCriticalMultiplierAttribute())
	{
		// Clamp 暴击倍率 >= 1
		NewValue = FMath::Max(NewValue, 1.0f);
	}
	// 可以添加对其他属性的 Clamp 或调整逻辑
}

void UAnabiosisAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// 在 GameplayEffect 执行后进行最终的 Clamp
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Clamp Health 在 [0, MaxHealth] 之间
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		// 死亡检查已移至 Character 的属性变化监听器中处理
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		// Clamp Mana 在 [0, MaxMana] 之间
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
	// 可以添加对其他属性的 Clamp
}

void UAnabiosisAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();

	// 检查 ASC 是否有效，以及当前最大值是否非零（避免除零错误）
	// 如果受影响属性的当前值大于新的最大值，则将其 Clamp 到新的最大值
	if (ASC && !FMath::IsNearlyZero(CurrentMaxValue) && AffectedAttribute.GetCurrentValue() > NewMaxValue)
	{
		// 同时设置基础值和当前值，以确保一致性
		// 注意：这可能需要根据具体设计调整，例如只调整当前值
		ASC->SetNumericAttributeBase(AffectedAttributeProperty, NewMaxValue);
		AffectedAttribute.SetCurrentValue(NewMaxValue);
	}
	// 可选：如果希望在最大值增加时按比例增加当前值，可以在此处添加逻辑
	// else if (ASC && !FMath::IsNearlyZero(CurrentMaxValue) && NewMaxValue > CurrentMaxValue)
	// {
	//     float Percentage = AffectedAttribute.GetCurrentValue() / CurrentMaxValue;
	//     ASC->SetNumericAttributeBase(AffectedAttributeProperty, NewMaxValue * Percentage); // Adjust base value proportionally
	//     AffectedAttribute.SetCurrentValue(NewMaxValue * Percentage); // Adjust current value proportionally
	// }
}
