/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */
// Copyright Epic Games, Inc. All Rights Reserved.

/*
* 文件名: AnabiosisOriginCharacter.h
* 功能描述： 定义玩家角色的基类 AAnabiosisOriginCharacter。
*            包含玩家的基本组件（相机、能力系统、属性集）、属性加载、状态管理（死亡、职业）和输入处理相关的接口。
* 结构：
* - 继承自 ACharacter 和 IAbilitySystemInterface。
* - 包含相机组件 (CameraBoom, FollowCamera)。
* - 包含 UAbilitySystemComponent 和 UAnabiosisAttributeSet。
* - 提供从数据表加载属性和动画的功能。
* - 定义处理死亡的函数。
* - 暴露状态检查函数（IsDead）。
* - 管理玩家职业和相关的属性更新。
* - 提供设置角色旋转模式和攻击能力标签的接口。
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h" // 包含能力系统接口
#include "GameplayTagContainer.h" // 包含 GameplayTagContainer
#include "AnabiosisOriginTypes.h" // 包含玩家职业枚举
#include "AnabiosisOriginCharacter.generated.h"

// 前向声明
class USpringArmComponent;
class UCameraComponent;
class UAbilitySystemComponent;
class UAnabiosisAttributeSet; // 明确包含属性集
class UDataTable;
class UAnimMontage;
struct FOnAttributeChangeData; // 包含属性变化数据结构

/**
 * @brief 玩家角色的基础类。
 */
UCLASS(config=Game)
class AAnabiosisOriginCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** 相机弹簧臂组件 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** 跟随相机组件 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

public:
	/** 构造函数 */
	AAnabiosisOriginCharacter();

	/** 获取相机弹簧臂 */
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** 获取跟随相机 */
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** 获取能力系统组件 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** 获取属性集 */
	UFUNCTION(BlueprintPure, Category = "Abilities|Attributes")
	UAnabiosisAttributeSet* GetAttributeSet() const;

	/**
	 * @brief 设置玩家职业，并根据新职业更新属性。
	 * @param NewClass 新的玩家职业。
	 */
	UFUNCTION(BlueprintCallable, Category = "Character|Class")
	void SetPlayerClass(EAnabiosisPlayerClass NewClass);

	/**
	 * @brief 获取当前玩家职业。
	 */
	UFUNCTION(BlueprintPure, Category = "Character|Class")
	EAnabiosisPlayerClass GetPlayerClass() const { return CurrentClass; }

	/**
	 * @brief 设置角色的旋转模式。
	 * @param bOrientToMovement 是否将旋转朝向移动方向。
	 * @param bUseControllerRotation 是否使用控制器的 Yaw 旋转。
	 */
	UFUNCTION(BlueprintCallable, Category = "Character|Movement")
	void SetCharacterRotationMode(bool bOrientToMovement, bool bUseControllerRotation);

	/**
	 * @brief 设置当前激活的攻击能力标签。
	 * @param NewTag 新的攻击能力标签。
	 */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void SetAttackAbilityTag(const FGameplayTag& NewTag);

	/**
	 * @brief 获取当前设置的攻击能力标签。
	 */
	UFUNCTION(BlueprintPure, Category = "Abilities")
	FGameplayTag GetAttackAbilityTag() const { return AttackAbilityTag; }

	/**
	 * @brief 刷新能力绑定（可能需要重新审视逻辑）。
	 */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void RefreshAbilityBindings();

	/** 检查角色是否已死亡 */
	UFUNCTION(BlueprintPure, Category = "Character|State")
	bool IsDead() const;

protected:
	/** 组件初始化后调用 */
	virtual void PostInitializeComponents() override;

	/** 从数据表初始化属性和蒙太奇 */
	UFUNCTION(BlueprintCallable, Category = "Character|Initialization")
	virtual void InitializeAttributesFromDataTable();

	/** 游戏开始时调用 */
	virtual void BeginPlay() override;

	/** 当角色被控制器控制时调用 */
	virtual void PossessedBy(AController* NewController) override;

	/** 授予默认能力 */
	virtual void GiveDefaultAbilities();

	/** 根据当前职业更新属性 */
	virtual void UpdateAttributesForClass();

	/** 绑定属性变化监听器 */
	virtual void BindAttributeChangeListeners();

	/** 当生命值属性改变时调用 */
	virtual void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);

	/** 处理角色死亡逻辑 */
	virtual void HandleDeath();

	/** 死亡蒙太奇播放结束时调用 */
	UFUNCTION()
	virtual void OnDeathMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// --- 组件 ---
	/** 能力系统组件 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	/** 属性集 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAttributeSet> AttributeSet; // 使用基类指针，在 C++ 中 Cast

	// --- 数据表和配置 ---
	/** 包含玩家属性的数据表 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Initialization")
	TObjectPtr<UDataTable> AttributeDataTable;

	/** 要从数据表中读取的行名 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Initialization")
	FName AttributeDataRowName;

	/** 默认授予的能力列表 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;

	/** 当前玩家职业 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Class", meta = (AllowPrivateAccess = "true"))
	EAnabiosisPlayerClass CurrentClass;

	/** 当前用于触发攻击的能力标签 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	FGameplayTag AttackAbilityTag;

	// --- 状态和缓存 ---
	/** 缓存的死亡蒙太奇指针 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> LoadedDeathMontage;

	/** 标记角色是否已死亡 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Character|State", meta = (AllowPrivateAccess = "true"))
	bool bIsDead;
};
