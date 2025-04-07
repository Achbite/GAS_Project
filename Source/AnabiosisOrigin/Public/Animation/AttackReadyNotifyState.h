#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackReadyNotifyState.generated.h"

/**
 * 攻击准备通知状态类
 * 标记角色可接收连击输入的阶段
 */
UCLASS()
class ANABIOSISORIGIN_API UAttackReadyNotifyState : public UAnimNotifyState
{
    GENERATED_BODY()

public:
    /** 当通知开始时执行 */
    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
    
    /** 当通知结束时执行 */
    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
