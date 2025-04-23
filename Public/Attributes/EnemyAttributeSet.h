/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: EnemyAttributeSet.h
* 功能描述： 定义敌人的属性集 UEnemyAttributeSet。
*            包含敌人的核心属性，如生命值、攻击力、防御力以及 AI 相关属性。
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
#include "EnemyAttributeSet.generated.h"

// 前向声明
class UDataTable;

// 使用宏定义属性访问器 (Attribute Accessors)
// 这会为每个属性生成 Get<AttributeName>Attribute, Get<AttributeName>, Set<AttributeName> 函数
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * @brief 敌人的属性集，定义了敌人的各种数值属性。
 */
UCLASS()
class ANABIOSISORIGIN_API UEnemyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	/** 构造函数，设置属性默认值 */
	UEnemyAttributeSet();

	// --- 核心战斗属性 ---

	/** 当前生命值 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Health)

	/** 最大生命值 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, MaxHealth)

	/** 攻击力 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Combat", ReplicatedUsing = OnRep_AttackPower)
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, AttackPower)

	/** 防御力 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Combat", ReplicatedUsing = OnRep_Defense)
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Defense)

	// --- AI 相关属性 ---

	/** 侦测范围 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|AI", ReplicatedUsing = OnRep_DetectionRange)
	FGameplayAttributeData DetectionRange;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, DetectionRange)

	/** 当前仇恨值 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|AI", ReplicatedUsing = OnRep_AggroValue)
	FGameplayAttributeData AggroValue;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, AggroValue)

	// --- 属性修改前的处理 ---
	/**
	 * @brief 在属性基础值改变应用之前调用。
	 * @param Attribute 正在改变的属性。
	 * @param NewValue 新的基础值。
	 */
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	/**
	 * @brief 在属性当前值改变应用之前调用。
	 * @param Attribute 正在改变的属性。
	 * @param NewValue 新的当前值。
	 */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// --- GameplayEffect 执行后的处理 ---
	/**
	 * @brief 在 GameplayEffect 执行后调用，用于处理属性修改后的逻辑（如 Clamp）。
	 * @param Data GameplayEffect 修改回调数据。
	 */
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// --- 网络复制相关 ---
	/**
	 * @brief 获取需要复制的属性列表。
	 * @param Props 属性列表数组。
	 */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// --- 从数据表初始化属性 ---
	/**
	 * @brief 使用数据表中的数据初始化属性集。
	 * @param DataTable 包含属性数据的数据表。
	 * @param RowName 数据表中的行名。
	 */
	UFUNCTION(BlueprintCallable, Category = "Attributes|Initialization")
	void InitializeFromDataTable(const UDataTable* DataTable, const FName& RowName);

protected:
	// --- 属性复制通知函数 ---
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION()
	virtual void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);
	UFUNCTION()
	virtual void OnRep_Defense(const FGameplayAttributeData& OldDefense);
	UFUNCTION()
	virtual void OnRep_DetectionRange(const FGameplayAttributeData& OldDetectionRange);
	UFUNCTION()
	virtual void OnRep_AggroValue(const FGameplayAttributeData& OldAggroValue);

	/**
	 * @brief 辅助函数，当最大属性值改变时调整受影响的属性值。
	 * @param AffectedAttribute 受影响的属性数据 (例如 Health)。
	 * @param MaxAttribute 最大属性数据 (例如 MaxHealth)。
	 * @param NewMaxValue 新的最大值。
	 * @param AffectedAttributeProperty 受影响属性的 FGameplayAttribute (例如 GetHealthAttribute())。
	 */
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
};
