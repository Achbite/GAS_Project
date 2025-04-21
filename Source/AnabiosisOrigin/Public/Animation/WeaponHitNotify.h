#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "WeaponHitNotify.generated.h"

// Declare a log category for this class
DECLARE_LOG_CATEGORY_EXTERN(LogWeaponHitNotify, Log, All);

// Forward declare
class UPrimitiveComponent;

/**
 * 武器命中检测通知状态
 * 在动画状态的持续时间内，使用武器插槽的起点和终点执行精确的射线检测。
 * 通过查找附加到Owner Actor上的子Actor中的PrimitiveComponent来定位武器。
 */
UCLASS()
class ANABIOSISORIGIN_API UWeaponHitNotify : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UWeaponHitNotify();

	/** 当动画通知状态开始时执行 */
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;

	/** 当动画通知状态Tick时执行 */
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime) override;

	/** 当动画通知状态结束时执行 */
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;

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

private:
	/** 在此通知状态期间已命中的Actor列表，防止重复命中 */
	UPROPERTY()
	TArray<TObjectPtr<AActor>> HitActors;

	/** 上一帧武器末端的位置 */
	FVector PreviousEndLocation;

	/** 缓存找到的武器组件指针，避免每帧查找 */
	UPROPERTY(Transient) // Transient表示这个属性不需要保存
	TObjectPtr<UPrimitiveComponent> CachedWeaponMeshComp;
};
