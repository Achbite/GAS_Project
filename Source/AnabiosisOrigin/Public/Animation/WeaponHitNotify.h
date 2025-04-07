#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "WeaponHitNotify.generated.h"

/**
 * 武器命中检测通知
 * 使用武器插槽的起点和终点执行精确的射线检测
 */
UCLASS()
class ANABIOSISORIGIN_API UWeaponHitNotify : public UAnimNotify
{
    GENERATED_BODY()
    
public:
    UWeaponHitNotify();
    
    /** 当动画通知触发时执行 */
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
    
    /** 武器射线起点的骨骼/插槽名称 (例如 "weapon_start" 或 "blade_base") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit")
    FName WeaponStartSocketName;
    
    /** 武器射线终点的骨骼/插槽名称 (例如 "weapon_end" 或 "blade_tip") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit")
    FName WeaponEndSocketName;
    
    /** 射线检测半径（0为线形检测，>0为球形检测） */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit")
    float TraceRadius;
    
    /** 调试模式（是否显示射线） */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Debug")
    bool bDebugTrace;
    
    /** 命中信息显示时长（秒） */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Debug")
    float DebugDisplayTime;
    
    /** 是否应用伤害 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit")
    bool bApplyDamage;
    
    /** 基础伤害值 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit", meta = (EditCondition = "bApplyDamage"))
    float BaseDamage;
};
