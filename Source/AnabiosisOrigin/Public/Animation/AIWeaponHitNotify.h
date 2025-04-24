/* 
 * Copyright (C) 2025 [Wang]
 * ... (Copy license header) ...
 */
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Engine/EngineTypes.h" 
#include "GameplayTagContainer.h" 
#include "AIWeaponHitNotify.generated.h"

// 日志类别声明
DECLARE_LOG_CATEGORY_EXTERN(LogAIWeaponHitNotify, Log, All);

// 前向声明
class UPrimitiveComponent;
class UAnimMontage; 
class ACharacter; 

// 定义 Player 追踪通道
#define COLLISION_PLAYER ECC_Pawn 

/**
 * @brief AI 武器命中检测通知状态。
 * 
 * 在动画状态的持续时间内，使用武器插槽的起点和终点执行扫描检测。
 * 对首次命中的、属于指定通道（默认为 Player）的玩家 Character Actor 应用伤害、播放受击蒙太奇，并施加 Gameplay Tag。
 */
UCLASS(Blueprintable, meta = (DisplayName = "AI Weapon Hit Notify")) // AI 武器命中通知
class ANABIOSISORIGIN_API UAIWeaponHitNotify : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UAIWeaponHitNotify();

	//~ Begin UAnimNotifyState Interface (UAnimNotifyState 接口开始)
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override; // 通知开始
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime) override; // 通知 Tick
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override; // 通知结束
	//~ End UAnimNotifyState Interface (UAnimNotifyState 接口结束)

protected:
	// --- Weapon Properties (武器属性) ---
	/** 武器扫描起点的骨骼/插槽名称 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIWeaponHit|Setup")
	FName WeaponStartSocketName; // 武器起始插槽名

	/** 武器扫描终点的骨骼/插槽名称 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIWeaponHit|Setup")
	FName WeaponEndSocketName; // 武器结束插槽名

	// --- Trace Properties (追踪属性) ---
	/** 扫描半径（0 为线形扫描，>0 为球形扫描） */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIWeaponHit|Trace", meta = (ClampMin = "0.0"))
	float TraceRadius; // 追踪半径

	/** 用于武器命中的追踪通道 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIWeaponHit|Trace")
	TEnumAsByte<ECollisionChannel> TraceChannel; // 追踪通道

	// --- Damage Properties (伤害属性) ---
	/** 是否应用伤害 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIWeaponHit|Damage")
	bool bApplyDamage; // 应用伤害

	/** 基础伤害值 (如果无法从 AI 属性获取攻击力，则使用此值作为备选) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIWeaponHit|Damage", meta = (EditCondition = "bApplyDamage", ClampMin = "0.0"))
	float BaseDamage; // 基础伤害

	// --- Hit Reaction Properties (受击反应属性) ---
	/** 命中玩家时播放的受击动画蒙太奇 (可选备用) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIWeaponHit|Reaction", meta = (DisplayName = "Fallback Player Hit Reaction Montage")) // 备用玩家受击反应蒙太奇
	TObjectPtr<UAnimMontage> FallbackPlayerHitReactionMontage; // 备用玩家受击反应蒙太奇

	/** 命中时施加给目标的 Gameplay Tag */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIWeaponHit|Reaction", meta = (DisplayName = "Hit React Tag")) // 受击反应标签
	FGameplayTag HitReactTag; // 受击反应标签

	// --- Debug Properties (调试属性) ---
	/** 是否启用调试绘制 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIWeaponHit|Debug")
	bool bDebugTrace; // 调试追踪

	/** 调试信息和绘制的显示时长 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIWeaponHit|Debug", meta = (EditCondition = "bDebugTrace", ClampMin = "0.0"))
	float DebugDisplayTime; // 调试显示时间

private:
	/** 在此通知状态实例期间已命中的 Actor 列表 */
	UPROPERTY(Transient) // 瞬态
	TSet<TObjectPtr<AActor>> HitActors; // 已命中 Actor 集合

	/** 缓存找到的武器组件指针 */
	UPROPERTY(Transient) // 瞬态
	TObjectPtr<UPrimitiveComponent> CachedWeaponMeshComp; // 缓存的武器网格组件
};
