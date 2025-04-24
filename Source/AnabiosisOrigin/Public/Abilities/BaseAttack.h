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
* 文件名: BaseAttack.h
* 功能描述： 定义基础攻击 Gameplay Ability (UBaseAttack)。
*            负责播放攻击动画蒙太奇，并处理能力生命周期和中断逻辑（如被受击打断）。
* 结构：
* - UBaseAttack：基础攻击能力类。
*   - AttackMontage：用于此攻击的动画蒙太奇。
*   - AbilityTag：此攻击能力的标识标签 (可能用于连击系统)。
*   - ActivateAbility：能力激活逻辑，注册标签监听器并播放蒙太奇。
*   - EndAbility：能力结束逻辑，清理蒙太奇任务和标签监听器。
*   - HandleMontageCompleted/Cancelled/Interrupted/BlendOut：蒙太奇回调函数。
*   - HandleGameplayTagEvent：监听 Gameplay Tag 变化的回调，用于处理中断。
*   - MontageTask：播放蒙太奇的异步任务。
*   - GameplayTagEventHandle：Gameplay Tag 监听器的委托句柄。
*/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
// #include "AbilitySystemComponent.h" // GameplayAbility 已包含
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameplayTagContainer.h" // 包含 FGameplayTag
#include "BaseAttack.generated.h"

/**
 * 基础攻击能力类
 * 负责实现角色的基础攻击行为，包括动画播放和网络同步。
 * 可以被 State.HitReact 标签中断。
 */
UCLASS()
class ANABIOSISORIGIN_API UBaseAttack : public UGameplayAbility
{
    GENERATED_BODY()

public:
    /** 构造函数，设置实例化策略等 */
    UBaseAttack();

    /** 攻击动画资源 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力")
    UAnimMontage* AttackMontage;

    /**
     * 此攻击能力的标识标签。
     * 可用于连击系统，例如在 AttackWindowNotifyState 中设置下一个可用的攻击标签。
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力")
    FGameplayTag AbilityTag;

protected:
    /** 处理能力激活逻辑 */
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

    /** 动画完成回调 */
    UFUNCTION()
    void HandleMontageCompleted();

    /** 动画取消回调 */
    UFUNCTION()
    void HandleMontageCancelled();

    /** 动画被打断回调 */
    UFUNCTION()
    void HandleMontageInterrupted();

    /** 动画混合结束回调 */
    UFUNCTION()
    void HandleMontageBlendOut();

    /** 重写 EndAbility 以确保清理标签监听器和蒙太奇任务 */
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

    /** 处理 Gameplay Tag 变化的回调 (例如，监听 State.HitReact 以中断攻击) */
    UFUNCTION()
    void HandleGameplayTagEvent(FGameplayTag Tag, int32 NewCount);

private:
    /** 管理动画播放的异步任务 */
    UPROPERTY()
    UAbilityTask_PlayMontageAndWait* MontageTask;

    /** Gameplay Tag 监听器的委托句柄，用于在能力结束时注销监听 */
    FDelegateHandle GameplayTagEventHandle;
};

