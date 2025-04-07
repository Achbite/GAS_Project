#include "Animation/AttackReadyNotifyState.h"
#include "Characters/AnabiosisOriginCharacter.h"
#include "Animation/AnimInstance.h"

void UAttackReadyNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    if (!MeshComp)
    {
        return;
    }
    
    // 设置动画蒙太奇为可打断
    UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
    if (AnimInstance)
    {
        // 在这里可以设置蒙太奇为可打断
        // 目前只是一个占位，实际实现需要根据项目需求添加
    }
}

void UAttackReadyNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp)
    {
        return;
    }
    
    // 动画蒙太奇恢复不可打断
    UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
    if (AnimInstance)
    {
        // 在这里可以设置蒙太奇为不可打断
        // 目前只是一个占位，实际实现需要根据项目需求添加
    }
}
