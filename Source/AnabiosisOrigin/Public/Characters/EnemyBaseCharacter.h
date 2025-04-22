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
* 文件名: EnemyBaseCharacter.h
* 功能描述： AI敌人基类定义。包含 GAS 组件、属性集，并处理属性初始化、能力赋予和伤害接收。
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffect.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataTable.h" // 包含数据表头文件
#include "Attributes/EnemyAttributeSet.h" // 包含 EnemyAttributeSet 的完整头文件
#include "Animation/AnimMontage.h" // Ensure AnimMontage is included
#include "EnemyBaseCharacter.generated.h"

class UAbilitySystemComponent;

UCLASS()
class ANABIOSISORIGIN_API AEnemyBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    AEnemyBaseCharacter();

    //~ Begin IAbilitySystemInterface
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    //~ End IAbilitySystemInterface

    /** 获取从数据表加载的受击蒙太奇 */
    UFUNCTION(BlueprintPure, Category = "Animation")
    UAnimMontage* GetHitReactionMontage() const;

    //~ Begin AActor Interface
    /** 重写 TakeDamage 以便与 GAS 属性交互 */
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
    //~ End AActor Interface

protected:
    //~ Begin AActor Interface
    virtual void PostInitializeComponents() override; 
    virtual void BeginPlay() override;
    virtual void PossessedBy(AController* NewController) override;
    //~ End AActor Interface

    // --- GAS Components ---
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent; // 能力系统组件

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true")) // VisibleDefaultsOnly 可能更合适
    TObjectPtr<UEnemyAttributeSet> AttributeSet; // 敌人属性集

    // --- GAS Initialization ---
    /** 默认赋予的能力列表 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
    TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities; // 默认能力列表

    /** 初始化时应用的 GameplayEffect 列表 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
    TArray<TSubclassOf<UGameplayEffect>> DefaultEffects; // 默认效果列表

    // --- Attribute Data Loading ---
    /** 用于加载敌人属性的数据表 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Attributes")
    TObjectPtr<UDataTable> AttributeDataTable; // 属性数据表

    /** 此敌人在数据表中的行名 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Attributes")
    FName AttributeDataRowName; // 属性数据表行名

    /** 从数据表加载的受击蒙太奇 (用于 GetHitReactionMontage) */
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Config|Animation", meta = (AllowPrivateAccess = "true")) // VisibleInstanceOnly 可能更合适
    TObjectPtr<UAnimMontage> LoadedHitReactionMontage; // 加载的受击反应蒙太奇

    /** 初始化默认能力 */
    virtual void GiveDefaultAbilities();
    
    /** 应用默认效果 */
    virtual void ApplyDefaultEffects();

    /** 从数据表加载并初始化属性 */
    virtual void InitializeAttributesFromDataTable(); 
};
