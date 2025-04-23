/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: WeaponHitNotify.h
* 功能描述： 定义动画通知 UWeaponHitNotify。
*            用于在动画播放期间，根据武器上的插槽位置执行扫描检测，处理武器命中逻辑。
* 结构：
* - 继承自 UAnimNotifyState。
* - 定义武器插槽名称、扫描参数（半径、通道）、调试选项。
* - 定义伤害和受击反应相关参数。
* - 在 NotifyBegin 中初始化，查找并缓存武器组件。
* - 在 NotifyTick 中执行扫描检测，处理命中结果（应用伤害、播放受击动画）。
* - 在 NotifyEnd 中清理状态。
* - 包含一个辅助函数 FindAttachedWeaponComponent 用于查找武器组件。
*/

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Engine/EngineTypes.h" // 包含 ECollisionChannel
#include "WeaponHitNotify.generated.h"

// 前向声明
class UAnimSequenceBase;
class USkeletalMeshComponent;
class UAnimMontage;
class ACharacter; // 添加 ACharacter 前向声明
class UPrimitiveComponent; // 添加 UPrimitiveComponent 前向声明

// 声明日志类别
DECLARE_LOG_CATEGORY_EXTERN(LogWeaponHitNotify, Log, All);

/**
 * @brief 动画通知状态，用于在动画期间执行武器命中检测。
 */
UCLASS(Blueprintable, meta = (DisplayName = "武器命中检测"))
class ANABIOSISORIGIN_API UWeaponHitNotify : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	/** 构造函数 */
	UWeaponHitNotify();

	/** 武器轨迹起点的插槽名称 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "武器命中检测")
	FName WeaponStartSocketName;

	/** 武器轨迹终点的插槽名称 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "武器命中检测")
	FName WeaponEndSocketName;

	/** 扫描半径 (如果为 0，则执行线性扫描) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "武器命中检测")
	float TraceRadius;

	/** 用于扫描的碰撞通道 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "武器命中检测")
	TEnumAsByte<ECollisionChannel> TraceChannel;

	/** 是否启用调试绘制 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "调试")
	bool bDebugTrace;

	/** 调试信息显示时长 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "调试", meta = (EditCondition = "bDebugTrace"))
	float DebugDisplayTime;

	/** 是否应用伤害 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "伤害")
	bool bApplyDamage;

	/** 基础伤害值 (如果无法从攻击者属性获取伤害) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "伤害", meta = (EditCondition = "bApplyDamage"))
	float BaseDamage;

	/** 命中时在目标身上播放的受击蒙太奇 (可选，如果目标角色没有自己的受击蒙太奇) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "效果")
	TObjectPtr<UAnimMontage> HitReactionMontage;

protected:
	/** 通知状态开始时调用 */
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;

	/** 通知状态 Tick 时调用 */
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime) override;

	/** 通知状态结束时调用 */
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;

private:
	/** 存储在本轮通知中已经命中的 Actor，防止重复处理 */
	UPROPERTY(Transient)
	TSet<TObjectPtr<ACharacter>> HitActors; // 使用 TSet 提高查找效率

	/** 缓存查找到的武器网格体组件 */
	UPROPERTY(Transient)
	TObjectPtr<UPrimitiveComponent> CachedWeaponMeshComp;
};

/**
 * @brief 辅助函数：查找附加到 OwnerActor 上的、包含指定插槽的第一个 PrimitiveComponent。
 * @param OwnerActor 拥有此动画通知的角色 Actor。
 * @param StartSocketName 武器起点的插槽名称。
 * @param EndSocketName 武器终点的插槽名称。
 * @param bDebug 是否启用调试日志和绘制。
 * @param DebugTime 调试信息显示时长。
 * @return 找到的武器组件指针，如果未找到则返回 nullptr。
 */
UPrimitiveComponent* FindAttachedWeaponComponent(const AActor* OwnerActor, FName StartSocketName, FName EndSocketName, bool bDebug, float DebugTime);
