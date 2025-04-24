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
#include "UObject/UObjectGlobals.h" 
#include "GameplayTagContainer.h" 
#include "GameFramework/GameMode.h" // 包含 GameMode 而不是 GameModeBase
#include "Kismet/GameplayStatics.h" // 包含 GameplayStatics

AAnabiosisOriginCharacter::AAnabiosisOriginCharacter()
{
	// 设置胶囊体大小
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// 配置控制器旋转
	bUseControllerRotationPitch = false; // 不使用控制器 Pitch 旋转
	bUseControllerRotationYaw = false;   // 不使用控制器 Yaw 旋转
	bUseControllerRotationRoll = false;  // 不使用控制器 Roll 旋转

	// 配置角色移动
	GetCharacterMovement()->bOrientRotationToMovement = true; // 角色朝向移动方向
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // 旋转速率

	// 配置跳跃和空中控制
	GetCharacterMovement()->JumpZVelocity = 700.f; // 跳跃 Z 轴速度
	GetCharacterMovement()->AirControl = 0.35f; // 空中控制力

	// 配置行走速度和减速
	GetCharacterMovement()->MaxWalkSpeed = 500.f; // 最大行走速度
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f; // 最小模拟行走速度
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; // 行走制动减速度
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f; // 下落制动减速度

	// 创建相机臂组件
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent); // 附加到根组件
	CameraBoom->TargetArmLength = 400.0f; // 相机臂长度
	CameraBoom->bUsePawnControlRotation = true; // 使用 Pawn 的控制旋转

	// 创建跟随相机
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // 附加到相机臂
	FollowCamera->bUsePawnControlRotation = false; // 不使用 Pawn 的控制旋转

	// 创建 GAS 组件
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent")); // 能力系统组件
	AttributeSet = CreateDefaultSubobject<UAnabiosisAttributeSet>(TEXT("AttributeSet")); // 属性集

	// 初始化数据表和状态变量
	AttributeDataTable = nullptr; // 属性数据表指针
	AttributeDataRowName = NAME_None; // 属性数据表行名
	WeaponAttributeDataTable = nullptr; // 武器属性数据表指针
	CurrentWeapon = nullptr; // 当前武器指针
	CurrentClass = EAnabiosisPlayerClass::Warrior; // 默认职业为战士
	LoadedDeathMontage = nullptr; // 加载的死亡蒙太奇指针
	bIsDead = false; // 初始状态为未死亡
	HitReactionMontage = nullptr; // 受击反应蒙太奇指针
}

void AAnabiosisOriginCharacter::BeginPlay()
{
	Super::BeginPlay();
	BindAttributeChangeListeners(); // 绑定属性变化监听器
	// 数据加载应在 PostInitializeComponents 或基于游戏事件进行
}

UAbilitySystemComponent* AAnabiosisOriginCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent; // 返回能力系统组件
}

void AAnabiosisOriginCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this); // 初始化 ASC 的 ActorInfo
		// 属性应在 PostInitializeComponents 中初始化
		GiveDefaultAbilities(); // 赋予默认能力
		BindAttributeChangeListeners(); // 绑定属性变化监听器
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: 在 PossessedBy 期间 AbilitySystemComponent 为空！"), *GetName());
	}
}

void AAnabiosisOriginCharacter::GiveDefaultAbilities()
{
	// 仅在服务器端执行，且 ASC 和 AttributeSet 有效
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || !AttributeSet)
	{
		return;
	}

	// 遍历默认能力列表并赋予能力
	for (const TSubclassOf<UGameplayAbility>& Ability : DefaultAbilities)
	{
		if (Ability)
		{
			// 赋予能力，等级为 1，输入 ID 无效，源对象为自身
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
		}
	}
}

void AAnabiosisOriginCharacter::SetPlayerClass(EAnabiosisPlayerClass NewClass)
{
	// 仅在服务器端执行，且新职业与当前职业不同
	if (GetLocalRole() == ROLE_Authority && CurrentClass != NewClass)
	{
		CurrentClass = NewClass; // 更新当前职业
		UpdateAttributesForClass(); // 根据新职业更新属性
	}
}

void AAnabiosisOriginCharacter::UpdateAttributesForClass()
{
	// 根据新职业从数据表重新加载属性
	InitializeAttributesFromDataTable();
}

void AAnabiosisOriginCharacter::SetCharacterRotationMode(bool bOrientToMovement, bool bUseControllerRotation)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bOrientRotationToMovement = bOrientToMovement; // 设置是否朝向移动方向
	}
	bUseControllerRotationYaw = bUseControllerRotation; // 设置是否使用控制器 Yaw 旋转
}

void AAnabiosisOriginCharacter::SetAttackAbilityTag(const FGameplayTag& NewTag)
{
	if (!AbilitySystemComponent) return; // ASC 无效则返回

	// 如果当前攻击标签有效，则移除旧标签
	if (AttackAbilityTag.IsValid())
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(AttackAbilityTag);
	}
	
	AttackAbilityTag = NewTag; // 设置新标签
	// 如果新标签有效，则添加新标签
	if (AttackAbilityTag.IsValid())
	{
		AbilitySystemComponent->AddLooseGameplayTag(AttackAbilityTag);
	}
}

void AAnabiosisOriginCharacter::RefreshAbilityBindings()
{
	// 此函数的目的不明确且可能存在问题。
	// 移除并重新添加标签可能不是刷新绑定的预期方式。
	// 考虑使用输入映射上下文和 GAS 输入绑定以获得更清晰的方法。
	UE_LOG(LogTemp, Warning, TEXT("调用了 RefreshAbilityBindings。请检查其逻辑并考虑替代方案。"));
	if (!AbilitySystemComponent) return; // ASC 无效则返回
	
	// 重新添加当前攻击标签的示例：
	if (AttackAbilityTag.IsValid())
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(AttackAbilityTag);
		AbilitySystemComponent->AddLooseGameplayTag(AttackAbilityTag);
	}
}

bool AAnabiosisOriginCharacter::IsDead() const
{
	return bIsDead; // 返回是否死亡状态
}

void AAnabiosisOriginCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// 仅在服务器端初始化属性
	if (GetLocalRole() == ROLE_Authority)
	{
		InitializeAttributesFromDataTable();
	}
	// 客户端也需要绑定监听器
	// BindAttributeChangeListeners(); // 移动到 BeginPlay/PossessedBy
}

void AAnabiosisOriginCharacter::InitializeAttributesFromDataTable()
{
	// 检查前置条件是否满足
	if (!AttributeDataTable || AttributeDataRowName == NAME_None || !AttributeSet || !AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: 初始化前检查失败 (数据表、行名、属性集或 ASC 缺失)。"), *GetName());
		return;
	}
	// 确保 AttributeSet 是正确的类型
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
		UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: 在属性数据表 '%s' 中找不到行 '%s'！"), *GetName(), *AttributeDataRowName.ToString(), *AttributeDataTable->GetName());
		return;
	}

	// 使用 ASC 设置基础值，使用 AttributeSet 设置当前值
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetHealthAttribute(), Row->Health);
	PlayerAttributeSet->SetHealth(Row->Health); // 设置当前生命值
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetMaxHealthAttribute(), Row->MaxHealth);
	PlayerAttributeSet->SetMaxHealth(Row->MaxHealth); // 设置最大生命值
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetManaAttribute(), Row->Mana);
	PlayerAttributeSet->SetMana(Row->Mana); // 设置当前法力值
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetMaxManaAttribute(), Row->MaxMana);
	PlayerAttributeSet->SetMaxMana(Row->MaxMana); // 设置最大法力值
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetStrengthAttribute(), Row->Strength);
	PlayerAttributeSet->SetStrength(Row->Strength); // 设置力量
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetAgilityAttribute(), Row->Agility);
	PlayerAttributeSet->SetAgility(Row->Agility); // 设置敏捷
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetConstitutionAttribute(), Row->Constitution);
	PlayerAttributeSet->SetConstitution(Row->Constitution); // 设置体质
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetIntelligenceAttribute(), Row->Intelligence);
	PlayerAttributeSet->SetIntelligence(Row->Intelligence); // 设置智力
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetAttackPowerAttribute(), Row->AttackPower);
	PlayerAttributeSet->SetAttackPower(Row->AttackPower); // 设置攻击力
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetDefenseAttribute(), Row->Defense);
	PlayerAttributeSet->SetDefense(Row->Defense); // 设置防御力
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetCriticalChanceAttribute(), Row->CriticalChance);
	PlayerAttributeSet->SetCriticalChance(Row->CriticalChance); // 设置暴击率
	AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetCriticalMultiplierAttribute(), Row->CriticalMultiplier);
	PlayerAttributeSet->SetCriticalMultiplier(Row->CriticalMultiplier); // 设置暴击倍率

	// 加载蒙太奇
	HitReactionMontage = Row->HitReactionMontage; // 加载受击反应蒙太奇
	if (!HitReactionMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("玩家 %s: 在数据表行 '%s' 中未设置 HitReactionMontage。"), *GetName(), *AttributeDataRowName.ToString());
	}
	LoadedDeathMontage = Row->DeathMontage; // 加载死亡蒙太奇
	if (!LoadedDeathMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("玩家 %s: 在数据表行 '%s' 中未设置 DeathMontage。"), *GetName(), *AttributeDataRowName.ToString());
	}

	// 生成武器 (仅服务器)
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

	// 检查武器数据表和行名是否有效
	if (!WeaponAttributeDataTable || InWeaponDataRowName == NAME_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: 未设置 WeaponAttributeDataTable 或 WeaponDataRowName 为 None。无法生成武器。"), *GetName());
		return;
	}
	 // 检查附加插槽名是否有效
	 if (InAttachSocketName == NAME_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: WeaponAttachSocketName 为 None。无法正确附加武器。"), *GetName());
	}

	// 从武器数据表查找行数据
	const FString ContextString(TEXT("加载武器属性"));
	FWeaponAttributeData* WeaponRow = WeaponAttributeDataTable->FindRow<FWeaponAttributeData>(InWeaponDataRowName, ContextString);
	if (!WeaponRow)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: 在武器数据表 '%s' 中找不到行 '%s'！"), *GetName(), *InWeaponDataRowName.ToString(), *WeaponAttributeDataTable->GetName());
		return;
	}

	// 检查武器 Actor 类指针是否有效
	if (WeaponRow->WeaponActorClassPtr.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("%s: 在武器属性数据行 '%s' 中未设置 WeaponActorClassPtr！"), *GetName(), *InWeaponDataRowName.ToString());
		return;
	}

	// 同步加载武器 Actor 类
	TSubclassOf<AWeaponBase> LoadedWeaponClass = WeaponRow->WeaponActorClassPtr.LoadSynchronous();
	if (!LoadedWeaponClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: 从路径 %s 加载行 '%s' 中的 WeaponActorClassPtr 失败！"), *GetName(), *WeaponRow->WeaponActorClassPtr.ToString(), *InWeaponDataRowName.ToString());
		return;
	}

	// 获取世界场景
	UWorld* World = GetWorld();
	if (!World) return;

	// 设置生成参数
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this; // 设置拥有者
	SpawnParams.Instigator = GetInstigator(); // 设置煽动者
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // 总是生成，忽略碰撞

	// 生成武器 Actor
	CurrentWeapon = World->SpawnActor<AWeaponBase>(LoadedWeaponClass, GetActorLocation(), GetActorRotation(), SpawnParams);

	if (CurrentWeapon) // 如果武器生成成功
	{
		// 附加武器到骨骼网格
		if (GetMesh() && InAttachSocketName != NAME_None) // 确保骨骼网格和插槽名有效
		{
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, InAttachSocketName);
		} else {
			 UE_LOG(LogTemp, Warning, TEXT("  无法附加 %s。骨骼网格无效或 SocketName 为 None。"), *CurrentWeapon->GetName());
		}

		// 应用武器赋予的属性效果
		if (WeaponRow->GrantedAttributesEffect && AbilitySystemComponent)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext(); // 创建效果上下文
			EffectContext.AddSourceObject(CurrentWeapon); // 添加源对象
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(WeaponRow->GrantedAttributesEffect, 1, EffectContext); // 创建效果规格
			if (SpecHandle.IsValid()) // 如果规格有效
			{
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get()); // 应用效果到自身
			}
		}

		// 设置初始攻击标签
		if (WeaponRow->InitialAttackTag.IsValid())
		{
			SetAttackAbilityTag(WeaponRow->InitialAttackTag); // 设置攻击标签
		}
	}
	 else // 武器生成失败
	{
		UE_LOG(LogTemp, Error, TEXT("%s 从加载的类 %s 生成武器 Actor 失败！"), *GetName(), *LoadedWeaponClass->GetName());
	}
}

void AAnabiosisOriginCharacter::BindAttributeChangeListeners()
{
	// 确保 ASC 和 AttributeSet 有效
	if (AbilitySystemComponent && AttributeSet)
	{
		// 确保 AttributeSet 是正确的类型
		const UAnabiosisAttributeSet* PlayerAttributeSet = Cast<const UAnabiosisAttributeSet>(AttributeSet);
		if (PlayerAttributeSet)
		{
			// 绑定生命值变化委托到 OnHealthAttributeChanged 函数
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetHealthAttribute()).AddUObject(this, &AAnabiosisOriginCharacter::OnHealthAttributeChanged);
			// 可以为其他属性添加更多绑定...
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("BindAttributeChangeListeners: %s 的 AttributeSet 不是 UAnabiosisAttributeSet"), *GetName());
		}
	}
}

void AAnabiosisOriginCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	// 如果角色未死亡，且新生命值小于等于 0，且旧生命值大于 0
	if (!bIsDead && Data.NewValue <= 0.0f && Data.OldValue > 0.0f) 
	{
		HandleDeath(); // 处理死亡逻辑
	}
}

void AAnabiosisOriginCharacter::HandleDeath()
{
	if (bIsDead) return; // 如果已经死亡，则返回
	bIsDead = true; // 标记为已死亡

	// 销毁当前武器
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr; 
	}

	// 停止并禁用移动
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately(); // 立即停止移动
		GetCharacterMovement()->DisableMovement(); // 禁用移动模式
		GetCharacterMovement()->SetComponentTickEnabled(false); // 禁用移动组件 Tick
	}

	// 禁用碰撞
	if (UCapsuleComponent* CapsuleComp = GetCapsuleComponent())
	{
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 禁用胶囊体碰撞
		CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore); // 对所有通道设置为忽略
	}
	if (GetMesh())
	{
		// 保留网格碰撞用于布娃娃或效果（如果需要），但禁用 Pawn 碰撞
		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll")); // 示例配置，根据需要调整
		GetMesh()->SetSimulatePhysics(true); // 可选：启用布娃娃效果
	}

	// 取消所有能力
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAllAbilities(); // 取消所有激活的能力
	}

	// 禁用输入
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		DisableInput(PC); // 禁用玩家控制器输入
	}

	// 播放死亡蒙太奇
	UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr; // 获取动画实例
	if (AnimInstance && LoadedDeathMontage) // 如果动画实例和死亡蒙太奇都有效
	{
		const float PlayRate = 1.0f; // 播放速率
		AnimInstance->Montage_Play(LoadedDeathMontage, PlayRate); // 播放死亡蒙太奇
		FOnMontageEnded MontageEndedDelegate; // 创建蒙太奇结束委托
		MontageEndedDelegate.BindUObject(this, &AAnabiosisOriginCharacter::OnDeathMontageEnded); // 绑定到 OnDeathMontageEnded 函数
		AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, LoadedDeathMontage); // 设置蒙太奇结束委托
	}
	else // 无法播放蒙太奇
	{
		UE_LOG(LogTemp, Warning, TEXT("  无法播放死亡蒙太奇：AnimInstance (%p) 或 LoadedDeathMontage (%p) 无效。立即结束比赛。"), AnimInstance, LoadedDeathMontage.Get());
		// 如果没有蒙太奇，立即结束游戏
		AGameMode* GameMode = Cast<AGameMode>(UGameplayStatics::GetGameMode(this)); // 获取游戏模式并转换为 AGameMode
		if (GameMode)
		{
			GameMode->EndMatch(); // 结束比赛
		}
	}
}

void AAnabiosisOriginCharacter::OnDeathMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// 获取游戏模式并结束比赛
	AGameMode* GameMode = Cast<AGameMode>(UGameplayStatics::GetGameMode(this)); // 获取游戏模式并转换为 AGameMode
	if (GameMode)
	{
		GameMode->EndMatch(); // 结束比赛
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("在 %s 的 OnDeathMontageEnded 中获取 GameMode 失败。"), *GetName());
	}

	// 不要在此处销毁 Actor；让 GameMode 处理清理或关卡转换。
}
