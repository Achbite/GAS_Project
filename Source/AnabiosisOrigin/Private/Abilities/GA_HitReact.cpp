/*
 * Copyright (C) 2025 [Wang]
 * ... (Copyleft header) ...
 */

/*
* 文件名: GA_HitReact.cpp
* 功能描述： 实现受击反应 Gameplay Ability (UGA_HitReact) 的逻辑。
*            获取角色的受击蒙太奇并播放。
*/

#include "Abilities/GA_HitReact.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "Characters/AnabiosisOriginCharacter.h" // Include player character
#include "Characters/EnemyBaseCharacter.h"     // Include enemy character
#include "AbilitySystemComponent.h"

UGA_HitReact::UGA_HitReact()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted; // Or ServerInitiated if preferred
	// Important: Configure Tags in the Blueprint child class or here if needed
	// AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.HitReact")));
	// ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.HitReact")));
	// ActivationRequiredTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.HitReact")));
	// CancelAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Action.MeleeAttack"))); // Example
}

void UGA_HitReact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	// --- Add Log ---
	ACharacter* LogOwnerCharacter = ActorInfo ? Cast<ACharacter>(ActorInfo->AvatarActor.Get()) : nullptr;
	UE_LOG(LogTemp, Log, TEXT("GA_HitReact: ActivateAbility called for %s."), LogOwnerCharacter ? *LogOwnerCharacter->GetName() : TEXT("Unknown Actor"));
	// ---------------

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		// --- Add Log ---
		UE_LOG(LogTemp, Warning, TEXT("GA_HitReact: Failed to commit ability for %s."), LogOwnerCharacter ? *LogOwnerCharacter->GetName() : TEXT("Unknown Actor"));
		// ---------------
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	ACharacter* OwnerCharacter = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (!OwnerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("GA_HitReact: Owner is not a Character."));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// --- Add Log ---
	UE_LOG(LogTemp, Log, TEXT("GA_HitReact: Getting HitReactionMontage for %s."), *OwnerCharacter->GetName());
	// ---------------
	UAnimMontage* MontageToPlay = GetHitReactionMontage(OwnerCharacter);

	if (!MontageToPlay)
	{
		// --- Log already exists ---
		UE_LOG(LogTemp, Warning, TEXT("GA_HitReact: No HitReactionMontage found for %s. Ending ability."), *OwnerCharacter->GetName());
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false); // End normally if no montage
		return;
	}

	// --- Add Log ---
	UE_LOG(LogTemp, Log, TEXT("GA_HitReact: Found Montage %s. Creating MontageTask for %s."), *MontageToPlay->GetName(), *OwnerCharacter->GetName());
	// ---------------

	MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		NAME_None,
		MontageToPlay,
		1.0f, // PlayRate
		NAME_None, // StartSection
		true // bStopWhenAbilityEnds
	);

	if (!MontageTask)
	{
		// --- Log already exists ---
		UE_LOG(LogTemp, Error, TEXT("GA_HitReact: Failed to create MontageTask for %s."), *OwnerCharacter->GetName());
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// Bind delegates
	MontageTask->OnCompleted.AddDynamic(this, &UGA_HitReact::OnMontageCompleted);
	MontageTask->OnCancelled.AddDynamic(this, &UGA_HitReact::OnMontageCancelled);
	MontageTask->OnInterrupted.AddDynamic(this, &UGA_HitReact::OnMontageInterrupted);
	MontageTask->OnBlendOut.AddDynamic(this, &UGA_HitReact::OnMontageBlendOut);

	MontageTask->ReadyForActivation();
	// --- Log already exists ---
	UE_LOG(LogTemp, Verbose, TEXT("GA_HitReact: Activated and playing montage %s for %s."), *MontageToPlay->GetName(), *OwnerCharacter->GetName());
}

void UGA_HitReact::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Clean up the montage task if it's still active
	if (MontageTask && MontageTask->IsActive())
	{
		MontageTask->EndTask();
	}
	MontageTask = nullptr;

	UE_LOG(LogTemp, Verbose, TEXT("GA_HitReact: Ended. Cancelled: %s"), bWasCancelled ? TEXT("Yes") : TEXT("No"));
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	// ActivationOwnedTags (State.HitReact) will be removed automatically by the base class
}

void UGA_HitReact::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGA_HitReact::OnMontageCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UGA_HitReact::OnMontageInterrupted()
{
	// Important: If interrupted (e.g., by another hit), we still end the ability.
	// The new hit will apply the tag again and potentially re-trigger this ability.
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UGA_HitReact::OnMontageBlendOut()
{
	// Usually called after Completed/Cancelled/Interrupted, handle just in case.
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

UAnimMontage* UGA_HitReact::GetHitReactionMontage(ACharacter* OwnerCharacter) const
{
	if (!OwnerCharacter) return nullptr;

	UAnimMontage* FoundMontage = nullptr; // Variable to store the found montage

	// Try casting to Player Character
	if (AAnabiosisOriginCharacter* PlayerChar = Cast<AAnabiosisOriginCharacter>(OwnerCharacter))
	{
		FoundMontage = PlayerChar->GetHitReactionMontage();
		// --- Add Log ---
		UE_LOG(LogTemp, Log, TEXT("GA_HitReact: GetHitReactionMontage - Checked Player %s. Montage: %s"),
			*PlayerChar->GetName(), FoundMontage ? *FoundMontage->GetName() : TEXT("NULL"));
		// ---------------
		return FoundMontage;
	}

	// Try casting to Enemy Character
	if (AEnemyBaseCharacter* EnemyChar = Cast<AEnemyBaseCharacter>(OwnerCharacter))
	{
		FoundMontage = EnemyChar->GetHitReactionMontage();
		// --- Add Log ---
		UE_LOG(LogTemp, Log, TEXT("GA_HitReact: GetHitReactionMontage - Checked Enemy %s. Montage: %s"),
			*EnemyChar->GetName(), FoundMontage ? *FoundMontage->GetName() : TEXT("NULL"));
		// ---------------
		return FoundMontage;
	}

	// Add checks for other character types if necessary

	// --- Log already exists ---
	UE_LOG(LogTemp, Warning, TEXT("GA_HitReact: GetHitReactionMontage - Owner %s is not a recognized character type (Player or Enemy)."), *OwnerCharacter->GetName());
	return nullptr;
}
