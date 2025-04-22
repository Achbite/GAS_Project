#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Engine/EngineTypes.h" 
#include "WeaponHitNotify.generated.h"

// 日志类别声明
DECLARE_LOG_CATEGORY_EXTERN(LogWeaponHitNotify, Log, All);

// 前向声明
class UPrimitiveComponent;
class UAnimMontage; 

// 定义 Enemy 追踪通道 (与 C++ 文件和 DefaultEngine.ini 中保持一致)
#define COLLISION_ENEMY ECC_GameTraceChannel1

/**
 * @brief 武器命中检测通知状态。
 * 
 * 在动画状态的持续时间内，使用武器插槽的起点和终点执行扫描检测（球体或射线）。
 * 对首次命中的、属于指定通道（默认为 Enemy）的 Character Actor 应用伤害和播放受击蒙太奇。
 * 通过查找附加到 Owner Actor 上的子 Actor 中的 PrimitiveComponent 来定位武器。
 */
UCLASS(Blueprintable, meta = (DisplayName = "Weapon Hit Notify")) // 使其在蓝图中更易识别
class ANABIOSISORIGIN_API UWeaponHitNotify : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UWeaponHitNotify();

	//~ Begin UAnimNotifyState Interface
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;
	//~ End UAnimNotifyState Interface

protected: // 改为 protected，因为这些属性主要在内部使用或由蓝图配置
	// --- Weapon Properties ---
	/** 武器扫描起点的骨骼/插槽名称 (例如 "weapon_start") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Setup")
	FName WeaponStartSocketName; // 武器扫描起点插槽名

	/** 武器扫描终点的骨骼/插槽名称 (例如 "weapon_end") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Setup")
	FName WeaponEndSocketName; // 武器扫描终点插槽名

	// --- Trace Properties ---
	/** 扫描半径（0 为线形扫描，>0 为球形扫描） */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Trace", meta = (ClampMin = "0.0"))
	float TraceRadius; // 扫描半径

	/** 用于武器命中的追踪通道 (默认为 Enemy 通道) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Trace")
	TEnumAsByte<ECollisionChannel> TraceChannel; // 追踪通道

	// --- Damage Properties ---
	/** 是否应用伤害 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Damage")
	bool bApplyDamage; // 是否应用伤害

	/** 基础伤害值 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Damage", meta = (EditCondition = "bApplyDamage", ClampMin = "0.0"))
	float BaseDamage; // 基础伤害值

	// --- Hit Reaction Properties ---
	/** 命中敌人时播放的受击动画蒙太奇 (可选，如果敌人自身没有配置，则使用此蒙太奇) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Reaction", meta = (DisplayName = "Fallback Hit Reaction Montage"))
	TObjectPtr<UAnimMontage> HitReactionMontage; // 备选受击反应蒙太奇

	// --- Debug Properties ---
	/** 是否启用调试绘制（显示扫描轨迹、插槽位置和命中点） */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Debug")
	bool bDebugTrace; // 是否启用调试绘制

	/** 调试信息和绘制的显示时长（秒） */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Debug", meta = (EditCondition = "bDebugTrace", ClampMin = "0.0"))
	float DebugDisplayTime; // 调试显示时长

private:
	/** 在此通知状态实例期间已命中的 Actor 列表，防止重复处理 */
	UPROPERTY(Transient) // Transient 表示此状态不需要保存或复制
	TSet<TObjectPtr<AActor>> HitActors; // 使用 TSet 以提高查找效率

	/** 缓存找到的武器组件指针，避免每帧查找 */
	UPROPERTY(Transient) 
	TObjectPtr<UPrimitiveComponent> CachedWeaponMeshComp; // 缓存的武器组件
};
