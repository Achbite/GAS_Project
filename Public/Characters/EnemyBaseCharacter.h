/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: EnemyBaseCharacter.h
* 功能描述： 定义 AI 敌人角色的基类 AEnemyBaseCharacter。
*            包含敌人的基本组件（能力系统、属性集、AI 行为组件）、属性加载、状态管理（死亡、眩晕）和事件处理（受击、死亡）。
* 结构：
* - 继承自 ACharacter 和 IAbilitySystemInterface。
* - 包含 UAbilitySystemComponent 和 UEnemyAttributeSet。
* - 包含 UAiBehaviorComponent 用于 AI 逻辑。
* - 提供从数据表加载属性和动画的功能。
* - 定义处理死亡和受击反应的函数。
* - 暴露状态检查函数（IsDead, IsStunned）。
* - 定义死亡委托 OnDeathDelegate。
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h" // 包含能力系统接口
#include "GameplayTagContainer.h" // 包含 GameplayTagContainer
#include "EnemyBaseCharacter.generated.h"

// 前向声明
class UAbilitySystemComponent;
class UEnemyAttributeSet;
class UDataTable;
class UAnimMontage;
class UGameplayEffect;
class UAiBehaviorComponent; // 添加 AI 行为组件的前向声明

// 声明死亡委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDeathDelegate);

/**
 * @brief AI 敌人的基础角色类。
 */
UCLASS()
class ANABIOSISORIGIN_API AEnemyBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	/** 构造函数 */
	AEnemyBaseCharacter();

	/** 获取能力系统组件 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** 获取属性集 */
	UFUNCTION(BlueprintPure, Category = "Abilities|Attributes")
	UEnemyAttributeSet* GetAttributeSet() const;

	/** 获取受击反应蒙太奇 */
	UFUNCTION(BlueprintPure, Category = "Animation")
	UAnimMontage* GetHitReactionMontage() const;

	/** 检查角色是否已死亡 */
	UFUNCTION(BlueprintPure, Category = "Character|State")
	bool IsDead() const;

	/** 检查角色是否处于受击/眩晕状态 */
	UFUNCTION(BlueprintPure, Category = "Character|State")
	bool IsStunned() const;

	/** 处理受击事件 (通常由 GE 或 GameplayEvent 触发) */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character|Combat")
	void HandleHitReaction(AActor* DamageCauser); // 添加伤害来源参数

	/** 当角色死亡时广播 */
	UPROPERTY(BlueprintAssignable, Category = "Character|Event")
	FOnEnemyDeathDelegate OnDeathDelegate;

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

	/** 处理角色受到伤害 */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	/** 处理角色死亡逻辑 */
	virtual void HandleDeath();

	/** 死亡蒙太奇播放结束时调用 */
	UFUNCTION()
	virtual void OnDeathMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	/** 授予默认能力 */
	virtual void GiveDefaultAbilities();

	/** 应用默认效果 */
	virtual void ApplyDefaultEffects();

	// --- 组件 ---
	/** 能力系统组件 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	/** 属性集 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnemyAttributeSet> AttributeSet;

	/** AI 行为组件 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAiBehaviorComponent> AiBehaviorComponent;

	// --- 数据表和配置 ---
	/** 包含敌人属性的数据表 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Initialization")
	TObjectPtr<UDataTable> AttributeDataTable;

	/** 要从数据表中读取的行名 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Initialization")
	FName AttributeDataRowName;

	/** 默认授予的能力列表 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;

	/** 初始化时应用的 GameplayEffect 列表 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;

	/** 应用于受击时的 GameplayEffect (例如，施加 Stunned 标签) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Combat")
	TSubclassOf<UGameplayEffect> HitReactionEffect;

	// --- 状态和缓存 ---
	/** 缓存的受击反应蒙太奇指针 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> LoadedHitReactionMontage;

	/** 缓存的死亡蒙太奇指针 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> LoadedDeathMontage;

	/** 标记角色是否已死亡，防止重复触发死亡逻辑 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Character|State", meta = (AllowPrivateAccess = "true"))
	bool bIsDead;

	/** 标记属性是否已从数据表初始化 */
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Character|State", meta = (AllowPrivateAccess = "true"))
	bool bAttributesInitialized;

	/** 用于标记角色眩晕/受击状态的 GameplayTag */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|State")
	FGameplayTag StunnedTag;
};
