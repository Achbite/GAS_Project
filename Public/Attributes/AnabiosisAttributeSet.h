/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: AnabiosisAttributeSet.h
* 功能描述： 定义玩家角色的属性集 UAnabiosisAttributeSet。
*            包含玩家的核心属性，如基础属性（力量、敏捷等）、资源属性（生命、法力）和战斗属性（攻击、防御、暴击等）。
* 结构：
* - 继承自 UAttributeSet。
* - 使用 FGameplayAttributeData 定义各个属性。
* - 提供宏定义方便属性的访问和设置。
* - 实现属性初始化、调整和 Clamp 逻辑。
*/

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h" // 包含 AbilitySystemComponent.h 以使用宏
#include "AnabiosisAttributeSet.generated.h"

// 使用宏定义属性访问器
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * @brief 玩家角色的属性集。
 */
UCLASS()
class ANABIOSISORIGIN_API UAnabiosisAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	/** 构造函数，设置属性默认值 */
	UAnabiosisAttributeSet();

	// --- 主要属性 ---
	/** 力量 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Primary", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Strength)

	/** 敏捷 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Primary", ReplicatedUsing = OnRep_Agility)
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Agility)

	/** 体质 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Primary", ReplicatedUsing = OnRep_Constitution)
	FGameplayAttributeData Constitution;
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Constitution)

	/** 智力 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Primary", ReplicatedUsing = OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Intelligence)

	// --- 资源属性 ---
	/** 当前生命值 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Health)

	/** 最大生命值 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, MaxHealth)

	/** 当前法力值 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Mana", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Mana)

	/** 最大法力值 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Mana", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, MaxMana)

	// --- 战斗属性 ---
	/** 攻击力 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Combat", ReplicatedUsing = OnRep_AttackPower)
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, AttackPower)

	/** 防御力 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Combat", ReplicatedUsing = OnRep_Defense)
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Defense)

	/** 暴击几率 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Combat", ReplicatedUsing = OnRep_CriticalChance)
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, CriticalChance)

	/** 暴击伤害倍率 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Combat", ReplicatedUsing = OnRep_CriticalMultiplier)
	FGameplayAttributeData CriticalMultiplier;
	ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, CriticalMultiplier)

	// --- 属性修改前的处理 ---
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// --- GameplayEffect 执行后的处理 ---
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// --- 网络复制相关 ---
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// --- 属性复制通知函数 ---
	UFUNCTION()
	virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength);
	UFUNCTION()
	virtual void OnRep_Agility(const FGameplayAttributeData& OldAgility);
	UFUNCTION()
	virtual void OnRep_Constitution(const FGameplayAttributeData& OldConstitution);
	UFUNCTION()
	virtual void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldMana);
	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
	UFUNCTION()
	virtual void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);
	UFUNCTION()
	virtual void OnRep_Defense(const FGameplayAttributeData& OldDefense);
	UFUNCTION()
	virtual void OnRep_CriticalChance(const FGameplayAttributeData& OldCriticalChance);
	UFUNCTION()
	virtual void OnRep_CriticalMultiplier(const FGameplayAttributeData& OldCriticalMultiplier);

	/** 辅助函数，当最大属性值改变时调整受影响的属性值 */
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
};
