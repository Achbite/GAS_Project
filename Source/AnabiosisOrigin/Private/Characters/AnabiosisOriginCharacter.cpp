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
* 功能描述： 实现玩家角色 AAnabiosisOriginCharacter 的逻辑。
*            负责初始化相机、移动、能力系统 (ASC)、属性集 (AttributeSet)，
*            从数据表加载属性、能力和动画蒙太奇，处理伤害、死亡逻辑，武器生成与附加，
*            以及角色旋转模式和攻击标签的管理。
* 结构：
* - 构造函数：设置默认组件值（胶囊体、移动、相机臂、相机）、创建 ASC 和属性集。
* - BeginPlay：绑定属性变化监听器。
* - GetAbilitySystemComponent, GetCameraBoom, GetFollowCamera, GetHitReactionMontage：访问器。
* - PossessedBy：初始化 ASC ActorInfo，授予默认能力，绑定监听器。
* - GiveDefaultAbilities：授予配置的默认 GameplayAbility。
* - SetPlayerClass, UpdateAttributesForClass：处理玩家职业切换及属性更新（当前实现为重新加载）。
* - SetCharacterRotationMode：设置角色是否朝向移动方向或使用控制器旋转。
* - SetAttackAbilityTag：设置当前的攻击能力标签（用于连击）。
* - RefreshAbilityBindings：刷新能力绑定（当前实现可能需要审查）。
* - IsDead：状态检查函数。
* - PostInitializeComponents：服务器上初始化属性。
* - InitializeAttributesFromDataTable：从数据表加载并应用属性、蒙太奇，生成武器。
* - SpawnAndAttachWeapon：根据数据表生成并附加武器 Actor，应用武器效果，设置初始攻击标签。
* - BindAttributeChangeListeners：绑定属性变化委托。
* - OnHealthAttributeChanged：生命值变化回调，检查死亡。
* - HandleDeath：处理死亡逻辑，销毁武器、停止移动、禁用碰撞、播放死亡动画、取消能力、禁用输入。
* - OnDeathMontageEnded：死亡动画结束回调，销毁 Actor。
*/

#include "Characters/AnabiosisOriginCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h"
#include "Attributes/AnabiosisAttributeSet.h"
#include "Data/AnabiosisAttributeData.h"
#include "Animation/AnimInstance.h"
#include "Engine/DataTable.h"
#include "Components/SkeletalMeshComponent.h"
#include "Items/WeaponBase.h"
#include "Data/WeaponAttributeData.h"
#include "UObject/UObjectGlobals.h" // 用于 FindObject
#include "GameplayTagContainer.h" // 用于 FGameplayTag
#include "Abilities/GameplayAbility.h" // 用于 TSubclassOf<UGameplayAbility>

AAnabiosisOriginCharacter::AAnabiosisOriginCharacter()
{
	// 配置胶囊体
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// 配置角色旋转（通常由控制器或战斗模式控制）
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 配置角色移动
	GetCharacterMovement()->bOrientRotationToMovement = true; // 默认朝向移动方向
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// 配置相机臂
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // 默认臂长
	CameraBoom->bUsePawnControlRotation = true; // 相机臂随控制器旋转

	// 配置跟随相机
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // 附加到相机臂末端
	FollowCamera->bUsePawnControlRotation = false; // 相机本身不随控制器旋转

	// 创建 GAS 组件
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UAnabiosisAttributeSet>(TEXT("AttributeSet"));

	// 初始化数据表和状态变量
	AttributeDataTable = nullptr;
	AttributeDataRowName = NAME_None;
	WeaponAttributeDataTable = nullptr;
	CurrentWeapon = nullptr;
	CurrentClass = EAnabiosisPlayerClass::Warrior; // 默认职业
	LoadedDeathMontage = nullptr;
	bIsDead = false;
	HitReactionMontage = nullptr;
}

void AAnabiosisOriginCharacter::BeginPlay()
{
	Super::BeginPlay();
	// 绑定属性变化监听器，用于处理生命值变化等
	BindAttributeChangeListeners();
	// 数据加载应在 PostInitializeComponents 或 PossessedBy 中处理
}

UAbilitySystemComponent* AAnabiosisOriginCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAnabiosisOriginCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 当被控制器控制时 (服务器和客户端都会调用)
	if (AbilitySystemComponent)
	{
		// 初始化 ASC 的 ActorInfo
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		// 授予默认能力 (仅服务器)
		GiveDefaultAbilities();
		// 绑定属性变化监听器 (客户端也需要监听以更新 UI 等)
		BindAttributeChangeListeners();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: 在 PossessedBy 期间 AbilitySystemComponent 为空！"), *GetName());
	}
}

void AAnabiosisOriginCharacter::GiveDefaultAbilities()
{
	// 仅在服务器上且 ASC 和属性集有效时执行
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || !AttributeSet)
	{
		return;
	}

	// 遍历默认能力列表并授予
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
	// 仅在服务器上且职业发生变化时执行
	if (GetLocalRole() == ROLE_Authority && CurrentClass != NewClass)
	{
		CurrentClass = NewClass;
		// 根据新职业更新属性（例如重新从数据表加载）
		UpdateAttributesForClass();
	}
}

void AAnabiosisOriginCharacter::UpdateAttributesForClass()
{
	// 重新从数据表加载属性以反映职业变化
	// 注意：这会覆盖当前的属性值，可能需要更精细的处理方式
	InitializeAttributesFromDataTable();
}

void AAnabiosisOriginCharacter::SetCharacterRotationMode(bool bOrientToMovement, bool bUseControllerRotation)
{
	// 设置角色移动组件是否朝向移动方向
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bOrientRotationToMovement = bOrientToMovement;
	}
	// 设置角色是否使用控制器的 Yaw 旋转
	bUseControllerRotationYaw = bUseControllerRotation;
}

void AAnabiosisOriginCharacter::SetAttackAbilityTag(const FGameplayTag& NewTag)
{
	if (!AbilitySystemComponent) return;

	// 移除旧的攻击标签（如果存在）
	if (AttackAbilityTag.IsValid())
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(AttackAbilityTag);
	}

	// 设置并添加新的攻击标签
	AttackAbilityTag = NewTag;
	if (AttackAbilityTag.IsValid())
	{
		AbilitySystemComponent->AddLooseGameplayTag(AttackAbilityTag);
	}
}

void AAnabiosisOriginCharacter::RefreshAbilityBindings()
{
	// 警告：此函数的目的和实现可能需要重新审视。
	// 移除并重新添加标签通常不是刷新 GAS 输入绑定的标准方法。
	// 考虑使用 Enhanced Input 和 GAS 的输入绑定机制。
	UE_LOG(LogTemp, Warning, TEXT("调用了 RefreshAbilityBindings。请检查其逻辑并考虑替代方案。"));
	if (!AbilitySystemComponent) return;

	// 示例：重新添加当前的攻击标签
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

	// 仅在服务器上初始化属性
	if (GetLocalRole() == ROLE_Authority)
	{
		InitializeAttributesFromDataTable();
	}
	// 客户端也需要绑定监听器
	// BindAttributeChangeListeners(); // 已移至 BeginPlay/PossessedBy
}

void AAnabiosisOriginCharacter::InitializeAttributesFromDataTable()
{
	// 检查必要的组件和数据表
	if (!AttributeDataTable || AttributeDataRowName == NAME_None || !AttributeSet || !AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: 初始化检查失败 (数据表、行名、属性集或 ASC 缺失)。"), *GetName());
		return;
	}
	// 确保属性集是玩家属性集类型
	UAnabiosisAttributeSet* PlayerAttributeSet = Cast<UAnabiosisAttributeSet>(AttributeSet);
	if (!PlayerAttributeSet)
	{
		UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: AttributeSet 不是 UAnabiosisAttributeSet！"), *GetName());
		return;
	}

	// 从数据表查找行数据
	const FString ContextString(TEXT("加载玩家属性"));
	const FAnabiosisAttributeData* Row = AttributeDataTable->FindRow<FAnabiosisAttributeData>(AttributeDataRowName, ContextString);
	if (!Row)
	{
		UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: 在属性数据表 '%s' 中找不到行 '%s'！"), *GetName(), *AttributeDataTable->GetName(), *AttributeDataRowName.ToString());
		return;
	}

	// 应用属性 (设置基础值和当前值)
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

	// 加载动画蒙太奇
	HitReactionMontage = Row->HitReactionMontage;
	if (!HitReactionMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("玩家 %s: 在数据表行 '%s' 中未设置 HitReactionMontage。"), *GetName(), *AttributeDataRowName.ToString());
	}
	LoadedDeathMontage = Row->DeathMontage;
	if (!LoadedDeathMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("玩家 %s: 在数据表行 '%s' 中未设置 DeathMontage。"), *GetName(), *AttributeDataRowName.ToString());
	}

	// 生成并附加武器 (仅服务器)
	if (GetLocalRole() == ROLE_Authority)
	{
		SpawnAndAttachWeapon(Row->WeaponDataRowName, Row->WeaponAttachSocketName);
	}
}

void AAnabiosisOriginCharacter::SpawnAndAttachWeapon(const FName& InWeaponDataRowName, const FName& InAttachSocketName)
{
	// 如果已有武器，先销毁
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}

	// 检查武器数据表和行名
	if (!WeaponAttributeDataTable || InWeaponDataRowName == NAME_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: WeaponAttributeDataTable 未设置或 WeaponDataRowName 为空。无法生成武器。"), *GetName());
		return;
	}
	 // 检查附加插槽名
	 if (InAttachSocketName == NAME_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: WeaponAttachSocketName 为空。无法正确附加武器。"), *GetName());
	}

	// 从武器数据表查找行数据
	const FString ContextString(TEXT("加载武器属性"));
	FWeaponAttributeData* WeaponRow = WeaponAttributeDataTable->FindRow<FWeaponAttributeData>(InWeaponDataRowName, ContextString);
	if (!WeaponRow)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: 在 WeaponAttributeDataTable '%s' 中找不到行 '%s'！"), *GetName(), *InWeaponDataRowName.ToString(), *WeaponAttributeDataTable->GetName());
		return;
	}

	// 检查武器 Actor 类指针
	if (WeaponRow->WeaponActorClassPtr.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("%s: 在 WeaponAttributeData 行 '%s' 中未设置 WeaponActorClassPtr！"), *GetName(), *InWeaponDataRowName.ToString());
		return;
	}

	// 同步加载武器 Actor 类
	TSubclassOf<AWeaponBase> LoadedWeaponClass = WeaponRow->WeaponActorClassPtr.LoadSynchronous();
	if (!LoadedWeaponClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: 从路径 %s 加载 WeaponActorClassPtr 失败 (行 '%s')！"), *GetName(), *WeaponRow->WeaponActorClassPtr.ToString(), *InWeaponDataRowName.ToString());
		return;
	}

	UWorld* World = GetWorld();
	if (!World) return;

	// 设置生成参数
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// 生成武器 Actor
	CurrentWeapon = World->SpawnActor<AWeaponBase>(LoadedWeaponClass, GetActorLocation(), GetActorRotation(), SpawnParams);

	if (CurrentWeapon)
	{
		// 附加武器到骨骼网格插槽
		if (GetMesh() && InAttachSocketName != NAME_None)
		{
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, InAttachSocketName);
		} else {
			 UE_LOG(LogTemp, Warning, TEXT("无法附加 %s。骨骼网格无效或 SocketName 为空。"), *CurrentWeapon->GetName());
		}

		// 应用武器授予的属性效果
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

		// 设置武器定义的初始攻击标签
		if (WeaponRow->InitialAttackTag.IsValid())
		{
			SetAttackAbilityTag(WeaponRow->InitialAttackTag);
		}
	}
	 else
	{
		UE_LOG(LogTemp, Error, TEXT("%s 生成武器 Actor 失败 (类 %s)！"), *GetName(), *LoadedWeaponClass->GetName());
	}
}

void AAnabiosisOriginCharacter::BindAttributeChangeListeners()
{
	// 确保 ASC 和属性集有效
	if (AbilitySystemComponent && AttributeSet)
	{
		// 确保是玩家属性集
		const UAnabiosisAttributeSet* PlayerAttributeSet = Cast<const UAnabiosisAttributeSet>(AttributeSet);
		if (PlayerAttributeSet)
		{
			// 绑定生命值变化委托
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetHealthAttribute()).AddUObject(this, &AAnabiosisOriginCharacter::OnHealthAttributeChanged);
			// 可以按需绑定其他属性的委托
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("BindAttributeChangeListeners: %s 的 AttributeSet 不是 UAnabiosisAttributeSet"), *GetName());
		}
	}
}

void AAnabiosisOriginCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	// 在生命值变化时调用
	// 如果未死亡且新生命值小于等于 0，则处理死亡
	if (!bIsDead && Data.NewValue <= 0.0f && Data.OldValue > 0.0f) // 检查 OldValue > 0 避免重复触发
	{
		HandleDeath();
	}
}

void AAnabiosisOriginCharacter::HandleDeath()
{
	if (bIsDead) return; // 防止重复处理
	bIsDead = true;

	// 销毁武器
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}

	// 停止移动并禁用移动组件
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
		GetCharacterMovement()->SetComponentTickEnabled(false);
	}

	// 禁用碰撞
	if (UCapsuleComponent* CapsuleComp = GetCapsuleComponent())
	{
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
	if (GetMesh())
	{
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// 播放死亡动画
	UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;
	if (AnimInstance && LoadedDeathMontage)
	{
		const float PlayRate = 1.0f;
		AnimInstance->Montage_Play(LoadedDeathMontage, PlayRate);
		// 绑定动画结束委托
		FOnMontageEnded MontageEndedDelegate;
		MontageEndedDelegate.BindUObject(this, &AAnabiosisOriginCharacter::OnDeathMontageEnded);
		AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, LoadedDeathMontage);
	}
	else
	{
		// 无动画则延迟销毁
		UE_LOG(LogTemp, Warning, TEXT("无法播放死亡蒙太奇: AnimInstance (%p) 或 LoadedDeathMontage (%p) 无效。将在 3 秒后销毁。"), AnimInstance, LoadedDeathMontage.Get());
		SetLifeSpan(3.0f);
	}

	// 取消所有能力
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAllAbilities();
	}

	// 禁用玩家输入
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		DisableInput(PC);
	}
}

void AAnabiosisOriginCharacter::OnDeathMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// 死亡动画结束后销毁 Actor
	Destroy();
}
