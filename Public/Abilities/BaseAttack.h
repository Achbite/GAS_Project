/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: BaseAttack.h
* 功能描述： 定义基础攻击 Gameplay Ability 类 UBaseAttack。
*            负责播放攻击动画蒙太奇，并管理能力的生命周期。
* 结构：
* - 继承自 UGameplayAbility。
* - 包含攻击动画蒙太奇资源引用。
* - 使用 UAbilityTask_PlayMontageAndWait 任务来播放动画。
* - 在 ActivateAbility 中启动动画播放任务。
* - 处理动画播放完成、取消、中断等事件，并在这些事件发生时结束能力。
* - 重写 EndAbility 以确保动画任务被正确取消。
*/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemComponent.h" // 包含 ASC
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h" // 包含动画播放任务
#include "BaseAttack.generated.h"

/**
 * @brief 基础攻击能力类。
 *        负责播放攻击动画蒙太奇。
 */
UCLASS()
class ANABIOSISORIGIN_API UBaseAttack : public UGameplayAbility
{
	GENERATED_BODY()

public:
	/** 构造函数，设置能力实例化策略 */
	UBaseAttack();

	/** 攻击动画蒙太奇资源 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力|动画")
	TObjectPtr<UAnimMontage> AttackMontage;

	/** 与此攻击能力关联的标签 (可选，用于识别或触发) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力|标签")
	FGameplayTag AbilityTag;

protected:
	/**
	 * @brief 激活能力，播放攻击动画。
	 * @param Handle 能力的唯一句柄。
	 * @param ActorInfo 能力拥有者的信息。
	 * @param ActivationInfo 能力激活信息。
	 * @param TriggerEventData 触发此能力的事件数据 (如果适用)。
	 */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	/** 动画正常完成时的回调 */
	UFUNCTION()
	void HandleMontageCompleted();

	/** 动画被取消时的回调 */
	UFUNCTION()
	void HandleMontageCancelled();

	/** 动画被中断时的回调 */
	UFUNCTION()
	void HandleMontageInterrupted();

	/** 动画混合结束时的回调 */
	UFUNCTION()
	void HandleMontageBlendOut();

	/**
	 * @brief 结束能力，确保清理动画任务。
	 * @param Handle 能力的唯一句柄。
	 * @param ActorInfo 能力拥有者的信息。
	 * @param ActivationInfo 能力激活信息。
	 * @param bReplicateEndAbility 是否复制能力结束状态。
	 * @param bWasCancelled 能力是否被取消。
	 */
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	/** 用于管理动画播放的异步任务 */
	UPROPERTY(Transient) // Transient 表示不需要保存
	TObjectPtr<UAbilityTask_PlayMontageAndWait> MontageTask;
};
