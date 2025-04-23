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
* 文件名: AttackReadyNotifyState.cpp
* 功能描述： 实现动画通知状态 UAttackReadyNotifyState 的逻辑。
*            用于标记动画中可以被其他动作打断的区间（占位符）。
* 结构：
* - NotifyBegin：通知开始时调用（占位）。
* - NotifyEnd：通知结束时调用（占位）。
* @note 当前实现为空，需要根据具体需求添加逻辑，例如通过 GameplayTag 控制打断。
*/

#include "Animation/AttackReadyNotifyState.h"
#include "Characters/AnabiosisOriginCharacter.h" // 可能需要包含角色头文件
#include "Animation/AnimInstance.h"

void UAttackReadyNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	// 检查 MeshComp 是否有效
	if (!MeshComp)
	{
		return;
	}

	// 获取动画实例
	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
	if (AnimInstance)
	{
		// 在这里可以添加逻辑，例如：
		// - 获取角色的 AbilitySystemComponent
		// - 添加一个表示“可被中断”的 GameplayTag (例如 "State.CanBeInterrupted")
		// UE_LOG(LogTemp, Verbose, TEXT("攻击可打断窗口开始"));
	}
}

void UAttackReadyNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// 检查 MeshComp 是否有效
	if (!MeshComp)
	{
		return;
	}

	// 获取动画实例
	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
	if (AnimInstance)
	{
		// 在这里可以添加逻辑，例如：
		// - 获取角色的 AbilitySystemComponent
		// - 移除表示“可被中断”的 GameplayTag
		// UE_LOG(LogTemp, Verbose, TEXT("攻击可打断窗口结束"));
	}
}

