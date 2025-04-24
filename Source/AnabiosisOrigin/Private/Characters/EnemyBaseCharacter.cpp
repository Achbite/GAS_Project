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
* 文件名: EnemyBaseCharacter.cpp
* 功能描述： 实现AI敌人基础功能，初始化属性和能力系统，处理死亡逻辑。
*/

#include "Characters/EnemyBaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "Attributes/EnemyAttributeSet.h" 
#include "Data/EnemyAttributeData.h"    
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h" 
#include "GameFramework/Controller.h" 
#include "Engine/DamageEvents.h"    
#include "Components/SkeletalMeshComponent.h" 
#include "Animation/AnimInstance.h" 
#include "AI/AiBehaviorComponent.h" 
#include "GameplayTagsManager.h" 
#include "Abilities/GameplayAbility.h" 
#include "Items/WeaponBase.h" 
#include "Data/WeaponAttributeData.h" 
#include "Engine/DataTable.h" 
#include "UObject/UObjectGlobals.h" 

#define COLLISION_ENEMY ECC_GameTraceChannel1

AEnemyBaseCharacter::AEnemyBaseCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent)
	{
		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	}

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("AttributeSet"));
	AiBehaviorComponent = CreateDefaultSubobject<UAiBehaviorComponent>(TEXT("AiBehaviorComponent"));

	UCapsuleComponent* Capsule = GetCapsuleComponent();
	if (Capsule)
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Capsule->SetCollisionObjectType(ECC_Pawn);
		Capsule->SetCollisionResponseToAllChannels(ECR_Block);
		Capsule->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
		Capsule->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
		Capsule->SetCollisionResponseToChannel(COLLISION_ENEMY, ECR_Block);
	}

	USkeletalMeshComponent* MeshComp = GetMesh();
	if (MeshComp)
	{
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
		MeshComp->SetCollisionObjectType(ECC_WorldStatic); 
		MeshComp->SetCollisionResponseToAllChannels(ECR_Ignore); 
	}

	AttributeDataTable = nullptr;
	AttributeDataRowName = NAME_None;
	WeaponAttributeDataTable = nullptr; 
	CurrentWeapon = nullptr; 
	LoadedHitReactionMontage = nullptr; 
	LoadedDeathMontage = nullptr; 
	bIsDead = false; 
	bAttributesInitialized = false; 
}

void AEnemyBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GetLocalRole() == ROLE_Authority && !bAttributesInitialized)
	{
		InitializeAttributesFromDataTable();
	}
}

void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	// 可以留空，或者添加特定于 BeginPlay 的逻辑
}

void AEnemyBaseCharacter::InitializeAttributesFromDataTable()
{
	if (bAttributesInitialized) return;
	if (!AttributeDataTable || AttributeDataRowName == NAME_None || !AttributeSet || !AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyBaseCharacter %s: Failed pre-initialization checks (DataTable, RowName, AttributeSet, or ASC missing)."), *GetName());
		return;
	}

	const FString ContextString(TEXT("Loading Enemy Attributes"));
	FEnemyAttributeData* Row = AttributeDataTable->FindRow<FEnemyAttributeData>(AttributeDataRowName, ContextString);
	if (!Row)
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyBaseCharacter %s: Cannot find row '%s' in AttributeDataTable '%s'!"), *GetName(), *AttributeDataRowName.ToString(), *AttributeDataTable->GetName());
		return;
	}

	// Apply attributes
	AbilitySystemComponent->SetNumericAttributeBase(AttributeSet->GetHealthAttribute(), Row->InitialHealth);
	AttributeSet->SetHealth(Row->InitialHealth); 
	AbilitySystemComponent->SetNumericAttributeBase(AttributeSet->GetMaxHealthAttribute(), Row->InitialMaxHealth);
	AbilitySystemComponent->SetNumericAttributeBase(AttributeSet->GetAttackPowerAttribute(), Row->AttackPower);
	AbilitySystemComponent->SetNumericAttributeBase(AttributeSet->GetDefenseAttribute(), Row->Defense);

	// Load montages
	LoadedHitReactionMontage = Row->HitReactionMontage;
	if (!LoadedHitReactionMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy %s: HitReactionMontage is not set in DataTable row '%s'."), *GetName(), *AttributeDataRowName.ToString());
	}
	LoadedDeathMontage = Row->DeathMontage;
	if (!LoadedDeathMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy %s: DeathMontage is not set in DataTable row '%s'."), *GetName(), *AttributeDataRowName.ToString());
	}

	// Grant abilities
	if (HasAuthority()) 
	{
		for (const TSubclassOf<UGameplayAbility>& AbilityClass : Row->GrantedAbilities)
		{
			if (AbilityClass)
			{
				FGameplayAbilitySpec AbilitySpec(AbilityClass, 1, INDEX_NONE, this); 
				AbilitySystemComponent->GiveAbility(AbilitySpec); // Give ability directly
			}
		}
	}

	// Initialize AI Behavior
	if (AiBehaviorComponent)
	{
		AiBehaviorComponent->InitializeBehavior(this, *Row); 
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyBaseCharacter %s: AiBehaviorComponent is NULL! Cannot initialize AI behavior."), *GetName());
	}

	bAttributesInitialized = true;

	// Spawn weapon
	if (GetLocalRole() == ROLE_Authority) 
	{
		SpawnAndAttachWeapon(Row->WeaponDataRowName, Row->WeaponAttachSocketName);
	}
}

UAbilitySystemComponent* AEnemyBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UEnemyAttributeSet* AEnemyBaseCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

UAnimMontage* AEnemyBaseCharacter::GetHitReactionMontage() const
{
	return LoadedHitReactionMontage;
}

bool AEnemyBaseCharacter::IsStunned() const
{
	return AbilitySystemComponent && AbilitySystemComponent->HasMatchingGameplayTag(StunnedTag);
}

void AEnemyBaseCharacter::HandleHitReaction_Implementation(AActor* DamageCauser)
{
	// 基础 C++ 实现。可以留空，或者添加通用逻辑。
	// 蓝图可以覆盖此行为。
	// UE_LOG(LogTemp, Log, TEXT("%s HandleHitReaction_Implementation called."), *GetName()); // Optional Log
}

void AEnemyBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		if (!StunnedTag.IsValid())
		{
			StunnedTag = FGameplayTag::RequestGameplayTag(FName("AI.State.Stunned"));
			UE_LOG(LogTemp, Warning, TEXT("%s: StunnedTag was invalid, using default 'AI.State.Stunned'."), *GetName());
		}
		ApplyDefaultEffects(); 
	}
}

bool AEnemyBaseCharacter::IsDead() const
{
	return bIsDead;
}

float AEnemyBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsDead()) return 0.f;

	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.f && AttributeSet && AbilitySystemComponent)
	{
		const float OldHealth = AttributeSet->GetHealth();
		float NewHealth = OldHealth - ActualDamage; 
		NewHealth = FMath::Clamp(NewHealth, 0.0f, AttributeSet->GetMaxHealth());
		AttributeSet->SetHealth(NewHealth); 

		if (NewHealth <= 0.0f) 
		{
			HandleDeath();
		}
	}
	else if (ActualDamage > 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyBaseCharacter %s Took %.1f damage, but AttributeSet or ASC is missing!"), *GetName(), ActualDamage);
	}

	return ActualDamage;
}

void AEnemyBaseCharacter::HandleDeath()
{
	if (bIsDead) return;
	bIsDead = true;

	OnDeathDelegate.Broadcast();

	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr; 
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
		MontageEndedDelegate.BindUObject(this, &AEnemyBaseCharacter::OnDeathMontageEnded);
		AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, LoadedDeathMontage);
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
}

void AEnemyBaseCharacter::OnDeathMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Destroy(); 
}

void AEnemyBaseCharacter::ApplyDefaultEffects()
{
	if (!HasAuthority() || !AbilitySystemComponent) return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (const TSubclassOf<UGameplayEffect>& GameplayEffect : DefaultEffects)
	{
		if (GameplayEffect)
		{
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext); 
			if (SpecHandle.IsValid())
			{
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
}

void AEnemyBaseCharacter::SpawnAndAttachWeapon(const FName& InWeaponDataRowName, const FName& InAttachSocketName)
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
		if (GetMesh() && InAttachSocketName != NAME_None)
		{
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, InAttachSocketName);
		}
		else {
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
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s failed to spawn weapon actor from loaded class %s!"), *GetName(), *LoadedWeaponClass->GetName());
	}
}

