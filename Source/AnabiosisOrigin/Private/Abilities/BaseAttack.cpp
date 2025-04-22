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
* 基础攻击能力实现文件
* 实现功能：
* 1. 能力初始化
* 2. 动画播放控制
* 3. 能力生命周期管理
*/

#include "Abilities/BaseAttack.h"
#include "GameFramework/AnabiosisOriginGameMode.h"

UBaseAttack::UBaseAttack()
{
    // 设置能力的实例化策略为每个角色一个实例
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UBaseAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    // 首先尝试提交能力（检查消耗等）
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        // 提交失败时结束能力
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    // 检查动画资源是否有效
    if (!AttackMontage)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    // 创建动画播放任务
    MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
        this,
        NAME_None,
        AttackMontage,
        1.0f,      // 播放速率
        NAME_None, // 起始段落名称
        true       // 能力结束时停止动画
    );

    // 绑定动画事件
    MontageTask->OnCompleted.AddDynamic(this, &UBaseAttack::HandleMontageCompleted);
    MontageTask->OnCancelled.AddDynamic(this, &UBaseAttack::HandleMontageCancelled);
    MontageTask->OnInterrupted.AddDynamic(this, &UBaseAttack::HandleMontageInterrupted);
    MontageTask->OnBlendOut.AddDynamic(this, &UBaseAttack::HandleMontageBlendOut);
    
    // 激活动画任务
    MontageTask->ReadyForActivation();
    
    // 安全检查：如果动画播放失败，确保能力会结束
    if (!MontageTask->IsActive())
    {
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
    }
}

void UBaseAttack::HandleMontageCompleted()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UBaseAttack::HandleMontageCancelled()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UBaseAttack::HandleMontageInterrupted()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UBaseAttack::HandleMontageBlendOut()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

// 重写EndAbility确保能力被正确清理
void UBaseAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    // 防止递归调用
    static bool bIsEndingAbility = false;
    if (bIsEndingAbility)
    {
        return;
    }
    
    bIsEndingAbility = true;
    
    // 如果蒙太奇任务仍然活跃，停止它
    if (MontageTask && MontageTask->IsActive())
    {
        MontageTask->ExternalCancel();
    }
    
    // 调用父类实现
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
    
    bIsEndingAbility = false;
}


