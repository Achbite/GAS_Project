/*
 * Copyright (C) 2025 [Wang]
 * ... (Copyleft header) ...
 */

/*
* 文件名: GA_HitReact.h
* 功能描述： 定义受击反应 Gameplay Ability (UGA_HitReact)。
*            当拥有者获得 State.HitReact 标签时激活，播放受击蒙太奇并禁用移动。
*            能力结束时恢复移动并自动移除 State.HitReact 标签。
* 结构：
* - UGA_HitReact：受击反应能力类。
*   - ActivateAbility：能力激活逻辑，禁用移动并播放蒙太奇。
*   - EndAbility：能力结束逻辑，恢复移动并清理任务。
*   - OnMontageCompleted/Cancelled/Interrupted/BlendOut：蒙太奇回调函数，用于结束能力。
*   - MontageTask：播放蒙太奇的异步任务。
*   - CachedMovementComponent：缓存的移动组件指针。
*   - GetHitReactionMontage：根据角色类型获取相应的受击蒙太奇。
*/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/CharacterMovementComponent.h" // 包含移动组件头文件
#include "GA_HitReact.generated.h"

// 前向声明
class UAbilityTask_PlayMontageAndWait;
class UAnimMontage;
class ACharacter;

/**
 * 处理受击反应的 Gameplay Ability。
 * 当被激活时（例如通过 State.HitReact 标签），播放受击蒙太奇并禁用移动。
 * 能力结束时恢复移动。
 */
UCLASS()
class ANABIOSISORIGIN_API UGA_HitReact : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_HitReact();

protected:
	/** 当能力激活时调用 */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	/** 当能力结束时调用 */
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	/** 蒙太奇播放完成时的回调 */
	UFUNCTION()
	void OnMontageCompleted();

	/** 蒙太奇被取消时的回调 */
	UFUNCTION()
	void OnMontageCancelled();

	/** 蒙太奇被中断时的回调 (例如被另一次攻击打断) */
	UFUNCTION()
	void OnMontageInterrupted();

	/** 蒙太奇淡出完成时的回调 */
	UFUNCTION()
	void OnMontageBlendOut();

private:
	/** 播放蒙太奇的异步任务 */
	UPROPERTY()
	TObjectPtr<UAbilityTask_PlayMontageAndWait> MontageTask;

	/** 缓存的移动组件，用于在能力结束时恢复移动 */
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> CachedMovementComponent;

	/** 根据拥有者角色的类型获取相应的受击蒙太奇 */
	UAnimMontage* GetHitReactionMontage(ACharacter* OwnerCharacter) const;
};
