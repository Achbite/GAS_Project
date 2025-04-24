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
* 功能描述： 实现敌人属性集的具体逻辑，包括默认值、属性调整和 Clamp。
*/

#include "Attributes/EnemyAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Data/EnemyAttributeData.h"
#include "AbilitySystemComponent.h"
#include "Characters/EnemyBaseCharacter.h"
#include "GameplayTagsManager.h"

UEnemyAttributeSet::UEnemyAttributeSet()
{
	// 初始化属性默认值
	Health.SetBaseValue(100.0f); Health.SetCurrentValue(100.0f);
	MaxHealth.SetBaseValue(100.0f); MaxHealth.SetCurrentValue(100.0f);
	AttackPower.SetBaseValue(10.0f); AttackPower.SetCurrentValue(10.0f);
	Defense.SetBaseValue(5.0f); Defense.SetCurrentValue(5.0f);
	DetectionRange.SetBaseValue(1000.0f); DetectionRange.SetCurrentValue(1000.0f);
	AggroValue.SetBaseValue(0.0f); AggroValue.SetCurrentValue(0.0f);
}

void UEnemyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// 当 MaxHealth 改变时调整 Health
	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	// Clamp 仇恨值
	// else if (Attribute == GetAggroValueAttribute())
	// {
	//     NewValue = FMath::Max(NewValue, 0.0f);
	// }
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* SourceASC = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	AEnemyBaseCharacter* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get(); // Might be AIController
		TargetCharacter = Cast<AEnemyBaseCharacter>(TargetActor);
	}

	// Clamp Health
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		// 死亡检查通常在 TakeDamage 或 GE 应用后进行
		// if (TargetCharacter && GetHealth() <= 0.0f && !TargetCharacter->IsDead())
		// {
		//     TargetCharacter->HandleDeath();
		// }
	}
	// ... (Clamp other attributes if needed) ...
}

void UEnemyAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
	const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (ASC && !FMath::IsNearlyZero(CurrentMaxValue) && AffectedAttribute.GetCurrentValue() > NewMaxValue)
	{
		ASC->SetNumericAttributeBase(AffectedAttributeProperty, NewMaxValue);
		AffectedAttribute.SetCurrentValue(NewMaxValue);
	}
}

// InitializeFromDataTable 函数已不再直接被 EnemyBaseCharacter 调用，
// 属性初始化现在通过 SetNumericAttributeBase 完成。
// 如果将来需要单独初始化 AttributeSet，可以保留此函数。
// void UEnemyAttributeSet::InitializeFromDataTable(const UDataTable* DataTable, const FName& RowName)
// {
//     // ... (Implementation removed for brevity, as it's currently unused) ...
// }

