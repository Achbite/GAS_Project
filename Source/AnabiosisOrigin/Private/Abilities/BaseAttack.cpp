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
*/

#include "Abilities/BaseAttack.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Animation/AnimMontage.h"

UBaseAttack::UBaseAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UBaseAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (!AttackMontage)
	{
		UE_LOG(LogTemp, Error, TEXT("BaseAttack Ability: AttackMontage is not set!"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		NAME_None,
		AttackMontage,
		1.0f,
		NAME_None,
		true // Stop when ability ends
	);

	if (!MontageTask)
	{
		UE_LOG(LogTemp, Error, TEXT("BaseAttack Ability: Failed to create MontageTask!"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	MontageTask->OnCompleted.AddDynamic(this, &UBaseAttack::HandleMontageCompleted);
	MontageTask->OnCancelled.AddDynamic(this, &UBaseAttack::HandleMontageCancelled);
	MontageTask->OnInterrupted.AddDynamic(this, &UBaseAttack::HandleMontageInterrupted);
	MontageTask->OnBlendOut.AddDynamic(this, &UBaseAttack::HandleMontageBlendOut);

	MontageTask->ReadyForActivation();
}

void UBaseAttack::HandleMontageCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UBaseAttack::HandleMontageCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UBaseAttack::HandleMontageInterrupted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UBaseAttack::HandleMontageBlendOut()
{
	// Often called after OnCompleted, but handle just in case
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UBaseAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Ensure montage task is cleaned up before calling Super
	if (MontageTask && MontageTask->IsActive())
	{
		MontageTask->EndTask();
	}
	MontageTask = nullptr;

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


