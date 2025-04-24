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
* 文件名: EnemyAttributeSet.cpp
* 功能描述： 实现敌人属性集 UEnemyAttributeSet 的逻辑。
*            负责定义属性的默认值，并在属性变化前后进行 Clamp 或调整。
* 结构：
* - 构造函数：设置各属性的初始基础值和当前值。
* - PreAttributeChange：在属性值被修改前调用，用于基于最大值调整当前值。
* - PostGameplayEffectExecute：在 GameplayEffect 执行后调用，用于 Clamp 生命值。
* - AdjustAttributeForMaxChange：辅助函数，当最大值属性变化时，调整关联的当前值属性。
*/

#include "Attributes/EnemyAttributeSet.h"
#include "GameplayEffectExtension.h" // 用于 FGameplayEffectModCallbackData
// #include "Data/EnemyAttributeData.h" // 如果 InitializeFromDataTable 不再使用，可以移除
#include "AbilitySystemComponent.h"
#include "Characters/EnemyBaseCharacter.h" // 包含角色头文件以备将来使用
// #include "GameplayTagsManager.h" // 如果不在此处使用 Tag，可以移除

UEnemyAttributeSet::UEnemyAttributeSet()
{
	// 初始化资源和战斗属性
	Health.SetBaseValue(100.0f); Health.SetCurrentValue(100.0f);
	MaxHealth.SetBaseValue(100.0f); MaxHealth.SetCurrentValue(100.0f);
	AttackPower.SetBaseValue(10.0f); AttackPower.SetCurrentValue(10.0f);
	Defense.SetBaseValue(5.0f); Defense.SetCurrentValue(5.0f);

	// 初始化 AI 相关属性 (这些值通常由数据表覆盖)
	DetectionRange.SetBaseValue(1000.0f); DetectionRange.SetCurrentValue(1000.0f);
	AggroValue.SetBaseValue(0.0f); AggroValue.SetCurrentValue(0.0f); // 仇恨值
}

void UEnemyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// 当最大生命值改变时，调整当前生命值
	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	// 可以添加对其他属性的 Clamp 或调整逻辑，例如仇恨值不能为负
	// else if (Attribute == GetAggroValueAttribute())
	// {
	//     NewValue = FMath::Max(NewValue, 0.0f);
	// }
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// 获取效果上下文和相关信息 (如果需要根据来源或标签做不同处理)
	// FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	// UAbilitySystemComponent* SourceASC = Context.GetOriginalInstigatorAbilitySystemComponent();
	// const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	// AActor* TargetActor = nullptr;
	// AController* TargetController = nullptr;
	// AEnemyBaseCharacter* TargetCharacter = nullptr;
	// if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	// {
	// 	TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
	// 	TargetController = Data.Target.AbilityActorInfo->PlayerController.Get(); // 对 AI 来说是 AIController
	// 	TargetCharacter = Cast<AEnemyBaseCharacter>(TargetActor);
	// }

	// 在 GameplayEffect 执行后进行最终的 Clamp
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Clamp Health 在 [0, MaxHealth] 之间
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		// 死亡检查已移至 Character 的 TakeDamage 或属性变化监听器中处理
	}
	// 可以添加对其他属性的 Clamp
}

void UEnemyAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
	const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();

	// 检查 ASC 是否有效，以及当前最大值是否非零
	// 如果受影响属性的当前值大于新的最大值，则将其 Clamp 到新的最大值
	if (ASC && !FMath::IsNearlyZero(CurrentMaxValue) && AffectedAttribute.GetCurrentValue() > NewMaxValue)
	{
		// 同时设置基础值和当前值
		ASC->SetNumericAttributeBase(AffectedAttributeProperty, NewMaxValue);
		AffectedAttribute.SetCurrentValue(NewMaxValue);
	}
	// 可选：按比例调整当前值
}

