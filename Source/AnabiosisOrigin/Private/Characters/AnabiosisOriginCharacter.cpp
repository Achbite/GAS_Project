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
// Copyright Epic Games, Inc. All Rights Reserved.

/*
* 文件名: AnabiosisOriginCharacter.cpp
* 功能描述： 实现玩家角色基础功能，包括组件初始化、GAS 设置和属性加载。
*/

#include "Characters/AnabiosisOriginCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
// #include "Components/InputComponent.h" // Likely unused directly if using Enhanced Input with GAS
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h"
// #include "AbilitySystemGlobals.h" // Likely unused directly
#include "Attributes/AnabiosisAttributeSet.h" 
#include "Data/AnabiosisAttributeData.h" 
#include "Animation/AnimInstance.h" 
#include "Engine/DataTable.h" 
#include "Components/SkeletalMeshComponent.h" 
#include "Items/WeaponBase.h" 
#include "Data/WeaponAttributeData.h" 
// #include "AbilitySystemComponent.h" // Already included
#include "UObject/UObjectGlobals.h" 
#include "GameplayTagContainer.h" 

AAnabiosisOriginCharacter::AAnabiosisOriginCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UAnabiosisAttributeSet>(TEXT("AttributeSet"));

	AttributeDataTable = nullptr;
	AttributeDataRowName = NAME_None;
	WeaponAttributeDataTable = nullptr; 
	CurrentWeapon = nullptr; 
	CurrentClass = EAnabiosisPlayerClass::Warrior; 
	LoadedDeathMontage = nullptr; 
	bIsDead = false; 
	HitReactionMontage = nullptr; 
}

void AAnabiosisOriginCharacter::BeginPlay()
{
	Super::BeginPlay();
	BindAttributeChangeListeners(); 
	// Data loading should happen in PostInitializeComponents or based on game events
}

UAbilitySystemComponent* AAnabiosisOriginCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAnabiosisOriginCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this); 
		// Attributes should be initialized in PostInitializeComponents
		GiveDefaultAbilities(); 
		BindAttributeChangeListeners(); 
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: AbilitySystemComponent is NULL during PossessedBy!"), *GetName());
	}
}

void AAnabiosisOriginCharacter::GiveDefaultAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || !AttributeSet)
	{
		return;
	}

	for (const TSubclassOf<UGameplayAbility>& Ability : DefaultAbilities)
	{
		if (Ability)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
		}
	}
}

void AAnabiosisOriginCharacter::SetPlayerClass(EAnabiosisPlayerClass NewClass)
{
	if (GetLocalRole() == ROLE_Authority && CurrentClass != NewClass)
	{
		CurrentClass = NewClass;
		UpdateAttributesForClass();
	}
}

void AAnabiosisOriginCharacter::UpdateAttributesForClass()
{
	// Reload attributes from data table based on the new class
	InitializeAttributesFromDataTable();
}

void AAnabiosisOriginCharacter::SetCharacterRotationMode(bool bOrientToMovement, bool bUseControllerRotation)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bOrientRotationToMovement = bOrientToMovement;
	}
	bUseControllerRotationYaw = bUseControllerRotation;
}

void AAnabiosisOriginCharacter::SetAttackAbilityTag(const FGameplayTag& NewTag)
{
	if (!AbilitySystemComponent) return; 

	if (AttackAbilityTag.IsValid())
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(AttackAbilityTag);
	}
	
	AttackAbilityTag = NewTag;
	if (AttackAbilityTag.IsValid())
	{
		AbilitySystemComponent->AddLooseGameplayTag(AttackAbilityTag);
	}
}

void AAnabiosisOriginCharacter::RefreshAbilityBindings()
{
	// This function's purpose is unclear and potentially problematic.
	// Removing and re-adding tags might not be the intended way to refresh bindings.
	// Consider using Input Mapping Contexts and GAS input binding for a cleaner approach.
	UE_LOG(LogTemp, Warning, TEXT("RefreshAbilityBindings called. Review its logic and consider alternatives."));
	if (!AbilitySystemComponent) return;
	
	// Example of re-adding the current attack tag:
	if (AttackAbilityTag.IsValid())
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(AttackAbilityTag);
		AbilitySystemComponent->AddLooseGameplayTag(AttackAbilityTag);
	}
}

bool AAnabiosisOriginCharacter::IsDead() const
{
	return bIsDead;
}

void AAnabiosisOriginCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GetLocalRole() == ROLE_Authority)
	{
		InitializeAttributesFromDataTable();
	}
	// Client needs listener binding too
	// BindAttributeChangeListeners(); // Moved to BeginPlay/PossessedBy
}

void AAnabiosisOriginCharacter::InitializeAttributesFromDataTable()
{
	if (!AttributeDataTable || AttributeDataRowName == NAME_None || !AttributeSet || !AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: Failed pre-initialization checks (DataTable, RowName, AttributeSet, or ASC missing)."), *GetName());
		return;
	}
	UAnabiosisAttributeSet* PlayerAttributeSet = Cast<UAnabiosisAttributeSet>(AttributeSet); 
	if (!PlayerAttributeSet)
	{
		UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: AttributeSet is not UAnabiosisAttributeSet!"), *GetName()); 
		return;
	}

	const FString ContextString(TEXT("Loading Player Attributes"));
	const FAnabiosisAttributeData* Row = AttributeDataTable->FindRow<FAnabiosisAttributeData>(AttributeDataRowName, ContextString);
	if (!Row)
	{
		UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: Cannot find row '%s' in AttributeDataTable '%s'!"), *GetName(), *AttributeDataRowName.ToString(), *AttributeDataTable->GetName());
		return;
	}

	// Apply attributes using ASC for base values, AttributeSet for current values
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetHealthAttribute(), Row->Health);
	PlayerAttributeSet->SetHealth(Row->Health);
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetMaxHealthAttribute(), Row->MaxHealth);
	PlayerAttributeSet->SetMaxHealth(Row->MaxHealth); 
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetManaAttribute(), Row->Mana);
	PlayerAttributeSet->SetMana(Row->Mana);
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetMaxManaAttribute(), Row->MaxMana);
	PlayerAttributeSet->SetMaxMana(Row->MaxMana); 
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetStrengthAttribute(), Row->Strength);
	PlayerAttributeSet->SetStrength(Row->Strength);
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetAgilityAttribute(), Row->Agility);
	PlayerAttributeSet->SetAgility(Row->Agility);
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetConstitutionAttribute(), Row->Constitution);
	PlayerAttributeSet->SetConstitution(Row->Constitution);
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetIntelligenceAttribute(), Row->Intelligence);
	PlayerAttributeSet->SetIntelligence(Row->Intelligence);
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetAttackPowerAttribute(), Row->AttackPower);
	PlayerAttributeSet->SetAttackPower(Row->AttackPower);
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetDefenseAttribute(), Row->Defense);
	PlayerAttributeSet->SetDefense(Row->Defense);
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetCriticalChanceAttribute(), Row->CriticalChance);
	PlayerAttributeSet->SetCriticalChance(Row->CriticalChance);
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetCriticalMultiplierAttribute(), Row->CriticalMultiplier);
	PlayerAttributeSet->SetCriticalMultiplier(Row->CriticalMultiplier);

	// Load montages
	HitReactionMontage = Row->HitReactionMontage; 
	if (!HitReactionMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player %s: HitReactionMontage is not set in DataTable row '%s'."), *GetName(), *AttributeDataRowName.ToString());
	}
	LoadedDeathMontage = Row->DeathMontage;
	if (!LoadedDeathMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player %s: DeathMontage is not set in DataTable row '%s'."), *GetName(), *AttributeDataRowName.ToString());
	}

	// UE_LOG(LogTemp, Log, TEXT("Player %s initialized attributes and montages..."), *GetName()); // Optional Log

	// Spawn weapon
	if (GetLocalRole() == ROLE_Authority) 
	{
		SpawnAndAttachWeapon(Row->WeaponDataRowName, Row->WeaponAttachSocketName);
	}
}

void AAnabiosisOriginCharacter::SpawnAndAttachWeapon(const FName& InWeaponDataRowName, const FName& InAttachSocketName)
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}

	if (!WeaponAttributeDataTable || InWeaponDataRowName == NAME_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: WeaponAttributeDataTable not set or WeaponDataRowName is None. Cannot spawn weapon."), *GetName());
		return;
	}
	 if (InAttachSocketName == NAME_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: WeaponAttachSocketName is None. Cannot attach weapon correctly."), *GetName());
	}

	const FString ContextString(TEXT("Loading Weapon Attributes"));
	FWeaponAttributeData* WeaponRow = WeaponAttributeDataTable->FindRow<FWeaponAttributeData>(InWeaponDataRowName, ContextString);
	if (!WeaponRow)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: Cannot find row '%s' in WeaponAttributeDataTable '%s'!"), *GetName(), *InWeaponDataRowName.ToString(), *WeaponAttributeDataTable->GetName());
		return;
	}

	if (WeaponRow->WeaponActorClassPtr.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("%s: WeaponActorClassPtr is not set in WeaponAttributeData row '%s'!"), *GetName(), *InWeaponDataRowName.ToString());
		return;
	}

	TSubclassOf<AWeaponBase> LoadedWeaponClass = WeaponRow->WeaponActorClassPtr.LoadSynchronous();
	if (!LoadedWeaponClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: Failed to load WeaponActorClassPtr from path %s in row '%s'!"), *GetName(), *WeaponRow->WeaponActorClassPtr.ToString(), *InWeaponDataRowName.ToString());
		return;
	}

	UWorld* World = GetWorld();
	if (!World) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CurrentWeapon = World->SpawnActor<AWeaponBase>(LoadedWeaponClass, GetActorLocation(), GetActorRotation(), SpawnParams);

	if (CurrentWeapon)
	{
		// UE_LOG(LogTemp, Log, TEXT("%s spawned weapon: %s"), *GetName(), *CurrentWeapon->GetName()); // Optional Log

		if (GetMesh() && InAttachSocketName != NAME_None)
		{
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, InAttachSocketName);
			 // UE_LOG(LogTemp, Log, TEXT("  Attached %s to socket %s"), *CurrentWeapon->GetName(), *InAttachSocketName.ToString()); // Optional Log
		} else {
			 UE_LOG(LogTemp, Warning, TEXT("  Could not attach %s. Mesh invalid or SocketName is None."), *CurrentWeapon->GetName());
		}

		if (WeaponRow->GrantedAttributesEffect && AbilitySystemComponent)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddSourceObject(CurrentWeapon);
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(WeaponRow->GrantedAttributesEffect, 1, EffectContext);
			if (SpecHandle.IsValid())
			{
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
				// UE_LOG(LogTemp, Log, TEXT("  Applied GrantedAttributesEffect: %s"), *WeaponRow->GrantedAttributesEffect->GetName()); // Optional Log
			}
			 // else { UE_LOG(LogTemp, Warning, ...); } // Optional Warning
		}

		if (WeaponRow->InitialAttackTag.IsValid())
		{
			SetAttackAbilityTag(WeaponRow->InitialAttackTag); 
			// UE_LOG(LogTemp, Log, TEXT("  Set AttackAbilityTag to %s from weapon data."), *WeaponRow->InitialAttackTag.ToString()); // Optional Log
		}
		// else { UE_LOG(LogTemp, Log, ...); } // Optional Log
	}
	 else
	{
		UE_LOG(LogTemp, Error, TEXT("%s failed to spawn weapon actor from loaded class %s!"), *GetName(), *LoadedWeaponClass->GetName());
	}
}

void AAnabiosisOriginCharacter::BindAttributeChangeListeners()
{
	if (AbilitySystemComponent && AttributeSet)
	{
		const UAnabiosisAttributeSet* PlayerAttributeSet = Cast<const UAnabiosisAttributeSet>(AttributeSet);
		if (PlayerAttributeSet)
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetHealthAttribute()).AddUObject(this, &AAnabiosisOriginCharacter::OnHealthAttributeChanged);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("BindAttributeChangeListeners: AttributeSet is not UAnabiosisAttributeSet for %s"), *GetName());
		}
	}
}

void AAnabiosisOriginCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	// UE_LOG(LogTemp, Verbose, TEXT("%s Health changed from %.1f to %.1f"), *GetName(), Data.OldValue, Data.NewValue); // Optional Log
	if (!bIsDead && Data.NewValue <= 0.0f && Data.OldValue > 0.0f) 
	{
		HandleDeath(); 
	}
}

void AAnabiosisOriginCharacter::HandleDeath()
{
	if (bIsDead) return;
	bIsDead = true;
	// UE_LOG(LogTemp, Log, TEXT("AnabiosisOriginCharacter %s is handling death."), *GetName()); // Optional Log

	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr; 
		// UE_LOG(LogTemp, Log, TEXT("  Destroyed CurrentWeapon for %s."), *GetName()); // Optional Log
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
		GetCharacterMovement()->SetComponentTickEnabled(false);
	}

	if (UCapsuleComponent* CapsuleComp = GetCapsuleComponent())
	{
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
	if (GetMesh())
	{
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;
	if (AnimInstance && LoadedDeathMontage)
	{
		const float PlayRate = 1.0f;
		AnimInstance->Montage_Play(LoadedDeathMontage, PlayRate);
		FOnMontageEnded MontageEndedDelegate;
		MontageEndedDelegate.BindUObject(this, &AAnabiosisOriginCharacter::OnDeathMontageEnded);
		AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, LoadedDeathMontage);
		// UE_LOG(LogTemp, Log, TEXT("  Playing Death Montage: %s"), *LoadedDeathMontage->GetName()); // Optional Log
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("  Cannot play death montage: AnimInstance (%p) or LoadedDeathMontage (%p) is invalid."), AnimInstance, LoadedDeathMontage.Get());
		SetLifeSpan(3.0f); 
	}

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAllAbilities();
	}

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		DisableInput(PC);
	}
}

void AAnabiosisOriginCharacter::OnDeathMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// UE_LOG(LogTemp, Log, TEXT("AnabiosisOriginCharacter %s death montage ended. Destroying Actor."), *GetName()); // Optional Log
	Destroy();
}
