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
* 文件名: EnemyAttributeSet.cpp
* 功能描述： 实现敌人属性集的具体逻辑，包括默认值、属性调整和 Clamp。
*/

#include "Attributes/EnemyAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Data/EnemyAttributeData.h"
#include "AbilitySystemComponent.h" 

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

	// 在属性值改变生效前进行调整 (例如，当 MaxHealth 改变时调整 Health)
	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute()); 
	}
	// 可以添加其他属性的 PreChange 逻辑，例如 Clamp 仇恨值
	// else if (Attribute == GetAggroValueAttribute())
	// {
	//     NewValue = FMath::Max(NewValue, 0.0f); 
	// }
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// 在 GameplayEffect 执行后进行 Clamp (确保当前值不超过最大值)
	// 注意：直接通过 TakeDamage 修改属性不会触发此函数
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	// 可以添加其他属性的 PostExecute 逻辑
}

void UEnemyAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, 
	const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	// 如果当前值大于新的最大值，则将当前值调整为新的最大值
	if (ASC && !FMath::IsNearlyZero(CurrentMaxValue) && AffectedAttribute.GetCurrentValue() > NewMaxValue)
	{
		// 同时设置基础值和当前值
		ASC->SetNumericAttributeBase(AffectedAttributeProperty, NewMaxValue);
		AffectedAttribute.SetCurrentValue(NewMaxValue);
	}
}

void UEnemyAttributeSet::InitializeFromDataTable(const UDataTable* DataTable, const FName& RowName)
{
	if (!DataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("InitializeFromDataTable: DataTable is NULL."));
		return;
	}

	const FString ContextString(TEXT("Initializing Enemy Attributes"));
	const FEnemyAttributeData* Row = DataTable->FindRow<FEnemyAttributeData>(RowName, ContextString);
	if (!Row)
	{
		UE_LOG(LogTemp, Error, TEXT("InitializeFromDataTable: Cannot find row '%s' in DataTable '%s'."), *RowName.ToString(), *DataTable->GetName());
		return;
	}

	UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	if (!ASC)
	{
		UE_LOG(LogTemp, Error, TEXT("InitializeFromDataTable: Owning AbilitySystemComponent is NULL."));
		return;
	}

	// --- 设置基础属性 ---
	ASC->SetNumericAttributeBase(GetHealthAttribute(), Row->InitialHealth);
	SetHealth(Row->InitialHealth); 
	ASC->SetNumericAttributeBase(GetMaxHealthAttribute(), Row->InitialMaxHealth);
	SetMaxHealth(Row->InitialMaxHealth); 
	
	// --- 设置战斗属性 ---
	ASC->SetNumericAttributeBase(GetAttackPowerAttribute(), Row->AttackPower);
	SetAttackPower(Row->AttackPower); 
	ASC->SetNumericAttributeBase(GetDefenseAttribute(), Row->Defense);
	SetDefense(Row->Defense); 
	
	// --- AI相关属性设置 ---
	ASC->SetNumericAttributeBase(GetDetectionRangeAttribute(), Row->DetectionRange);
	SetDetectionRange(Row->DetectionRange); 

	// 仇恨值通常从 0 开始
	ASC->SetNumericAttributeBase(GetAggroValueAttribute(), 0.0f); 
	SetAggroValue(0.0f); 

	// 可以移除这个日志，除非调试初始化问题
	// UE_LOG(LogTemp, Log, TEXT("Enemy attributes initialized from DataTable row '%s'."), *RowName.ToString());
}
