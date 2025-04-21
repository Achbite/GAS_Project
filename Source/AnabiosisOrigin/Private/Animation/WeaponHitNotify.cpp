/**
 * @file WeaponHitNotify.cpp
 * @brief 实现了 UWeaponHitNotify 类，这是一个动画通知状态，用于在动画播放期间执行武器的射线或球体检测。
 *
 * 主要功能：
 * - 在 NotifyBegin 时查找并缓存附加到角色上的武器组件。
 * - 在 NotifyTick 时使用缓存的武器组件，获取武器上的插槽位置。
 * - 在每一帧执行从上一帧末端位置到当前末端位置的扫描检测（球体或射线）。
 * - 处理命中结果，应用伤害（如果启用），并避免对同一 Actor 重复造成伤害。
 * - 提供调试可视化功能（绘制扫描轨迹和插槽位置）。
 */

#include "Animation/WeaponHitNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequenceBase.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Controller.h"
#include "Engine/DamageEvents.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"

// Define the log category
DEFINE_LOG_CATEGORY(LogWeaponHitNotify);

UWeaponHitNotify::UWeaponHitNotify()
{
	// 默认值设置
	WeaponStartSocketName = FName("weapon_start");
	WeaponEndSocketName = FName("weapon_end");
	TraceRadius = 2.0f;
	bDebugTrace = true; // 默认开启调试模式
	DebugDisplayTime = 2.0f;
	bApplyDamage = false;
	BaseDamage = 10.0f;
	PreviousEndLocation = FVector::ZeroVector;
	CachedWeaponMeshComp = nullptr; // 初始化缓存指针
}

/**
 * @brief 辅助函数：查找附加到 OwnerActor 上的子 Actor 中，第一个包含指定插槽的 PrimitiveComponent。
 * @param OwnerActor 拥有此动画通知的角色 Actor。
 * @param StartSocketName 武器起点的插槽名称。
 * @param EndSocketName 武器终点的插槽名称。
 * @param bDebug 是否启用调试日志和绘制。
 * @param DebugTime 调试信息显示时长。
 * @return 找到的武器组件指针，如果未找到则返回 nullptr。
 */
UPrimitiveComponent* FindAttachedWeaponComponent(const AActor* OwnerActor, FName StartSocketName, FName EndSocketName, bool bDebug, float DebugTime)
{
	if (!OwnerActor)
	{
		UE_LOG(LogWeaponHitNotify, Error, TEXT("FindAttachedWeaponComponent: OwnerActor is NULL"));
		return nullptr;
	}

	UE_LOG(LogWeaponHitNotify, Log, TEXT("FindAttachedWeaponComponent: Searching on Owner '%s'"), *OwnerActor->GetName());

	TArray<AActor*> AttachedActors;
	OwnerActor->GetAttachedActors(AttachedActors); // 获取所有附加的子 Actor

	UE_LOG(LogWeaponHitNotify, Log, TEXT("  Found %d Attached Actors."), AttachedActors.Num());

	for (AActor* AttachedActor : AttachedActors)
	{
		if (!AttachedActor) continue;

		UE_LOG(LogWeaponHitNotify, Log, TEXT("  Checking Attached Actor: '%s'"), *AttachedActor->GetName());

		// 优先检查根组件
		UPrimitiveComponent* RootPrimComp = Cast<UPrimitiveComponent>(AttachedActor->GetRootComponent());
		if (RootPrimComp)
		{
			bool bHasStartSocket = RootPrimComp->DoesSocketExist(StartSocketName);
			bool bHasEndSocket = RootPrimComp->DoesSocketExist(EndSocketName);
			UE_LOG(LogWeaponHitNotify, Log, TEXT("    Root Comp: '%s'. Socket '%s': %s. Socket '%s': %s"),
					*RootPrimComp->GetName(), *StartSocketName.ToString(), bHasStartSocket ? TEXT("Exists") : TEXT("Missing"), *EndSocketName.ToString(), bHasEndSocket ? TEXT("Exists") : TEXT("Missing"));

			if (bHasStartSocket && bHasEndSocket)
			{
				UE_LOG(LogWeaponHitNotify, Log, TEXT("    Found Weapon Component (Root): '%s' on Actor '%s'"), *RootPrimComp->GetName(), *AttachedActor->GetName());
				// 如果启用调试，绘制插槽位置
				if (bDebug)
				{
					FVector StartLoc = RootPrimComp->GetSocketLocation(StartSocketName);
					FVector EndLoc = RootPrimComp->GetSocketLocation(EndSocketName);
					DrawDebugSphere(RootPrimComp->GetWorld(), StartLoc, 5.f, 12, FColor::Magenta, false, DebugTime);
					DrawDebugSphere(RootPrimComp->GetWorld(), EndLoc, 5.f, 12, FColor::Blue, false, DebugTime);
				}
				return RootPrimComp; // 找到即返回
			}
		}
		else
		{
			UE_LOG(LogWeaponHitNotify, Log, TEXT("    Attached Actor '%s' has no Primitive Root Component."), *AttachedActor->GetName());
		}

		// 如果根组件不是，则检查该 Actor 内的所有 PrimitiveComponent
		TArray<UPrimitiveComponent*> PrimitiveComponents;
		AttachedActor->GetComponents<UPrimitiveComponent>(PrimitiveComponents);
		UE_LOG(LogWeaponHitNotify, Log, TEXT("    Found %d Primitive Components in '%s'. Checking them..."), PrimitiveComponents.Num(), *AttachedActor->GetName());

		for (UPrimitiveComponent* PrimComp : PrimitiveComponents)
		{
			if (!PrimComp || PrimComp == RootPrimComp) continue; // 跳过空指针或已检查过的根组件

			bool bHasStartSocket = PrimComp->DoesSocketExist(StartSocketName);
			bool bHasEndSocket = PrimComp->DoesSocketExist(EndSocketName);
			UE_LOG(LogWeaponHitNotify, Log, TEXT("      Checking Comp: '%s'. Socket '%s': %s. Socket '%s': %s"),
					*PrimComp->GetName(), *StartSocketName.ToString(), bHasStartSocket ? TEXT("Exists") : TEXT("Missing"), *EndSocketName.ToString(), bHasEndSocket ? TEXT("Exists") : TEXT("Missing"));

			if (bHasStartSocket && bHasEndSocket)
			{
				UE_LOG(LogWeaponHitNotify, Log, TEXT("    Found Weapon Component (Non-Root): '%s' on Actor '%s'"), *PrimComp->GetName(), *AttachedActor->GetName());
				// 如果启用调试，绘制插槽位置
				if (bDebug)
				{
					FVector StartLoc = PrimComp->GetSocketLocation(StartSocketName);
					FVector EndLoc = PrimComp->GetSocketLocation(EndSocketName);
					DrawDebugSphere(PrimComp->GetWorld(), StartLoc, 5.f, 12, FColor::Magenta, false, DebugTime);
					DrawDebugSphere(PrimComp->GetWorld(), EndLoc, 5.f, 12, FColor::Blue, false, DebugTime);
				}
				return PrimComp; // 找到即返回
			}
		}
	}

	// 如果遍历完所有附加 Actor 及其组件都未找到
	UE_LOG(LogWeaponHitNotify, Error, TEXT("FindAttachedWeaponComponent: Weapon component with sockets '%s' AND '%s' not found on '%s' or its attachments."),
			*StartSocketName.ToString(),*EndSocketName.ToString(), *OwnerActor->GetName());
	if (bDebug && GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugTime, FColor::Red, FString::Printf(TEXT("FindAttachedWeaponComponent: Weapon component with sockets '%s' AND '%s' not found on '%s' or its attachments."),
			*StartSocketName.ToString(),*EndSocketName.ToString(), *OwnerActor->GetName()));

	return nullptr; // 未找到武器组件
}

/**
 * @brief 通知状态开始时调用。
 *        查找并缓存武器组件，初始化命中列表和上一帧位置。
 */
void UWeaponHitNotify::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	UE_LOG(LogWeaponHitNotify, Log, TEXT("WeaponHitNotify::NotifyBegin - Anim: %s"), *GetNameSafe(Animation));

	// 检查传入的骨骼网格组件和其所有者 Actor 是否有效
	if (!MeshComp)
	{
		UE_LOG(LogWeaponHitNotify, Error, TEXT("WeaponHitNotify::NotifyBegin - MeshComp is NULL"));
		return;
	}
	AActor* OwnerActor = MeshComp->GetOwner();
	if (!OwnerActor)
	{
		UE_LOG(LogWeaponHitNotify, Error, TEXT("WeaponHitNotify::NotifyBegin - OwnerActor is NULL"));
		return;
	}

	// 清空上一轮的命中记录
	HitActors.Empty();
	// 重置缓存的武器组件指针
	CachedWeaponMeshComp = nullptr;
	// 重置上一帧位置
	PreviousEndLocation = FVector::ZeroVector;

	// 查找武器组件
	UPrimitiveComponent* WeaponMeshComp = FindAttachedWeaponComponent(OwnerActor, WeaponStartSocketName, WeaponEndSocketName, bDebugTrace, DebugDisplayTime);

	if (WeaponMeshComp)
	{
		// 缓存找到的组件指针
		CachedWeaponMeshComp = WeaponMeshComp;
		// 获取武器末端的初始位置
		PreviousEndLocation = WeaponMeshComp->GetSocketLocation(WeaponEndSocketName);

		// 检查获取的位置是否有效
		if (PreviousEndLocation.IsZero())
		{
			UE_LOG(LogWeaponHitNotify, Warning, TEXT("WeaponHitNotify: Socket '%s' returned zero location on Begin for component '%s'."), *WeaponEndSocketName.ToString(), *WeaponMeshComp->GetName());
			// 设置一个非零值，避免 Tick 因为 PreviousEndLocation 为零而提前退出
			PreviousEndLocation = FVector(1.f);
		}
		else
		{
			UE_LOG(LogWeaponHitNotify, Log, TEXT("WeaponHitNotify::NotifyBegin - Initial PreviousEndLocation set from '%s'"), *WeaponMeshComp->GetName());
		}
	}
	// 如果未找到武器组件，FindAttachedWeaponComponent 内部会打印错误日志
}

/**
 * @brief 通知状态在每一帧 Tick 时调用。
 *        执行扫描检测并处理命中。
 */
void UWeaponHitNotify::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	// 检查 OwnerActor 和缓存的武器组件是否有效，以及上一帧位置是否已初始化
	AActor* OwnerActor = MeshComp ? MeshComp->GetOwner() : nullptr;
	if (!OwnerActor || !CachedWeaponMeshComp || PreviousEndLocation.IsZero())
	{
		// 如果缓存的组件无效，但上一帧位置有效（说明Begin时找到了但现在丢失了），则打印错误
		if (!CachedWeaponMeshComp && !PreviousEndLocation.IsZero())
		{
			UE_LOG(LogWeaponHitNotify, Error, TEXT("NotifyTick: Cached Weapon component became NULL."));
			if (GEngine && bDebugTrace) GEngine->AddOnScreenDebugMessage(-1, DebugDisplayTime, FColor::Red, TEXT("NotifyTick: Cached Weapon component became NULL."));
			PreviousEndLocation = FVector::ZeroVector; // 重置位置以停止后续 Tick 处理
		}
		return; // 提前退出 Tick
	}

	// 从缓存的武器组件获取当前插槽位置
	FVector CurrentStartLocation = CachedWeaponMeshComp->GetSocketLocation(WeaponStartSocketName);
	FVector CurrentEndLocation = CachedWeaponMeshComp->GetSocketLocation(WeaponEndSocketName);

	// 如果启用调试，绘制当前插槽位置的球体
	if (bDebugTrace)
	{
		DrawDebugSphere(CachedWeaponMeshComp->GetWorld(), CurrentStartLocation, 5.f, 12, FColor::Magenta, false, 0.f); // 起点：品红
		DrawDebugSphere(CachedWeaponMeshComp->GetWorld(), CurrentEndLocation, 5.f, 12, FColor::Blue, false, 0.f);    // 终点：蓝色
	}

	// 检查获取的插槽位置是否有效
	if (CurrentStartLocation.IsZero() || CurrentEndLocation.IsZero())
	{
		UE_LOG(LogWeaponHitNotify, Warning, TEXT("WeaponHitNotify: Socket '%s' or '%s' returned zero location on component '%s' during Tick."),
				*WeaponStartSocketName.ToString(), *WeaponEndSocketName.ToString(), *CachedWeaponMeshComp->GetName());
		// 更新 PreviousEndLocation 以避免使用零向量进行追踪，并防止重复打印此警告
		PreviousEndLocation = CurrentEndLocation.IsZero() ? (CurrentStartLocation.IsZero() ? FVector(1.f) : CurrentStartLocation) : CurrentEndLocation;
		return;
	}

	// --- 执行扫描检测 ---

	// 设置碰撞查询参数
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwnerActor); // 忽略角色自身
	if (CachedWeaponMeshComp->GetOwner() != OwnerActor) // 如果武器是单独的 Actor，也忽略它
	{
		QueryParams.AddIgnoredActor(CachedWeaponMeshComp->GetOwner());
	}
	QueryParams.bTraceComplex = true; // 使用复杂碰撞进行精确检测

	TArray<FHitResult> HitResults; // 存储命中结果
	bool bHit = false; // 标记是否发生命中

	// 设置忽略列表（冗余，但 KismetSystemLibrary 需要）
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(OwnerActor);
	if (CachedWeaponMeshComp->GetOwner() != OwnerActor)
	{
		ActorsToIgnore.Add(CachedWeaponMeshComp->GetOwner());
	}

	// 定义扫描的起点和终点（从上一帧末端到当前帧末端）
	FVector TraceStart = PreviousEndLocation;
	FVector TraceEnd = CurrentEndLocation;

	// 根据 TraceRadius 选择球体扫描或射线扫描
	if (TraceRadius > 0.0f)
	{
		// 球形扫描
		bHit = UKismetSystemLibrary::SphereTraceMulti(
			CachedWeaponMeshComp->GetWorld(), // 使用武器组件所在的世界
			TraceStart,
			TraceEnd,
			TraceRadius,
			UEngineTypes::ConvertToTraceType(ECC_Visibility), // 检测可见性通道
			false, // 不检测复杂碰撞（已在 QueryParams 中设置）
			ActorsToIgnore,
			bDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, // 根据调试设置绘制轨迹
			HitResults,
			true, // 忽略自身 Actor (已在 ActorsToIgnore 中设置)
			FLinearColor::Red, // 未命中颜色
			FLinearColor::Green, // 命中颜色
			DebugDisplayTime
		);
	}
	else
	{
		// 射线扫描
		bHit = UKismetSystemLibrary::LineTraceMulti(
			CachedWeaponMeshComp->GetWorld(),
			TraceStart,
			TraceEnd,
			UEngineTypes::ConvertToTraceType(ECC_Visibility),
			false,
			ActorsToIgnore,
			bDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
			HitResults,
			true,
			FLinearColor::Red,
			FLinearColor::Green,
			DebugDisplayTime
		);
	}

	// --- 处理命中结果 ---
	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			// 检查命中的 Actor 是否有效，以及是否已在本轮通知中处理过
			if (!HitActor || HitActors.Contains(HitActor))
			{
				continue;
			}

			// 将命中的 Actor 添加到已处理列表
			HitActors.Add(HitActor);

			UE_LOG(LogWeaponHitNotify, Log, TEXT("Weapon Hit: %s (Bone: %s)"), *HitActor->GetName(), *Hit.BoneName.ToString());
			if (GEngine && bDebugTrace) GEngine->AddOnScreenDebugMessage(-1, DebugDisplayTime, FColor::Green, FString::Printf(TEXT("武器命中: %s (骨骼: %s)"), *HitActor->GetName(), *Hit.BoneName.ToString()));

			// 如果启用了伤害应用
			if (bApplyDamage)
			{
				ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerActor);
				// 确保攻击者和其控制器有效
				if (OwnerCharacter && OwnerCharacter->GetController())
				{
					// 创建点伤害事件，包含伤害值、命中信息、伤害方向和伤害类型
					FPointDamageEvent DamageEvent(BaseDamage, Hit, (TraceEnd - TraceStart).GetSafeNormal(), UDamageType::StaticClass());
					// 对命中的 Actor 应用伤害
					HitActor->TakeDamage(BaseDamage, DamageEvent, OwnerCharacter->GetController(), OwnerActor);

					UE_LOG(LogWeaponHitNotify, Log, TEXT("  Applied %.1f damage to %s"), BaseDamage, *HitActor->GetName());
					if (GEngine && bDebugTrace) GEngine->AddOnScreenDebugMessage(-1, DebugDisplayTime, FColor::Orange, FString::Printf(TEXT("对 %s 造成 %.1f 伤害"), *HitActor->GetName(), BaseDamage));
				}
			}
		}
	}

	// 更新上一帧的末端位置，为下一帧的扫描做准备
	PreviousEndLocation = CurrentEndLocation;
}

/**
 * @brief 通知状态结束时调用。
 *        清理命中列表和缓存。
 */
void UWeaponHitNotify::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	// 清空已命中列表
	HitActors.Empty();
	// 重置上一帧位置
	PreviousEndLocation = FVector::ZeroVector;
	// 清除缓存的武器组件指针
	CachedWeaponMeshComp = nullptr;
}
