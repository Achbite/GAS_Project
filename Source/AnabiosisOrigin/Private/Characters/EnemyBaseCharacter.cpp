/* 
 * Copyright (C) 2024 [Wang] 
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
* 功能描述：
* - 实现AI敌人基础功能
* - 初始化属性和能力系统
* - 处理AI行为逻辑
*/

#include "Characters/EnemyBaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "Attributes/EnemyAttributeSet.h" // 确保包含属性集头文件
#include "Data/EnemyAttributeData.h"    // 包含敌人属性数据结构头文件
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/CollisionProfile.h"
#include "Animation/AnimMontage.h" // Include AnimMontage
#include "GameFramework/Controller.h" // Include Controller for TakeDamage override
#include "Engine/DamageEvents.h"    // Include DamageEvents for TakeDamage override
#include "Components/SkeletalMeshComponent.h" // 包含骨骼网格体组件头文件

#define COLLISION_ENEMY ECC_GameTraceChannel1

AEnemyBaseCharacter::AEnemyBaseCharacter()
{
    // 禁用玩家控制器的旋转
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // 配置移动组件
    UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
    if (MovementComponent)
    {
        MovementComponent->bOrientRotationToMovement = true;
        MovementComponent->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    }

    // 初始化能力系统组件 (移除复制设置)
    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

    // 创建属性集
    AttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("AttributeSet"));

    // 设置胶囊体碰撞
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

    // 禁用骨骼网格体的碰撞
    USkeletalMeshComponent* MeshComp = GetMesh();
    if (MeshComp)
    {
        MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 完全禁用碰撞
        MeshComp->SetCollisionObjectType(ECC_WorldStatic); // 可以设为不影响物理的类型
        MeshComp->SetCollisionResponseToAllChannels(ECR_Ignore); // 忽略所有通道
    }

    // 设置数据表和行名默认值 (可选)
    AttributeDataTable = nullptr;
    AttributeDataRowName = NAME_None;

    LoadedHitReactionMontage = nullptr; // Initialize the pointer
}

void AEnemyBaseCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 确保在服务器上执行属性初始化
    if (GetLocalRole() == ROLE_Authority)
    {
        InitializeAttributesFromDataTable();
    }
    // 注意：如果属性需要在客户端上也立即反映（例如用于UI），可能需要RPC或复制机制
}

void AEnemyBaseCharacter::InitializeAttributesFromDataTable()
{
    if (!AttributeDataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("EnemyBaseCharacter %s: AttributeDataTable is not set!"), *GetName());
        return;
    }
    if (AttributeDataRowName == NAME_None)
    {
        UE_LOG(LogTemp, Error, TEXT("EnemyBaseCharacter %s: AttributeDataRowName is not set!"), *GetName());
        return;
    }
    if (!AttributeSet)
    {
         UE_LOG(LogTemp, Error, TEXT("EnemyBaseCharacter %s: AttributeSet is NULL! Cannot initialize attributes."), *GetName());
        return;       
    }
     if (!AbilitySystemComponent)
    {
         UE_LOG(LogTemp, Error, TEXT("EnemyBaseCharacter %s: AbilitySystemComponent is NULL! Cannot initialize attributes."), *GetName());
        return;       
    }

    const FString ContextString(TEXT("Loading Enemy Attributes"));
    FEnemyAttributeData* Row = AttributeDataTable->FindRow<FEnemyAttributeData>(AttributeDataRowName, ContextString);

    if (!Row)
    {
        UE_LOG(LogTemp, Error, TEXT("EnemyBaseCharacter %s: Cannot find row '%s' in AttributeDataTable '%s'!"), *GetName(), *AttributeDataRowName.ToString(), *AttributeDataTable->GetName());
        return;
    }

    // --- 应用加载的属性到 AttributeSet ---
    // 使用 AbilitySystemComponent 初始化基础属性值
    // 这会触发属性的元数据（如 Clamp）和相关计算（如 MaxHealth 基于 Constitution）
    
    // 示例：直接设置基础值 (如果你的 AttributeSet 这样设计)
    // AttributeSet->InitHealth(Row->InitialHealth);
    // AttributeSet->InitMaxHealth(Row->InitialMaxHealth);
    // AttributeSet->InitAttackPower(Row->AttackPower);
    // AttributeSet->InitDefense(Row->Defense);
    // ... 其他属性 ...

    // 或者，更好的方式是使用 GameplayEffect 来初始化属性
    // 创建一个临时的 GameplayEffect 或使用预定义的初始化 GE
    // 例如，假设你有一个 UPROPERTY 定义的 TSubclassOf<UGameplayEffect> InitStatsEffect;
    /*
    if (InitStatsEffect)
    {
        FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
        EffectContext.AddSourceObject(this);
        FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(InitStatsEffect, Row->Level, EffectContext);

        if (SpecHandle.IsValid())
        {
            // 使用 SetByCaller 修改 GameplayEffect 中的值
            SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Health.Initial")), Row->InitialHealth);
            SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.MaxHealth.Initial")), Row->InitialMaxHealth);
            SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.AttackPower.Initial")), Row->AttackPower);
            SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Defense.Initial")), Row->Defense);
            // ... 为其他需要从数据表初始化的属性添加 SetByCaller ...

            AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
            UE_LOG(LogTemp, Log, TEXT("Enemy %s initialized attributes from DataTable row '%s' using GE."), *GetName(), *AttributeDataRowName.ToString());
        }
    }
    else
    {
         UE_LOG(LogTemp, Warning, TEXT("EnemyBaseCharacter %s: InitStatsEffect is not set. Cannot initialize attributes via GameplayEffect."), *GetName());
         // 回退到直接设置 (如果实现了 Init 函数)
         AttributeSet->InitHealth(Row->InitialHealth);
         AttributeSet->InitMaxHealth(Row->InitialMaxHealth);
         // ...
    }
    */
    
    // --- 简化版：直接调用 AttributeSet 的初始化函数 (假设已实现) ---
    // 这要求你的 UEnemyAttributeSet 有类似 InitHealth, InitMaxHealth 的函数
    // 并且这些函数内部调用了对应的 SetBaseValue 和 SetCurrentValue
    AbilitySystemComponent->SetNumericAttributeBase(AttributeSet->GetHealthAttribute(), Row->InitialHealth);
    AttributeSet->SetHealth(Row->InitialHealth); // 同时设置当前值
    AbilitySystemComponent->SetNumericAttributeBase(AttributeSet->GetMaxHealthAttribute(), Row->InitialMaxHealth);
    AbilitySystemComponent->SetNumericAttributeBase(AttributeSet->GetAttackPowerAttribute(), Row->AttackPower);
    AbilitySystemComponent->SetNumericAttributeBase(AttributeSet->GetDefenseAttribute(), Row->Defense);
    // ... 初始化其他属性 ...

    // --- 加载并存储受击蒙太奇 ---
    LoadedHitReactionMontage = Row->HitReactionMontage;
    if (!LoadedHitReactionMontage)
    {
        UE_LOG(LogTemp, Warning, TEXT("Enemy %s: HitReactionMontage is not set in DataTable row '%s'."), *GetName(), *AttributeDataRowName.ToString());
    }

    UE_LOG(LogTemp, Log, TEXT("Enemy %s initialized attributes and montage from DataTable row '%s'."), *GetName(), *AttributeDataRowName.ToString());

    // 应用其他从数据表读取的配置，例如 AI 参数 (如果需要)
    // GetCharacterMovement()->MaxWalkSpeed = ... Row->MovementSpeed ... (如果数据表中有)
}

void AEnemyBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    // BeginPlay 也可以是初始化属性的地方，取决于依赖关系
    // if (GetLocalRole() == ROLE_Authority && !bAttributesInitialized) // 添加标志位避免重复初始化
    // {
    //     InitializeAttributesFromDataTable();
    //     bAttributesInitialized = true;
    // }
}

UAbilitySystemComponent* AEnemyBaseCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

UAnimMontage* AEnemyBaseCharacter::GetHitReactionMontage() const
{
    return LoadedHitReactionMontage;
}

void AEnemyBaseCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    
    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->InitAbilityActorInfo(this, this);
        GiveDefaultAbilities();
        ApplyDefaultEffects();
    }
}

float AEnemyBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 调用基类实现（可能触发蓝图事件等）
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.f && AttributeSet && AbilitySystemComponent)
	{
		// 直接修改 Health 属性
		// 注意：这种方式绕过了 GameplayEffect 的执行流程，可能不触发某些依赖 GE 的逻辑
		// 但对于简单的伤害扣血是可行的
		const float OldHealth = AttributeSet->GetHealth();
		float NewHealth = OldHealth - ActualDamage;

		// 使用 AttributeSet 的 Setter 来确保 Clamp 逻辑被调用（如果 PostGameplayEffectExecute 中有）
		// 或者直接 Clamp
		NewHealth = FMath::Clamp(NewHealth, 0.0f, AttributeSet->GetMaxHealth());
		AttributeSet->SetHealth(NewHealth); // 直接设置当前值

		// 可选：如果需要更新基础值（通常不直接在受伤时做）
		// AbilitySystemComponent->SetNumericAttributeBase(AttributeSet->GetHealthAttribute(), NewHealth);

		UE_LOG(LogTemp, Log, TEXT("EnemyBaseCharacter %s Took %.1f damage. Health changed from %.1f to %.1f"), *GetName(), ActualDamage, OldHealth, NewHealth);
	}
	else if (ActualDamage > 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyBaseCharacter %s Took %.1f damage, but AttributeSet or ASC is missing!"), *GetName(), ActualDamage);
	}

	return ActualDamage; // 返回实际受到的伤害
}

void AEnemyBaseCharacter::GiveDefaultAbilities()
{
    if (!HasAuthority() || !AbilitySystemComponent) return;

    for (TSubclassOf<UGameplayAbility>& Ability : DefaultAbilities)
    {
        if (Ability)
        {
            AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
        }
    }
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
            FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
            if (NewHandle.IsValid())
            {
                AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
            }
        }
    }
}
