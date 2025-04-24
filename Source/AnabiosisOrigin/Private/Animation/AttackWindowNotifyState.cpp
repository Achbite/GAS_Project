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
* 文件名: AttackWindowNotifyState.cpp
* 功能描述： 实现动画通知状态 UAttackWindowNotifyState 的逻辑。
*            用于在动画的特定区间内设置角色的攻击能力标签 (AttackAbilityTag)，
*            以允许玩家输入连击指令，触发后续的攻击能力。
* 结构：
* - NotifyBegin：通知开始时，获取玩家角色并将角色的 AttackAbilityTag 设置为 CurrentAttackTag。
* - NotifyEnd：通知结束时，获取玩家角色并将角色的 AttackAbilityTag 恢复为 BaseAttackTag。
*/

#include "Animation/AttackWindowNotifyState.h"
#include "Characters/AnabiosisOriginCharacter.h" // 包含玩家角色头文件
// #include "AbilitySystemBlueprintLibrary.h" // 如果不直接使用蓝图库函数，可以移除

void UAttackWindowNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	// 检查 MeshComp 及其拥有者是否有效
	if (!MeshComp || !MeshComp->GetOwner())
	{
		return;
	}

	// 获取拥有者角色，并确保是玩家角色
	AAnabiosisOriginCharacter* Character = Cast<AAnabiosisOriginCharacter>(MeshComp->GetOwner());
	if (!Character)
	{
		return; // 如果不是玩家角色，则不处理
	}

	// 如果当前攻击标签 (表示连击窗口对应的下一个攻击) 有效，则设置到角色上
	if (CurrentAttackTag.IsValid())
	{
		Character->SetAttackAbilityTag(CurrentAttackTag);
		// UE_LOG(LogTemp, Verbose, TEXT("攻击窗口开始：设置攻击标签为 %s"), *CurrentAttackTag.ToString());
	}
}

void UAttackWindowNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// 检查 MeshComp 及其拥有者是否有效
	if (!MeshComp || !MeshComp->GetOwner())
	{
		return;
	}

	// 获取拥有者角色，并确保是玩家角色
	AAnabiosisOriginCharacter* Character = Cast<AAnabiosisOriginCharacter>(MeshComp->GetOwner());
	if (!Character)
	{
		return; // 如果不是玩家角色，则不处理
	}

	// 如果基础攻击标签 (表示连击中断或结束后应恢复的默认攻击) 有效，
	// 则将角色的攻击标签恢复为基础攻击标签。
	if (BaseAttackTag.IsValid())
	{
		Character->SetAttackAbilityTag(BaseAttackTag);
		// UE_LOG(LogTemp, Verbose, TEXT("攻击窗口结束：恢复攻击标签为 %s"), *BaseAttackTag.ToString());
	}
	// 如果 BaseAttackTag 无效，则当前攻击标签会保留，直到下一次被覆盖或清除。
}

