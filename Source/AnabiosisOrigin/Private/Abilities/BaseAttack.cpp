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
* 文件名: BaseAttack.cpp
* 功能描述： 实现基础攻击 Gameplay Ability UBaseAttack 的逻辑。
*            负责播放攻击动画蒙太奇并管理能力的生命周期。
* 结构：
* - 构造函数：设置实例化策略。
* - ActivateAbility：能力激活时调用，提交能力消耗，检查动画资源，创建并启动动画播放任务，绑定回调。
* - HandleMontage...：动画播放任务的回调函数，在动画完成、取消、中断或混合结束时结束能力。
* - EndAbility：结束能力，确保取消动画任务。
*/

#include "Abilities/BaseAttack.h"
#include "GameFramework/AnabiosisOriginGameMode.h" // 可能需要包含游戏模式头文件 (如果用到)
#include "AbilitySystemComponent.h" // 包含 ASC
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h" // 包含动画播放任务
#include "Animation/AnimMontage.h" // 包含动画蒙太奇

UBaseAttack::UBaseAttack()
{
	// 设置能力的实例化策略为每个 Actor 一个实例
	// 这意味着每个拥有此能力的角色都会有一个独立的实例
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UBaseAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	// 首先尝试提交能力（检查消耗、冷却、标签阻塞等）
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		// 如果提交失败（例如，资源不足或冷却中），则立即结束能力
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true); // true 表示复制结束状态，true 表示被取消
		return;
	}

	// 检查攻击动画蒙太奇资源是否有效
	if (!AttackMontage)
	{
		UE_LOG(LogTemp, Error, TEXT("基础攻击能力：AttackMontage 未设置！"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// 创建并配置动画播放任务 (PlayMontageAndWait)
	MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,      // 能力实例自身
		NAME_None, // 任务实例名称 (可选)
		AttackMontage, // 要播放的蒙太奇
		1.0f,      // 播放速率
		NAME_None, // 起始段落名称 (NAME_None 表示从头播放)
		true       // 能力结束时是否停止蒙太奇
	);

	// 检查任务是否成功创建
	if (!MontageTask)
	{
		UE_LOG(LogTemp, Error, TEXT("基础攻击能力：创建 MontageTask 失败！"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// 绑定动画播放任务的事件回调
	MontageTask->OnCompleted.AddDynamic(this, &UBaseAttack::HandleMontageCompleted);     // 动画正常完成
	MontageTask->OnCancelled.AddDynamic(this, &UBaseAttack::HandleMontageCancelled);     // 动画被取消
	MontageTask->OnInterrupted.AddDynamic(this, &UBaseAttack::HandleMontageInterrupted); // 动画被中断 (例如被其他蒙太奇覆盖)
	MontageTask->OnBlendOut.AddDynamic(this, &UBaseAttack::HandleMontageBlendOut);       // 动画混合结束

	// 准备并激活动画任务
	MontageTask->ReadyForActivation();

	// 安全检查：如果任务未能成功激活（例如，在 ReadyForActivation 内部失败），则结束能力
	// if (!MontageTask->IsActive())
	// {
	//     UE_LOG(LogTemp, Warning, TEXT("基础攻击能力：MontageTask 未能激活。"));
	//     EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	// }
}

// --- 动画任务回调函数 ---

void UBaseAttack::HandleMontageCompleted()
{
	// 动画正常完成时结束能力
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false); // false 表示非取消
}

void UBaseAttack::HandleMontageCancelled()
{
	// 动画被取消时结束能力
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true); // true 表示被取消
}

void UBaseAttack::HandleMontageInterrupted()
{
	// 动画被中断时结束能力
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true); // true 表示被取消 (中断视为一种取消)
}

void UBaseAttack::HandleMontageBlendOut()
{
	// 动画混合结束时结束能力 (通常在 OnCompleted 之后触发，但为了保险起见也处理)
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false); // false 表示非取消
}

// --- 重写 EndAbility ---

void UBaseAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// 确保在调用 Super::EndAbility 之前停止蒙太奇任务
	// 这样可以避免在父类逻辑中再次尝试结束任务或产生冲突
	if (MontageTask && MontageTask->IsActive())
	{
		MontageTask->EndTask(); // 使用 EndTask 而不是 ExternalCancel，以避免触发 OnCancelled 回调
	}
	MontageTask = nullptr; // 清理任务指针

	// 调用父类的 EndAbility 实现
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


