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
* 文件名: EnemyBaseCharacter.h
* 功能描述： AI敌人基类定义。包含 GAS 组件、属性集，并处理属性初始化、能力赋予和伤害接收。
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffect.h"
#include "Engine/DataTable.h" // 包含数据表头文件
#include "Attributes/EnemyAttributeSet.h" // 包含 EnemyAttributeSet 的完整头文件
#include "Animation/AnimMontage.h" // Ensure AnimMontage is included
#include "GameplayTagContainer.h" // Include GameplayTagContainer
#include "EnemyBaseCharacter.generated.h"

class UAbilitySystemComponent;
class UAnimMontage; // Forward declare UAnimMontage
class UAiBehaviorComponent; // 前向声明
class AWeaponBase; // Forward declare Weapon Actor
class UDataTable; // Forward declare DataTable

// 声明死亡委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

UCLASS()
class ANABIOSISORIGIN_API AEnemyBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    AEnemyBaseCharacter();

    //~ Begin IAbilitySystemInterface
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    //~ End IAbilitySystemInterface

    /** 获取敌人的属性集 */
    UFUNCTION(BlueprintPure, Category = "AttackComponent|Abilities") // Changed Category
    UEnemyAttributeSet* GetAttributeSet() const; // <--- 添加 Getter

    /** 获取从数据表加载的受击蒙太奇 */
    UFUNCTION(BlueprintPure, Category = "AttackComponent|Animation") // Changed Category
    UAnimMontage* GetHitReactionMontage() const;

    /** 角色死亡时广播的委托 */
    UPROPERTY(BlueprintAssignable, Category = "AttackComponent|State") // Changed Category
    FOnDeathDelegate OnDeathDelegate;

    //~ Begin AActor Interface
    /** 重写 TakeDamage 以便与 GAS 属性交互 */
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
    //~ End AActor Interface

    /** 检查角色是否已死亡 */
    UFUNCTION(BlueprintPure, Category = "AttackComponent|State") // Changed Category
    bool IsDead() const;

    /** 检查角色是否处于受击/眩晕状态 */
    UFUNCTION(BlueprintPure, Category = "AttackComponent|State") // Changed Category
    bool IsStunned() const;

    /** 处理受击事件 (通常由 GE 触发) */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AttackComponent|Combat") // Changed Category
    void HandleHitReaction(AActor* DamageCauser); // 添加伤害来源参数

protected:
    //~ Begin AActor Interface
    virtual void PostInitializeComponents() override; 
    virtual void BeginPlay() override;
    virtual void PossessedBy(AController* NewController) override;
    //~ End AActor Interface

    // --- Weapon ---
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AttackComponent|Weapon", meta = (AllowPrivateAccess = "true")) // Changed Category
    TObjectPtr<AWeaponBase> CurrentWeapon; // 当前装备的武器 Actor

    /** 指向武器属性数据表的指针 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AttackComponent|Config|Weapon") // Changed Category
    TObjectPtr<UDataTable> WeaponAttributeDataTable;

    /** 生成并附加武器 */
    virtual void SpawnAndAttachWeapon(const FName& InWeaponDataRowName, const FName& InAttachSocketName);

    // --- GAS Components ---
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AttackComponent|Abilities", meta = (AllowPrivateAccess = "true")) // Changed Category
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent; // 能力系统组件

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AttackComponent|Abilities", meta = (AllowPrivateAccess = "true")) // Changed Category
    TObjectPtr<UEnemyAttributeSet> AttributeSet; // 敌人属性集

    // --- AI Component --- // <--- 添加 AI 组件部分
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAiBehaviorComponent> AiBehaviorComponent; // AI 行为组件

    // --- GAS Initialization ---
    /** 初始化时应用的 GameplayEffect 列表 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AttackComponent|Abilities") // Changed Category
    TArray<TSubclassOf<UGameplayEffect>> DefaultEffects; // 默认效果列表

    /** 应用于受击时的 GameplayEffect (例如，施加 Stunned 标签) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AttackComponent|Abilities|Combat") // Changed Category
    TSubclassOf<UGameplayEffect> HitReactionEffect; // 受击反应效果

    // --- Attribute Data Loading ---
    /** 用于加载敌人属性的数据表 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AttackComponent|Config|Attributes") // Changed Category
    TObjectPtr<UDataTable> AttributeDataTable; // 属性数据表

    /** 此敌人在数据表中的行名 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AttackComponent|Config|Attributes") // Changed Category
    FName AttributeDataRowName; // 属性数据表行名

    /** 从数据表加载的受击蒙太奇 (用于 GetHitReactionMontage) */
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AttackComponent|Config|Animation", meta = (AllowPrivateAccess = "true")) // Changed Category
    TObjectPtr<UAnimMontage> LoadedHitReactionMontage; // 加载的受击反应蒙太奇

    /** 从数据表加载的死亡蒙太奇 */
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AttackComponent|Config|Animation", meta = (AllowPrivateAccess = "true")) // Changed Category
    TObjectPtr<UAnimMontage> LoadedDeathMontage; // 加载的死亡蒙太奇

    /** 标记角色是否已死亡，防止重复触发死亡逻辑 */
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AttackComponent|State") // Changed Category
    bool bIsDead; // 是否已死亡

    /** 标记属性是否已从数据表初始化 */
    UPROPERTY(Transient, VisibleInstanceOnly, Category = "AttackComponent|State") // Changed Category
    bool bAttributesInitialized; // <--- 添加此行声明

    /** 用于标记角色眩晕/受击状态的 GameplayTag */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AttackComponent|State") // Changed Category
    FGameplayTag StunnedTag; // 眩晕标签

    /** 处理角色死亡逻辑 */
    virtual void HandleDeath();

    /** 死亡蒙太奇播放结束时调用 */
    UFUNCTION() // UFUNCTION is required for delegate binding
    virtual void OnDeathMontageEnded(UAnimMontage* Montage, bool bInterrupted);

    /** 应用默认效果 */
    virtual void ApplyDefaultEffects();

    /** 从数据表加载并初始化属性 */
    virtual void InitializeAttributesFromDataTable(); 
};

