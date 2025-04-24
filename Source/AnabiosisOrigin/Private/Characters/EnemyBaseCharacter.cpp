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
* 功能描述： 实现 AI 敌人基础角色 AEnemyBaseCharacter 的逻辑。
*            负责初始化能力系统 (ASC)、属性集 (AttributeSet)、AI 行为组件 (AiBehaviorComponent)，
*            从数据表加载属性、能力和动画蒙太奇，处理伤害和死亡逻辑，以及武器的生成和附加。
* 结构：
* - 构造函数：设置默认组件值、碰撞配置。
* - PostInitializeComponents：在组件初始化后，如果是服务器，则从数据表加载属性。
* - BeginPlay：基类实现。
* - InitializeAttributesFromDataTable：从数据表加载并应用属性、蒙太奇、能力，初始化 AI 行为。
* - GetAbilitySystemComponent, GetAttributeSet, GetHitReactionMontage：访问器函数。
* - IsStunned, IsDead：状态检查函数。
* - HandleHitReaction_Implementation：受击反应的 C++ 实现（可被蓝图覆盖）。
* - PossessedBy：初始化 ASC ActorInfo，应用默认效果。
* - TakeDamage：处理接收到的伤害，更新生命值属性，检查死亡。
* - HandleDeath：处理死亡逻辑，停止移动、禁用碰撞、播放死亡动画、销毁武器、取消能力。
* - OnDeathMontageEnded：死亡动画结束后的回调，销毁 Actor。
* - ApplyDefaultEffects：应用配置的默认 GameplayEffect。
* - SpawnAndAttachWeapon：根据数据表生成并附加武器 Actor。
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
#include "GameplayTagsManager.h" // 用于 RequestGameplayTag
#include "Abilities/GameplayAbility.h"
#include "Items/WeaponBase.h"
#include "Data/WeaponAttributeData.h"
#include "Engine/DataTable.h"
#include "UObject/UObjectGlobals.h" // 用于 FindObject

#define COLLISION_ENEMY ECC_GameTraceChannel1 // 定义敌人碰撞通道

AEnemyBaseCharacter::AEnemyBaseCharacter()
{
	// 配置角色旋转和移动
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false; // AI 通常不直接使用控制器旋转 Yaw
	bUseControllerRotationRoll = false;

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent)
	{
		MovementComponent->bOrientRotationToMovement = true; // 使角色朝向移动方向
		MovementComponent->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // 设置旋转速率
	}

	// 创建 GAS 和 AI 相关组件
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("AttributeSet"));
	AiBehaviorComponent = CreateDefaultSubobject<UAiBehaviorComponent>(TEXT("AiBehaviorComponent"));

	// 配置胶囊体碰撞
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	if (Capsule)
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Capsule->SetCollisionObjectType(ECC_Pawn);
		Capsule->SetCollisionResponseToAllChannels(ECR_Block);
		Capsule->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore); // 忽略可见性检测
		Capsule->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);    // 忽略相机碰撞
		Capsule->SetCollisionResponseToChannel(COLLISION_ENEMY, ECR_Block); // 与其他敌人碰撞
	}

	// 配置骨骼网格碰撞 (通常 AI 的主要碰撞由胶囊体处理)
	USkeletalMeshComponent* MeshComp = GetMesh();
	if (MeshComp)
	{
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 通常不启用网格碰撞
		// MeshComp->SetCollisionObjectType(ECC_WorldStatic);
		// MeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	}

	// 初始化数据表和状态变量
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

	// 仅在服务器上且未初始化时，从数据表加载属性
	if (GetLocalRole() == ROLE_Authority && !bAttributesInitialized)
	{
		InitializeAttributesFromDataTable();
	}
}

void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	// BeginPlay 中可以添加与游戏世界交互后的初始化逻辑
}

void AEnemyBaseCharacter::InitializeAttributesFromDataTable()
{
	if (bAttributesInitialized) return; // 防止重复初始化
	// 检查必要的组件和数据表是否有效
	if (!AttributeDataTable || AttributeDataRowName == NAME_None || !AttributeSet || !AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyBaseCharacter %s: 初始化检查失败 (数据表、行名、属性集或 ASC 缺失)。"), *GetName());
		return;
	}

	// 从数据表查找行数据
	const FString ContextString(TEXT("加载敌人属性"));
	FEnemyAttributeData* Row = AttributeDataTable->FindRow<FEnemyAttributeData>(AttributeDataRowName, ContextString);
	if (!Row)
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyBaseCharacter %s: 在属性数据表 '%s' 中找不到行 '%s'！"), *GetName(), *AttributeDataTable->GetName(), *AttributeDataRowName.ToString());
		return;
	}

	// 应用属性 (设置基础值，当前值由 AttributeSet 构造函数或后续 GE 处理)
	AbilitySystemComponent->SetNumericAttributeBase(AttributeSet->GetHealthAttribute(), Row->InitialHealth);
	AttributeSet->SetHealth(Row->InitialHealth); // 同时设置当前值以确保初始状态正确
	AbilitySystemComponent->SetNumericAttributeBase(AttributeSet->GetMaxHealthAttribute(), Row->InitialMaxHealth);
	AbilitySystemComponent->SetNumericAttributeBase(AttributeSet->GetAttackPowerAttribute(), Row->AttackPower);
	AbilitySystemComponent->SetNumericAttributeBase(AttributeSet->GetDefenseAttribute(), Row->Defense);
	// 注意：DetectionRange 等 AI 相关属性由 AiBehaviorComponent 处理

	// 加载动画蒙太奇
	LoadedHitReactionMontage = Row->HitReactionMontage;
	if (!LoadedHitReactionMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("敌人 %s: 在数据表行 '%s' 中未设置 HitReactionMontage。"), *GetName(), *AttributeDataRowName.ToString());
	}
	LoadedDeathMontage = Row->DeathMontage;
	if (!LoadedDeathMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("敌人 %s: 在数据表行 '%s' 中未设置 DeathMontage。"), *GetName(), *AttributeDataRowName.ToString());
	}

	// 授予能力 (仅服务器)
	if (HasAuthority())
	{
		for (const TSubclassOf<UGameplayAbility>& AbilityClass : Row->GrantedAbilities)
		{
			if (AbilityClass)
			{
				// 创建能力规格并授予
				FGameplayAbilitySpec AbilitySpec(AbilityClass, 1, INDEX_NONE, this);
				AbilitySystemComponent->GiveAbility(AbilitySpec);
			}
		}
	}

	// 初始化 AI 行为组件
	if (AiBehaviorComponent)
	{
		AiBehaviorComponent->InitializeBehavior(this, *Row);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyBaseCharacter %s: AiBehaviorComponent 为空！无法初始化 AI 行为。"), *GetName());
	}

	bAttributesInitialized = true; // 标记为已初始化

	// 生成并附加武器 (仅服务器)
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
	// 返回从数据表加载的受击蒙太奇
	return LoadedHitReactionMontage;
}

bool AEnemyBaseCharacter::IsStunned() const
{
	// 检查是否拥有眩晕标签
	return AbilitySystemComponent && AbilitySystemComponent->HasMatchingGameplayTag(StunnedTag);
}

void AEnemyBaseCharacter::HandleHitReaction_Implementation(AActor* DamageCauser)
{
	// 默认的受击反应 C++ 实现。
	// 可以在蓝图中覆盖此函数以添加更复杂的逻辑，例如根据伤害来源播放不同的动画。
	// UE_LOG(LogTemp, Log, TEXT("%s HandleHitReaction_Implementation called."), *GetName());
}

void AEnemyBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 当被控制器控制时 (服务器和客户端都会调用)
	if (AbilitySystemComponent)
	{
		// 初始化 ASC 的 ActorInfo，将此 Character 设置为 Avatar 和 Owner
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		// 确保 StunnedTag 有效
		if (!StunnedTag.IsValid())
		{
			StunnedTag = FGameplayTag::RequestGameplayTag(FName("AI.State.Stunned"));
			UE_LOG(LogTemp, Warning, TEXT("%s: StunnedTag 无效，使用默认 'AI.State.Stunned'。"), *GetName());
		}
		// 应用默认效果 (例如，被动效果)
		ApplyDefaultEffects();
	}
}

bool AEnemyBaseCharacter::IsDead() const
{
	return bIsDead;
}

float AEnemyBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 如果已死亡，不受伤害
	if (IsDead()) return 0.f;

	// 调用父类的 TakeDamage 处理基础逻辑
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 如果实际造成了伤害，并且属性集和 ASC 有效
	if (ActualDamage > 0.f && AttributeSet && AbilitySystemComponent)
	{
		// 更新生命值属性
		const float OldHealth = AttributeSet->GetHealth();
		float NewHealth = OldHealth - ActualDamage;
		// Clamp 生命值在 [0, MaxHealth] 之间
		NewHealth = FMath::Clamp(NewHealth, 0.0f, AttributeSet->GetMaxHealth());
		AttributeSet->SetHealth(NewHealth); // 直接设置属性值

		// 检查是否死亡
		if (NewHealth <= 0.0f)
		{
			HandleDeath(); // 处理死亡逻辑
		}
	}
	else if (ActualDamage > 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyBaseCharacter %s 受到 %.1f 伤害，但 AttributeSet 或 ASC 缺失！"), *GetName(), ActualDamage);
	}

	return ActualDamage;
}

void AEnemyBaseCharacter::HandleDeath()
{
	if (bIsDead) return; // 防止重复处理
	bIsDead = true;

	// 广播死亡委托
	OnDeathDelegate.Broadcast();

	// 销毁当前武器
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
		// 绑定动画结束委托，在动画播放完毕后销毁 Actor
		FOnMontageEnded MontageEndedDelegate;
		MontageEndedDelegate.BindUObject(this, &AEnemyBaseCharacter::OnDeathMontageEnded);
		AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, LoadedDeathMontage);
	}
	else
	{
		// 如果没有动画或动画实例，则延迟销毁
		UE_LOG(LogTemp, Warning, TEXT("无法播放死亡蒙太奇: AnimInstance (%p) 或 LoadedDeathMontage (%p) 无效。将在 3 秒后销毁。"), AnimInstance, LoadedDeathMontage.Get());
		SetLifeSpan(3.0f);
	}

	// 取消所有正在进行的能力
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAllAbilities();
	}
}

void AEnemyBaseCharacter::OnDeathMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// 死亡动画播放完毕后销毁 Actor
	Destroy();
}

void AEnemyBaseCharacter::ApplyDefaultEffects()
{
	// 仅在服务器上且 ASC 有效时应用
	if (!HasAuthority() || !AbilitySystemComponent) return;

	// 创建效果上下文
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	// 遍历默认效果列表
	for (const TSubclassOf<UGameplayEffect>& GameplayEffect : DefaultEffects)
	{
		if (GameplayEffect)
		{
			// 创建效果规格并应用到自身
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
	// 如果已有武器，先销毁
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}

	// 检查武器数据表和行名是否有效
	if (!WeaponAttributeDataTable || InWeaponDataRowName == NAME_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: WeaponAttributeDataTable 未设置或 WeaponDataRowName 为空。无法生成武器。"), *GetName());
		return;
	}
	// 检查附加插槽名是否有效
	if (InAttachSocketName == NAME_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: WeaponAttachSocketName 为空。无法正确附加武器。"), *GetName());
	}

	// 从武器数据表查找行数据
	const FString ContextString(TEXT("加载武器属性"));
	FWeaponAttributeData* WeaponRow = WeaponAttributeDataTable->FindRow<FWeaponAttributeData>(InWeaponDataRowName, ContextString);
	if (!WeaponRow)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: 在 WeaponAttributeDataTable '%s' 中找不到行 '%s'！"), *GetName(), *WeaponAttributeDataTable->GetName(), *InWeaponDataRowName.ToString());
		return;
	}

	// 检查武器 Actor 类指针是否有效
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
	SpawnParams.Owner = this; // 设置拥有者
	SpawnParams.Instigator = GetInstigator(); // 设置煽动者
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // 始终生成，忽略碰撞

	// 生成武器 Actor
	CurrentWeapon = World->SpawnActor<AWeaponBase>(LoadedWeaponClass, GetActorLocation(), GetActorRotation(), SpawnParams);

	if (CurrentWeapon)
	{
		// 如果骨骼网格和插槽名有效，则附加武器到插槽
		if (GetMesh() && InAttachSocketName != NAME_None)
		{
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, InAttachSocketName);
		}
		else {
			 UE_LOG(LogTemp, Warning, TEXT("无法附加 %s。骨骼网格无效或 SocketName 为空。"), *CurrentWeapon->GetName());
		}

		// 如果武器数据中定义了授予属性的效果，则应用该效果
		if (WeaponRow->GrantedAttributesEffect && AbilitySystemComponent)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddSourceObject(CurrentWeapon); // 将武器设为效果源
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(WeaponRow->GrantedAttributesEffect, 1, EffectContext);
			if (SpecHandle.IsValid())
			{
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s 生成武器 Actor 失败 (类 %s)！"), *GetName(), *LoadedWeaponClass->GetName());
	}
}

