#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"
#include "AttackWindowNotifyState.generated.h"

/**
 * 攻击窗口通知状态类
 * 定义角色可以接收连击输入的时间窗口
 */
UCLASS()
class ANABIOSISORIGIN_API UAttackWindowNotifyState : public UAnimNotifyState
{
    GENERATED_BODY()

public:
    /** 当通知开始时设置角色的当前攻击类型标签 */
    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
    
    /** 当通知结束时恢复角色的基础攻击标签 */
    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
    
    /** 当前攻击标签，连击窗口期间使用此标签识别下一次攻击 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    FGameplayTag CurrentAttackTag;
    
    /** 基础攻击标签，窗口结束时还原 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    FGameplayTag BaseAttackTag;
};
