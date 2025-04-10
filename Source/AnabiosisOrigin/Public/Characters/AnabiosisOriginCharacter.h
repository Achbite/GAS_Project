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

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Data/AnabiosisAttributeData.h"
#include "AnabiosisOriginCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAttributeSet;

/**
 * 游戏主角色类
 * 实现基础移动、视角和能力系统
 */
UCLASS(config=Game)
class AAnabiosisOriginCharacter : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

private:
    /** 相机臂组件：控制相机跟随距离和位置 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraBoom;

    /** 跟随相机：实现第三人称视角 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FollowCamera;

protected:
    /** GAS系统组件 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
    UAbilitySystemComponent* AbilitySystemComponent;

    /** 属性集 */
    UPROPERTY()
    UAttributeSet* AttributeSet;

    /** 攻击能力标签 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
    FGameplayTag AttackAbilityTag;

    /** 默认能力列表 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
    TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

    /** 属性数据表引用 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Class")
    UDataTable* ClassAttributeTable;

    /** 当前角色职业 */
    UPROPERTY(ReplicatedUsing = OnRep_CurrentClass, EditAnywhere, BlueprintReadWrite, Category = "Character|Class")
    EAnabiosisPlayerClass CurrentClass;

public:
    /** 构造函数 */
    AAnabiosisOriginCharacter();

    /** 获取能力系统组件 */
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    /** 获取攻击能力标签 */
    UFUNCTION(BlueprintCallable, Category = "Abilities")
    FGameplayTag GetAttackAbilityTag() const { return AttackAbilityTag; }
    
    /** 设置攻击能力标签 */
    UFUNCTION(BlueprintCallable, Category = "Abilities")
    void SetAttackAbilityTag(const FGameplayTag& NewTag);
    
    /** 获取相机组件 */
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

    /** 设置角色旋转模式 */
    void SetCharacterRotationMode(bool bOrientToMovement, bool bUseControllerRotation);

    /** 设置角色职业 */
    UFUNCTION(BlueprintCallable, Category = "Character|Class")
    void SetPlayerClass(EAnabiosisPlayerClass NewClass);

    /** 获取当前职业 */
    UFUNCTION(BlueprintPure, Category = "Character|Class")
    EAnabiosisPlayerClass GetPlayerClass() const { return CurrentClass; }

    /** 刷新能力输入绑定 */
    UFUNCTION(BlueprintCallable, Category = "Abilities")
    void RefreshAbilityBindings();

protected:
    virtual void BeginPlay() override;
    virtual void PossessedBy(AController* NewController) override;
    virtual void OnRep_PlayerState() override;
    
    /** 初始化默认能力 */
    void GiveDefaultAbilities();

    /** 处理职业变化的网络复制 */
    UFUNCTION()
    void OnRep_CurrentClass();

    /** 更新角色属性为新职业的属性 */
    void UpdateAttributesForClass();
};
