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

