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
#include "Animation/AnimInstance.h" // Include for AnimInstance
#include "AI/AiBehaviorComponent.h" // 包含 AI 行为组件以便查找
#include "AI/EnemyAIController.h"   // 包含 AI 控制器以便通知 (如果需要)
#include "GameplayTagsManager.h" // Include for Gameplay Tags

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

    // --- 创建 AI 行为组件 ---
    AiBehaviorComponent = CreateDefaultSubobject<UAiBehaviorComponent>(TEXT("AiBehaviorComponent"));
    // -----------------------

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
    LoadedDeathMontage = nullptr; // Initialize death montage pointer
    bIsDead = false; // Initialize dead state
    bAttributesInitialized = false; // Initialize initialization flag
}

void AEnemyBaseCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 确保在服务器上执行属性初始化，并且只执行一次
    if (GetLocalRole() == ROLE_Authority && !bAttributesInitialized)
    {
        InitializeAttributesFromDataTable();
        // 注意：AiBehaviorComponent 的初始化现在在 InitializeAttributesFromDataTable 内部完成
    }
    // --- 移除这里的 AiBehaviorComponent 初始化逻辑，因为它移到了 InitializeAttributesFromDataTable 内部 ---
    /*
    if (AbilitySystemComponent && AttributeSet)
    {
        // ...
        if (AiBehaviorComponent)
        {
           // ... (Initialization logic removed) ...
        }
        // ...
    }
    */
    // -------------------------------------------------------------------------------------------------
}

void AEnemyBaseCharacter::InitializeAttributesFromDataTable()
{
    // --- 添加初始化检查 ---
    if (bAttributesInitialized)
    {
        // UE_LOG(LogTemp, Verbose, TEXT("EnemyBaseCharacter %s: Attributes already initialized."), *GetName()); // 可以用 Verbose 级别记录
        return;
    }
    // -----------------------

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
        // 保留警告
        UE_LOG(LogTemp, Warning, TEXT("Enemy %s: HitReactionMontage is not set in DataTable row '%s'."), *GetName(), *AttributeDataRowName.ToString());
    }

    // --- 加载并存储死亡蒙太奇 ---
    LoadedDeathMontage = Row->DeathMontage;
    if (!LoadedDeathMontage)
    {
        // 保留警告
        UE_LOG(LogTemp, Warning, TEXT("Enemy %s: DeathMontage is not set in DataTable row '%s'."), *GetName(), *AttributeDataRowName.ToString());
    }

    // 保留初始化完成日志
    UE_LOG(LogTemp, Log, TEXT("Enemy %s initialized attributes and montages from DataTable row '%s'."), *GetName(), *AttributeDataRowName.ToString());

    // --- 初始化 AI 行为组件 ---
    if (AiBehaviorComponent)
    {
        // 确保在属性加载后调用 InitializeBehavior
        AiBehaviorComponent->InitializeBehavior(this, *Row); // 传递自身指针和加载的数据行
        UE_LOG(LogTemp, Log, TEXT("Enemy %s initialized AiBehaviorComponent."), *GetName());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("EnemyBaseCharacter %s: AiBehaviorComponent is NULL! Cannot initialize AI behavior."), *GetName());
    }
    // --------------------------

    // --- 设置初始化标志位 ---
    bAttributesInitialized = true;
    // -----------------------

    UE_LOG(LogTemp, Log, TEXT("Enemy %s finished initializing attributes, montages, and AI behavior from DataTable row '%s'."), *GetName(), *AttributeDataRowName.ToString());

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

// --- 实现 GetAttributeSet ---
UEnemyAttributeSet* AEnemyBaseCharacter::GetAttributeSet() const
{
	return AttributeSet;
}
// --------------------------

UAnimMontage* AEnemyBaseCharacter::GetHitReactionMontage() const
{
    return LoadedHitReactionMontage;
}

bool AEnemyBaseCharacter::IsStunned() const
{
	// 检查 AbilitySystemComponent 是否有效以及是否拥有 StunnedTag
	return AbilitySystemComponent && AbilitySystemComponent->HasMatchingGameplayTag(StunnedTag);
}

// --- 实现受击处理函数 (BlueprintNativeEvent 的 C++ 部分) ---
void AEnemyBaseCharacter::HandleHitReaction_Implementation(AActor* DamageCauser)
{
	if (IsDead() || IsStunned()) // 如果已死亡或已处于受击状态，则不处理
	{
		return;
	}

	// 播放受击蒙太奇
	UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;
	if (AnimInstance && LoadedHitReactionMontage)
	{
		// 停止当前可能在播放的其他蒙太奇 (可选，取决于设计)
		// AnimInstance->Montage_Stop(0.1f);

		const float PlayRate = 1.0f;
		AnimInstance->Montage_Play(LoadedHitReactionMontage, PlayRate);
		UE_LOG(LogTemp, Verbose, TEXT("%s playing HitReactionMontage: %s"), *GetName(), *LoadedHitReactionMontage->GetName());

		// 可选：根据伤害来源调整朝向
		if (DamageCauser)
		{
			FVector DirectionToCauser = (DamageCauser->GetActorLocation() - GetActorLocation()).GetSafeNormal2D();
			FRotator LookAtRotation = DirectionToCauser.Rotation();
			// 可以平滑转向或立即设置
			SetActorRotation(LookAtRotation);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s cannot play HitReactionMontage. AnimInstance: %p, Montage: %p"),
			*GetName(), AnimInstance, LoadedHitReactionMontage.Get());
	}

	// 应用受击效果 (例如，施加 StunnedTag) - 这通常由伤害 GE 完成，但也可以在这里补充
	if (HitReactionEffect && AbilitySystemComponent)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(DamageCauser ? DamageCauser : this); // 设置伤害来源
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(HitReactionEffect, 1, EffectContext);
		if (SpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			UE_LOG(LogTemp, Verbose, TEXT("%s applied HitReactionEffect."), *GetName());
		}
	}
}
// ---------------------------------------------------------

void AEnemyBaseCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    
    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->InitAbilityActorInfo(this, this);

        // --- 初始化 StunnedTag ---
        // 确保 StunnedTag 有效，如果未在编辑器中设置，则使用默认值
        if (!StunnedTag.IsValid())
        {
            StunnedTag = FGameplayTag::RequestGameplayTag(FName("AI.State.Stunned"));
            UE_LOG(LogTemp, Warning, TEXT("%s: StunnedTag was invalid, using default 'AI.State.Stunned'."), *GetName());
        }
        // -------------------------

        GiveDefaultAbilities();
        ApplyDefaultEffects();
    }
}

bool AEnemyBaseCharacter::IsDead() const
{
    return bIsDead;
}

float AEnemyBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// --- 添加伤害免疫检查 (未来实现) ---
	// if (AbilitySystemComponent && AbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Player.State.DamageImmune"))))
	// {
	//     UE_LOG(LogTemp, Verbose, TEXT("%s is immune to damage."), *GetName());
	//     return 0.f;
	// }
	// ------------------------------------

	if (IsDead()) // 如果已死亡，不再接受伤害
	{
		return 0.f;
	}

	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.f && AttributeSet && AbilitySystemComponent)
	{
		// --- 注意：伤害计算和属性修改最好通过 GameplayEffect 处理 ---
		// 这里的直接修改仅作为示例，推荐使用 GE 来应用伤害和触发后续效果
		const float OldHealth = AttributeSet->GetHealth();
		float NewHealth = OldHealth - ActualDamage; // 简化计算，未考虑防御等
		NewHealth = FMath::Clamp(NewHealth, 0.0f, AttributeSet->GetMaxHealth());
		AttributeSet->SetHealth(NewHealth); // 直接设置属性

		UE_LOG(LogTemp, Log, TEXT("%s Took %.1f damage. Health changed from %.1f to %.1f"), *GetName(), ActualDamage, OldHealth, NewHealth);

		// --- 触发受击事件标签 ---
		FGameplayEventData Payload;
		Payload.Instigator = EventInstigator ? EventInstigator : GetController();
		Payload.Target = this;
		Payload.EventMagnitude = ActualDamage;
		Payload.OptionalObject = DamageCauser;
		// 如果需要传递伤害类型，可以考虑使用 OptionalObject2 或 ContextHandle
		// Payload.OptionalObject2 = DamageEvent.DamageTypeClass; // 示例

		AbilitySystemComponent->HandleGameplayEvent(FGameplayTag::RequestGameplayTag(FName("Event.Damage.HitReact")), &Payload);
		UE_LOG(LogTemp, Verbose, TEXT("%s sent GameplayEvent 'Event.Damage.HitReact'"), *GetName());
		// ------------------------

		// 检查是否死亡
		if (NewHealth <= 0.0f)
		{
			HandleDeath();
		}
		// --- 移除这里的 HandleHitReaction 调用，改为由 GE 或 GameplayEvent 触发 ---
		// else
		// {
		//     HandleHitReaction(DamageCauser); // 处理受击反应
		// }
		// --------------------------------------------------------------------
	}
	else if (ActualDamage > 0.f)
	{
		// 保留重要警告
		UE_LOG(LogTemp, Warning, TEXT("EnemyBaseCharacter %s Took %.1f damage, but AttributeSet or ASC is missing!"), *GetName(), ActualDamage);
	}

	return ActualDamage;
}

void AEnemyBaseCharacter::HandleDeath()
{
	if (bIsDead) // 防止重复执行
	{
		return;
	}
	bIsDead = true;
	UE_LOG(LogTemp, Log, TEXT("EnemyBaseCharacter %s is handling death."), *GetName());

	// --- 广播死亡委托 ---
	OnDeathDelegate.Broadcast();
	// --------------------

	// 停止移动
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
		GetCharacterMovement()->SetComponentTickEnabled(false);
	}

	// 禁用碰撞 (保留查询以便可能的交互，例如拾取)
	if (UCapsuleComponent* CapsuleComp = GetCapsuleComponent())
	{
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 完全禁用碰撞
		CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
	if (GetMesh())
	{
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 确保骨骼网格体也无碰撞
	}


	// 播放死亡蒙太奇
	UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;
	if (AnimInstance && LoadedDeathMontage)
	{
		const float PlayRate = 1.0f;
		AnimInstance->Montage_Play(LoadedDeathMontage, PlayRate);
		// 绑定蒙太奇结束事件
		FOnMontageEnded MontageEndedDelegate;
		MontageEndedDelegate.BindUObject(this, &AEnemyBaseCharacter::OnDeathMontageEnded);
		AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, LoadedDeathMontage);
		// 可以保留播放蒙太奇的日志，或改为 Verbose
		UE_LOG(LogTemp, Log, TEXT("  Playing Death Montage: %s"), *LoadedDeathMontage->GetName());
	}
	else
	{
		// 保留重要警告
		UE_LOG(LogTemp, Warning, TEXT("  Cannot play death montage: AnimInstance (%p) or LoadedDeathMontage (%p) is invalid."), AnimInstance, LoadedDeathMontage.Get());
		SetLifeSpan(3.0f); 
	}

	// 可选：取消所有激活的能力
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAllAbilities();
	}

	// 可选：通知 AI 控制器角色已死亡
	// AAIController* AIController = Cast<AAIController>(GetController());
	// if (AIController) { // ... 通知逻辑 ... }
}

void AEnemyBaseCharacter::OnDeathMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// 保留蒙太奇结束和销毁日志
	UE_LOG(LogTemp, Log, TEXT("EnemyBaseCharacter %s death montage ended (Interrupted: %s). Destroying Actor."), *GetName(), bInterrupted ? TEXT("Yes") : TEXT("No"));
	Destroy();
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

