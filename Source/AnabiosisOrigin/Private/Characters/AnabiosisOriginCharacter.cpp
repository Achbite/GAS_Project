// Copyright Epic Games, Inc. All Rights Reserved.

/*
* 文件名: AnabiosisOriginCharacter.cpp
* 功能描述：
* - 实现角色基础功能
* - 初始化角色组件
* - 处理能力系统交互
*
* 实现细节：
* - 组件初始化：设置默认属性和组件
* - 能力系统：配置和初始化GAS
*/

#include "Characters/AnabiosisOriginCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Net/UnrealNetwork.h"
#include "Data/AnabiosisAttributeData.h"
#include "GameplayEffect.h"

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
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    AttributeSet = CreateDefaultSubobject<UAttributeSet>(TEXT("AttributeSet"));
}

void AAnabiosisOriginCharacter::BeginPlay()
{
    Super::BeginPlay();
    UAbilitySystemGlobals::Get().InitGlobalData();
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
        GiveDefaultAbilities();
    }
}

void AAnabiosisOriginCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();
    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->InitAbilityActorInfo(this, this);
    }
}

void AAnabiosisOriginCharacter::GiveDefaultAbilities()
{
    if (!HasAuthority() || !AbilitySystemComponent)
    {
        return;
    }

    for (TSubclassOf<UGameplayAbility>& Ability : DefaultAbilities)
    {
        if (Ability)
        {
            AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
        }
    }
}

void AAnabiosisOriginCharacter::SetPlayerClass(EAnabiosisPlayerClass NewClass)
{
    if (!HasAuthority()) return;
    
    CurrentClass = NewClass;
    UpdateAttributesForClass();
}

void AAnabiosisOriginCharacter::OnRep_CurrentClass()
{
    UpdateAttributesForClass();
}

void AAnabiosisOriginCharacter::UpdateAttributesForClass()
{
    if (!AbilitySystemComponent) return;

    // 获取对应职业的属性行名称
    FString RowName = FString::Printf(TEXT("%s_Data"), *UEnum::GetValueAsString(CurrentClass));
    const FAnabiosisAttributeData* AttributeData = ClassAttributeTable->FindRow<FAnabiosisAttributeData>(*RowName, TEXT(""));
    
    if (!AttributeData) return;

    // 创建GameplayEffect来应用属性
    UGameplayEffect* ClassEffect = NewObject<UGameplayEffect>(GetTransientPackage(), FName(TEXT("ClassAttributes")));
    if (!ClassEffect) return;

    ClassEffect->DurationPolicy = EGameplayEffectDurationType::Infinite;

    // 应用效果
    FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
    FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(TSubclassOf<UGameplayEffect>(ClassEffect->GetClass()), 1, EffectContext);
    if (SpecHandle.IsValid())
    {
        AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
    }
}

void AAnabiosisOriginCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AAnabiosisOriginCharacter, CurrentClass);
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
    if (!NewTag.IsValid() || !AbilitySystemComponent)
    {
        return;
    }
    
    // 从能力系统中移除旧攻击标签
    if (AttackAbilityTag.IsValid())
    {
        AbilitySystemComponent->RemoveLooseGameplayTag(AttackAbilityTag);
    }
    
    // 设置新攻击标签
    AttackAbilityTag = NewTag;
    
    // 将新标签添加到能力系统
    AbilitySystemComponent->AddLooseGameplayTag(AttackAbilityTag);
}

void AAnabiosisOriginCharacter::RefreshAbilityBindings()
{
    if (!AbilitySystemComponent)
    {
        return;
    }
    
    // 获取当前标签
    FGameplayTagContainer CurrentTags;
    AbilitySystemComponent->GetOwnedGameplayTags(CurrentTags);
    
    // 先移除所有标签
    for (auto Tag : CurrentTags)
    {
        AbilitySystemComponent->RemoveLooseGameplayTag(Tag);
    }
    
    // 确保攻击标签被重新添加
    if (AttackAbilityTag.IsValid())
    {
        AbilitySystemComponent->AddLooseGameplayTag(AttackAbilityTag);
    }
    
    // 重新添加其他标签
    for (auto Tag : CurrentTags)
    {
        if (Tag != AttackAbilityTag)
        {
            AbilitySystemComponent->AddLooseGameplayTag(Tag);
        }
    }
    
    // 刷新能力状态
    AbilitySystemComponent->NotifyAbilityEnded(FGameplayAbilitySpecHandle(), nullptr, false);
}