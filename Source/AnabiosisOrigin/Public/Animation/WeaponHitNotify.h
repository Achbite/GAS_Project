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
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Engine/EngineTypes.h" 
#include "GameplayTagContainer.h" 
#include "WeaponHitNotify.generated.h"

// 日志类别声明
DECLARE_LOG_CATEGORY_EXTERN(LogWeaponHitNotify, Log, All);

// 前向声明
class UPrimitiveComponent;
class UAnimMontage; 
class ACharacter; 

// 定义 Enemy 追踪通道
#define COLLISION_ENEMY ECC_GameTraceChannel1

/**
 * @brief 武器命中检测通知状态。
 * 
 * 在动画状态的持续时间内，使用武器插槽的起点和终点执行扫描检测。
 * 对首次命中的、属于指定通道的 Character Actor 应用伤害、播放受击蒙太奇，并施加 Gameplay Tag。
 */
UCLASS(Blueprintable, meta = (DisplayName = "Weapon Hit Notify")) 
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

protected: 
	// --- Weapon Properties ---
	/** 武器扫描起点的骨骼/插槽名称 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Setup")
	FName WeaponStartSocketName; 

	/** 武器扫描终点的骨骼/插槽名称 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Setup")
	FName WeaponEndSocketName; 

	// --- Trace Properties ---
	/** 扫描半径（0 为线形扫描，>0 为球形扫描） */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Trace", meta = (ClampMin = "0.0"))
	float TraceRadius; 

	/** 用于武器命中的追踪通道 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Trace")
	TEnumAsByte<ECollisionChannel> TraceChannel; 

	// --- Damage Properties ---
	/** 是否应用伤害 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Damage")
	bool bApplyDamage; 

	/** 基础伤害值 (如果无法从攻击者属性获取，则使用此值) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Damage", meta = (EditCondition = "bApplyDamage", ClampMin = "0.0"))
	float BaseDamage; 

	// --- Hit Reaction Properties ---
	/** 命中敌人时播放的受击动画蒙太奇 (可选备用) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Reaction", meta = (DisplayName = "Fallback Hit Reaction Montage"))
	TObjectPtr<UAnimMontage> HitReactionMontage; 

	/** 命中时施加给目标的 Gameplay Tag */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Reaction", meta = (DisplayName = "Hit React Tag"))
	FGameplayTag HitReactTag; 

	// --- Debug Properties ---
	/** 是否启用调试绘制 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Debug")
	bool bDebugTrace; 

	/** 调试信息和绘制的显示时长 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponHit|Debug", meta = (EditCondition = "bDebugTrace", ClampMin = "0.0"))
	float DebugDisplayTime; 

private:
	/** 在此通知状态实例期间已命中的 Actor 列表 */
	UPROPERTY(Transient) 
	TSet<TObjectPtr<AActor>> HitActors; 

	/** 缓存找到的武器组件指针 */
	UPROPERTY(Transient) 
	TObjectPtr<UPrimitiveComponent> CachedWeaponMeshComp; 
};

