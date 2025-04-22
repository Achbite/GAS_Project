// Copyright Epic Games, Inc. All Rights Reserved.

/*
* 文件名: AnabiosisOriginCharacter.cpp
* 功能描述： 实现玩家角色基础功能，包括组件初始化、GAS 设置和属性加载。
*/

#include "Characters/AnabiosisOriginCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h" 
#include "Attributes/AnabiosisAttributeSet.h" 
#include "Data/AnabiosisAttributeData.h" 

AAnabiosisOriginCharacter::AAnabiosisOriginCharacter()
{
    // 碰撞胶囊体设置
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // 移动系统配置
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
    GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

    // 相机系统初始化
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // 能力系统组件初始化
    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AttributeSet = CreateDefaultSubobject<UAnabiosisAttributeSet>(TEXT("AttributeSet"));

    // 设置数据表和行名默认值
    AttributeDataTable = nullptr;
    AttributeDataRowName = NAME_None;
    CurrentClass = EAnabiosisPlayerClass::Warrior; // 设置默认职业
}

void AAnabiosisOriginCharacter::BeginPlay()
{
    Super::BeginPlay();
}

UAbilitySystemComponent* AAnabiosisOriginCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void AAnabiosisOriginCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    // 初始化 GAS ActorInfo (Owner 和 Avatar 都是 Character 自身)
    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->InitAbilityActorInfo(this, this); 
        
        // 属性应已在 PostInitializeComponents 中初始化
        // InitializeAttributesFromDataTable(); 
        
        GiveDefaultAbilities(); 
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: AbilitySystemComponent is NULL during PossessedBy!"), *GetName());
    }
}

void AAnabiosisOriginCharacter::GiveDefaultAbilities()
{
    // 仅在服务端执行
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
    // 仅在服务端执行
    if (GetLocalRole() == ROLE_Authority && CurrentClass != NewClass)
    {
        CurrentClass = NewClass;
        UpdateAttributesForClass();
    }
}

void AAnabiosisOriginCharacter::UpdateAttributesForClass()
{
    // 重新从数据表加载属性（可能需要根据 NewClass 查找不同的行）
    // 简化：假设 AttributeDataRowName 会被外部修改或逻辑处理
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

// Correct the class name here
void AAnabiosisOriginCharacter::SetAttackAbilityTag(const FGameplayTag& NewTag)
{
    if (!AbilitySystemComponent) return; // 检查 ASC

    // 移除旧标签 (如果有效)
    if (AttackAbilityTag.IsValid())
    {
        AbilitySystemComponent->RemoveLooseGameplayTag(AttackAbilityTag);
    }
    
    // 设置并添加新标签 (如果有效)
    AttackAbilityTag = NewTag;
    if (AttackAbilityTag.IsValid())
    {
        AbilitySystemComponent->AddLooseGameplayTag(AttackAbilityTag);
    }
}

void AAnabiosisOriginCharacter::RefreshAbilityBindings()
{
    // 这个函数的功能可能需要重新审视，它移除了所有标签再加回来，可能不是预期行为
    // 暂时保留，但标记为可能需要修改
    if (!AbilitySystemComponent)
    {
        return;
    }
    
    FGameplayTagContainer CurrentTags;
    AbilitySystemComponent->GetOwnedGameplayTags(CurrentTags);
    
    // 移除所有 Loose 标签
    AbilitySystemComponent->RemoveLooseGameplayTags(CurrentTags);
    
    // 重新添加 AttackAbilityTag (如果有效)
    if (AttackAbilityTag.IsValid())
    {
        AbilitySystemComponent->AddLooseGameplayTag(AttackAbilityTag);
    }
    
    // 重新添加其他标签 (这部分逻辑可能不正确，因为 CurrentTags 已经被移除了)
    // for (auto Tag : CurrentTags) 
    // {
    //     if (Tag != AttackAbilityTag)
    //     {
    //         AbilitySystemComponent->AddLooseGameplayTag(Tag);
    //     }
    // }
    
    // 刷新能力状态可能不是必要的，取决于具体需求
    // AbilitySystemComponent->NotifyAbilityEnded(FGameplayAbilitySpecHandle(), nullptr, false);
    UE_LOG(LogTemp, Warning, TEXT("RefreshAbilityBindings called. Review its logic if issues arise."));
}

void AAnabiosisOriginCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 仅在服务端初始化属性
    if (GetLocalRole() == ROLE_Authority)
    {
        InitializeAttributesFromDataTable();
    }
}

void AAnabiosisOriginCharacter::InitializeAttributesFromDataTable()
{
    if (!AttributeDataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: AttributeDataTable is not set!"), *GetName());
        return;
    }
    if (AttributeDataRowName == NAME_None)
    {
        UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: AttributeDataRowName is not set!"), *GetName());
        return;
    }
    if (!AttributeSet)
    {
        UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: AttributeSet is NULL!"), *GetName());
        return;       
    }
    UAnabiosisAttributeSet* PlayerAttributeSet = Cast<UAnabiosisAttributeSet>(AttributeSet); 
    if (!PlayerAttributeSet)
    {
        UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: AttributeSet is not UAnabiosisAttributeSet!"), *GetName()); 
        return;
    }
    if (!AbilitySystemComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: AbilitySystemComponent is NULL!"), *GetName());
        return;       
    }

    const FString ContextString(TEXT("Loading Player Attributes"));
    const FAnabiosisAttributeData* Row = AttributeDataTable->FindRow<FAnabiosisAttributeData>(AttributeDataRowName, ContextString);

    if (!Row)
    {
        UE_LOG(LogTemp, Error, TEXT("AnabiosisOriginCharacter %s: Cannot find row '%s' in AttributeDataTable '%s'!"), *GetName(), *AttributeDataRowName.ToString(), *AttributeDataTable->GetName());
        return;
    }

    // 使用 ASC 设置基础值，AttributeSet 设置当前值
    AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetHealthAttribute(), Row->Health);
    PlayerAttributeSet->SetHealth(Row->Health);
    AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetMaxHealthAttribute(), Row->MaxHealth);
    PlayerAttributeSet->SetMaxHealth(Row->MaxHealth); // 设置 MaxHealth 当前值
    AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetManaAttribute(), Row->Mana);
    PlayerAttributeSet->SetMana(Row->Mana);
    AbilitySystemComponent->SetNumericAttributeBase(PlayerAttributeSet->GetMaxManaAttribute(), Row->MaxMana);
    PlayerAttributeSet->SetMaxMana(Row->MaxMana); // 设置 MaxMana 当前值
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

    UE_LOG(LogTemp, Log, TEXT("Player %s initialized attributes from DataTable row '%s'."), *GetName(), *AttributeDataRowName.ToString());
}