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
* 文件名: AnabiosisOriginCharacter.h
* 功能描述： 游戏主角色类定义。包含相机、GAS 组件、属性集，并处理输入、职业切换和属性加载。
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataTable.h"
#include "Data/AnabiosisAttributeData.h"
#include "Animation/AnimMontage.h"
#include "AnabiosisOriginCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAttributeSet;
class UAbilitySystemComponent;
class UAnimMontage;
class AWeaponBase; // 前向声明武器 Actor
class UDataTable; // 前向声明数据表

UCLASS(config=Game)
class AAnabiosisOriginCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

private:
	/** 相机臂组件 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom; // 相机臂

	/** 跟随相机 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera; // 跟随相机

protected:
    // --- 武器 ---
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AttackComponent|Weapon", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<AWeaponBase> CurrentWeapon; // 当前装备的武器 Actor

    /** 指向武器属性数据表的指针 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AttackComponent|Config|Weapon")
    TObjectPtr<UDataTable> WeaponAttributeDataTable; // 武器属性数据表

    /** 生成并附加武器 */
    virtual void SpawnAndAttachWeapon(const FName& InWeaponDataRowName, const FName& InAttachSocketName);

	// --- GAS 组件 ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AttackComponent|Abilities", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent; // 能力系统组件

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AttackComponent|Abilities", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAttributeSet> AttributeSet; // 属性集 (基类指针)

	// --- GAS 初始化与状态 ---
	/** 攻击能力标签 (用于触发特定攻击能力) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackComponent|Abilities")
	FGameplayTag AttackAbilityTag; // 攻击能力标签

	/** 默认赋予的能力列表 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AttackComponent|Abilities") // BlueprintReadOnly 允许在蓝图中读取, EditDefaultsOnly 允许在蓝图默认值中设置
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities; // 默认能力列表

	// --- 属性数据加载 ---
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AttackComponent|Config|Attributes")
	TObjectPtr<UDataTable> AttributeDataTable; // 属性数据表

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AttackComponent|Config|Attributes")
	FName AttributeDataRowName; // 属性数据表行名

	// --- 角色状态 ---
	/** 当前角色职业 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Class")
	EAnabiosisPlayerClass CurrentClass; // 当前职业

	/** 受击时播放的动画蒙太奇 (从数据表加载) */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AttackComponent|Animation", meta = (AllowPrivateAccess = "true")) // 从 EditDefaultsOnly 更改
	TObjectPtr<UAnimMontage> HitReactionMontage; // 受击反应蒙太奇

	/** 从数据表加载的死亡蒙太奇 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AttackComponent|Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> LoadedDeathMontage; // 加载的死亡蒙太奇

	/** 标记角色是否已死亡，防止重复触发死亡逻辑 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AttackComponent|State")
	bool bIsDead; // 是否已死亡

public:
	AAnabiosisOriginCharacter();

	//~ Begin IAbilitySystemInterface (能力系统接口开始)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface (能力系统接口结束)

	// --- Getters (获取器) ---
	UFUNCTION(BlueprintCallable, Category = "AttackComponent|Abilities")
	FGameplayTag GetAttackAbilityTag() const { return AttackAbilityTag; } // 获取攻击能力标签
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; } // 获取相机臂
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; } // 获取跟随相机

	UFUNCTION(BlueprintPure, Category = "Character|Class")
	EAnabiosisPlayerClass GetPlayerClass() const { return CurrentClass; } // 获取玩家职业

	/** 检查角色是否已死亡 */
	UFUNCTION(BlueprintPure, Category = "AttackComponent|State")
	bool IsDead() const;

	/** 返回角色的受击反应蒙太奇 */
	UFUNCTION(BlueprintCallable, Category = "AttackComponent|Animation")
	virtual UAnimMontage* GetHitReactionMontage() const { return HitReactionMontage; }

	// --- Setters & Modifiers (设置器与修改器) ---
	UFUNCTION(BlueprintCallable, Category = "AttackComponent|Abilities")
	void SetAttackAbilityTag(const FGameplayTag& NewTag); // 设置攻击能力标签
	
	/** 设置角色旋转模式 (是否朝向移动方向，是否使用控制器 Yaw 旋转) */
	void SetCharacterRotationMode(bool bOrientToMovement, bool bUseControllerRotation);

	/** 设置角色职业 (仅服务端有效) */
	UFUNCTION(BlueprintCallable, Category = "Character|Class")
	void SetPlayerClass(EAnabiosisPlayerClass NewClass);

	/** 刷新能力输入绑定 (可能需要审查逻辑) */
	UFUNCTION(BlueprintCallable, Category = "AttackComponent|Abilities")
	void RefreshAbilityBindings();

	/** 处理角色死亡逻辑 (公开，以便 AttributeSet 可以调用) */
	virtual void HandleDeath();

protected:
	//~ Begin AActor Interface (AActor 接口开始)
	virtual void PostInitializeComponents() override; // 组件初始化后调用
	virtual void BeginPlay() override; // 游戏开始时调用
	virtual void PossessedBy(AController* NewController) override; // 被控制器控制时调用
	//~ End AActor Interface (AActor 接口结束)
	
	/** 初始化默认能力 (仅服务端) */
	virtual void GiveDefaultAbilities();

	/** 根据当前职业更新属性 (仅服务端) */
	virtual void UpdateAttributesForClass(); 

	/** 从数据表加载并初始化属性 (仅服务端) */
	virtual void InitializeAttributesFromDataTable(); 

	/** 死亡蒙太奇播放结束时调用 */
	UFUNCTION() // UFUNCTION 宏是委托绑定所必需的
	virtual void OnDeathMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	/** 监听生命值变化的回调 */
	virtual void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);

	/** 绑定属性变化监听器 */
	void BindAttributeChangeListeners();
};

