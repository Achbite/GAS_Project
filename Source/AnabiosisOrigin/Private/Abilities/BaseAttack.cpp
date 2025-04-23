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
*            在获得 State.HitReact 标签时中断攻击。
*/

#include "Abilities/BaseAttack.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Animation/AnimMontage.h"
#include "GameplayTagContainer.h" // Include for FGameplayTag

UBaseAttack::UBaseAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	// Define the tag that cancels this ability
	// ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.HitReact"))); // Optional: Prevent activation if already hit reacting
	// AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Attack"))); // Example tag for the ability itself
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

	// --- Register Gameplay Tag Listener ---
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		// Listen for the addition of the HitReact tag
		GameplayTagEventHandle = ASC->RegisterGameplayTagEvent(
			FGameplayTag::RequestGameplayTag(FName("State.HitReact")), // The tag to listen for
			EGameplayTagEventType::NewOrRemoved // Listen for both addition and removal (we only care about addition here)
		).AddUObject(this, &UBaseAttack::HandleGameplayTagEvent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BaseAttack Ability: Could not get ASC to register tag listener!"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	// ------------------------------------

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
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true); // EndAbility will unregister the tag listener
		return;
	}

	MontageTask->OnCompleted.AddDynamic(this, &UBaseAttack::HandleMontageCompleted);
	MontageTask->OnCancelled.AddDynamic(this, &UBaseAttack::HandleMontageCancelled);
	MontageTask->OnInterrupted.AddDynamic(this, &UBaseAttack::HandleMontageInterrupted);
	MontageTask->OnBlendOut.AddDynamic(this, &UBaseAttack::HandleMontageBlendOut);

	MontageTask->ReadyForActivation();
}

void UBaseAttack::HandleGameplayTagEvent(FGameplayTag Tag, int32 NewCount)
{
	// Check if the HitReact tag was added (NewCount > 0)
	if (Tag == FGameplayTag::RequestGameplayTag(FName("State.HitReact")) && NewCount > 0)
	{
		UE_LOG(LogTemp, Log, TEXT("BaseAttack Ability: HitReact tag added. Cancelling ability."));
		// Cancel the ability. This will trigger EndAbility, which stops the montage.
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
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
	// --- Unregister Gameplay Tag Listener ---
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (ASC && GameplayTagEventHandle.IsValid())
	{
		ASC->UnregisterGameplayTagEvent(GameplayTagEventHandle, FGameplayTag::RequestGameplayTag(FName("State.HitReact")), EGameplayTagEventType::NewOrRemoved);
		GameplayTagEventHandle.Reset(); // Clear the handle
	}
	// ------------------------------------

	// Ensure montage task is cleaned up before calling Super
	if (MontageTask && MontageTask->IsActive())
	{
		MontageTask->EndTask();
	}
	MontageTask = nullptr;

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


