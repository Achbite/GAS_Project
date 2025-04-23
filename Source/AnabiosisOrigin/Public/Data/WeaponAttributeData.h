/*
 * Copyright (C) 2025 [Wang]
 * ... (Copyleft header) ...
 */

/*
* 文件名: WeaponAttributeData.h
* 功能描述： 定义武器属性数据表 (DataTable) 的行结构 (FWeaponAttributeData)。
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayEffect.h" // Include for TSubclassOf<UGameplayEffect>
#include "UObject/SoftObjectPtr.h" // Include for TSoftClassPtr
#include "GameplayTagContainer.h" // Include for FGameplayTag
#include "WeaponAttributeData.generated.h"

class AWeaponBase; // Forward declaration

USTRUCT(BlueprintType)
struct FWeaponAttributeData : public FTableRowBase
{
	GENERATED_BODY()

	/** 要生成的武器 Actor 类资产的软指针 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackComponent|Equipment|Weapon|Definition") // Refined Category
	TSoftClassPtr<AWeaponBase> WeaponActorClassPtr; // Changed from TSubclassOf

	/** 装备此武器时授予的属性 GameplayEffect (可选) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackComponent|Equipment|Weapon|GrantedAttributes") // Refined Category
	TSubclassOf<UGameplayEffect> GrantedAttributesEffect;

	/** 武器基础攻击力加成 (示例) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackComponent|Equipment|Weapon|GrantedAttributes", meta = (ClampMin = "0.0")) // Refined Category
	float BaseAttackPowerBonus = 0.0f;

	/** 武器暴击率加成 (示例) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackComponent|Equipment|Weapon|GrantedAttributes", meta = (ClampMin = "0.0", ClampMax = "1.0")) // Refined Category
	float CriticalChanceBonus = 0.0f;

	/** 装备此武器时设置给角色的初始攻击能力标签 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackComponent|Equipment|Weapon|Abilities") // New Category
	FGameplayTag InitialAttackTag; // New Property

	// --- 可以添加更多武器特有的属性 ---
	// 例如：攻击速度修正、特殊能力触发效果等

	FWeaponAttributeData() : GrantedAttributesEffect(nullptr), BaseAttackPowerBonus(0.0f), CriticalChanceBonus(0.0f), InitialAttackTag(FGameplayTag::EmptyTag) {} // Initialize new property
};
