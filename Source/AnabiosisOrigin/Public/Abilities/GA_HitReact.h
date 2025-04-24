/*
 * Copyright (C) 2025 [Wang]
 * ... (Copyleft header) ...
 */

/*
* 文件名: GA_HitReact.h
* 功能描述： 定义受击反应 Gameplay Ability。
*            当拥有者获得 State.HitReact 标签时激活，播放受击蒙太奇并禁用移动。
*            能力结束时恢复移动并自动移除 State.HitReact 标签。
*/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/CharacterMovementComponent.h" // Include for movement component
#include "GA_HitReact.generated.h"

class UAbilityTask_PlayMontageAndWait;
class UAnimMontage;
class ACharacter; // Forward declaration

/**
 * Gameplay Ability for handling hit reactions (or other related logic).
 * Plays a hit reaction montage and disables movement when activated (e.g., by State.HitReact tag).
 * Restores movement when the ability ends.
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

	/** 蒙太奇被中断时的回调 */
	UFUNCTION()
	void OnMontageInterrupted();

	/** 蒙太奇淡出完成时的回调 */
	UFUNCTION()
	void OnMontageBlendOut();

private:
	/** 播放蒙太奇的任务 */
	UPROPERTY()
	TObjectPtr<UAbilityTask_PlayMontageAndWait> MontageTask;

	/** 缓存的移动组件，用于在能力结束时恢复移动 */
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> CachedMovementComponent;

	/** 获取拥有者角色的受击蒙太奇 */
	UAnimMontage* GetHitReactionMontage(ACharacter* OwnerCharacter) const;
};
