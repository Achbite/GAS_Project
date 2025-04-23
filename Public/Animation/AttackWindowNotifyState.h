/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: AttackWindowNotifyState.h
* 功能描述： 定义动画通知状态 UAttackWindowNotifyState。
*            用于标记动画中的攻击连击窗口期。在此期间，角色可以接收下一次攻击输入以执行连击。
* 结构：
* - 继承自 UAnimNotifyState。
* - 定义当前攻击和基础攻击的 GameplayTag。
* - 在 NotifyBegin 中，将角色的攻击能力标签设置为 CurrentAttackTag。
* - 在 NotifyEnd 中，将角色的攻击能力标签恢复为 BaseAttackTag。
*/

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h" // 包含 GameplayTagContainer
#include "AttackWindowNotifyState.generated.h"

/**
 * @brief 动画通知状态，用于标记攻击连击的输入窗口期。
 */
UCLASS(Blueprintable, meta = (DisplayName = "攻击窗口"))
class ANABIOSISORIGIN_API UAttackWindowNotifyState : public UAnimNotifyState
{
    GENERATED_BODY()

public:
    /** 当前攻击对应的 GameplayTag (例如 Ability.Action.BaseAttack.2) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "攻击窗口")
    FGameplayTag CurrentAttackTag;

    /** 基础攻击对应的 GameplayTag (例如 Ability.Action.BaseAttack.1) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "攻击窗口")
    FGameplayTag BaseAttackTag;

protected:
    /** 通知状态开始时调用 */
    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

    /** 通知状态结束时调用 */
    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
