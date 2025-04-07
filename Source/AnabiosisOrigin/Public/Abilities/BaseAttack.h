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
* 文件名: BaseAttack.h
* 功能描述：
* - 实现基础攻击能力系统
* - 管理攻击动画的播放和控制
* - 处理攻击相关的标签和状态
*
* 关键组件：
* - 攻击动画蒙太奇：控制攻击动作表现
* - 能力标签系统：管理攻击状态
* - 动画任务系统：处理动画播放
*/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "BaseAttack.generated.h"

/**
 * 基础攻击能力类
 * 负责实现角色的基础攻击行为，包括动画播放和网络同步
 */
UCLASS()
class ANABIOSISORIGIN_API UBaseAttack : public UGameplayAbility
{
    GENERATED_BODY()
    
public:
    /** 初始化能力实例化策略 */
    UBaseAttack();

    /** 攻击动画资源 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力")
    UAnimMontage* AttackMontage;

    /** 能力标签 */
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
    
    /** 重写EndAbility以确保清理 */
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
    /** 管理动画播放的任务 */
    UPROPERTY()
    UAbilityTask_PlayMontageAndWait* MontageTask;
};
