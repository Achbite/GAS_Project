#include "Animation/AttackWindowNotifyState.h"
#include "Characters/AnabiosisOriginCharacter.h"
#include "AbilitySystemBlueprintLibrary.h"

void UAttackWindowNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    if (!MeshComp || !MeshComp->GetOwner())
    {
        return;
    }

    // 获取角色引用
    AAnabiosisOriginCharacter* Character = Cast<AAnabiosisOriginCharacter>(MeshComp->GetOwner());
    if (!Character)
    {
        return;
    }

    // 设置当前攻击标签，以便角色可以响应连击输入
    if (CurrentAttackTag.IsValid())
    {
        // 设置角色的攻击标签
        Character->SetAttackAbilityTag(CurrentAttackTag);
    }
}

void UAttackWindowNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp || !MeshComp->GetOwner())
    {
        return;
    }

    // 获取角色引用
    AAnabiosisOriginCharacter* Character = Cast<AAnabiosisOriginCharacter>(MeshComp->GetOwner());
    if (!Character)
    {
        return;
    }

    // 窗口期结束，恢复基础攻击标签
    if (BaseAttackTag.IsValid())
    {
        // 设置角色的攻击标签为基础攻击标签
        Character->SetAttackAbilityTag(BaseAttackTag);
    }
}
