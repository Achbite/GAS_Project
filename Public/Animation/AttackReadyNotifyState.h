/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: AttackReadyNotifyState.h
* 功能描述： 定义动画通知状态 UAttackReadyNotifyState。
*            用于标记动画中可以被其他动作（如闪避、格挡）打断的区间。
* 结构：
* - 继承自 UAnimNotifyState。
* - 目前 NotifyBegin 和 NotifyEnd 是占位符，需要根据具体实现添加逻辑（例如，添加/移除允许打断的 GameplayTag）。
*/

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackReadyNotifyState.generated.h"

/**
 * @brief 动画通知状态，标记动画可以被其他动作打断的区间。
 *        (当前为占位符，需要具体实现打断逻辑)
 */
UCLASS(Blueprintable, meta = (DisplayName = "攻击可打断"))
class ANABIOSISORIGIN_API UAttackReadyNotifyState : public UAnimNotifyState
{
    GENERATED_BODY()

protected:
    /** 通知状态开始时调用 (例如，添加允许打断的 Tag) */
    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

    /** 通知状态结束时调用 (例如，移除允许打断的 Tag) */
    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
