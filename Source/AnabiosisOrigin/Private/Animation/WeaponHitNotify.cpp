/**
 * @file WeaponHitNotify.cpp
 * @brief 实现了 UWeaponHitNotify 类，这是一个动画通知状态，用于在动画播放期间执行武器的射线或球体检测。
 *
 * 主要功能：
 * - 在 NotifyBegin 时查找并缓存附加到角色上的武器组件。
 * - 在 NotifyTick 时使用缓存的武器组件，获取武器上的插槽位置。
 * - 在每一帧执行从当前武器起点到当前武器终点的扫描检测（球体或射线）。 // <--- 修改了检测方式
 * - 处理命中结果，仅对 EnemyBaseCharacter 派生类播放受击蒙太奇，并避免重复处理。
 * - 提供调试可视化功能（绘制扫描轨迹、插槽位置和命中点）。
 */

#include "Animation/WeaponHitNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequenceBase.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "CollisionQueryParams.h" // 包含 CollisionQueryParams.h
#include "Characters/EnemyBaseCharacter.h" // 包含敌人基类头文件
#include "Animation/AnimInstance.h"      // 包含动画实例头文件
#include "Animation/AnimMontage.h"       // 包含动画蒙太奇头文件

// 定义 Enemy 追踪通道的宏 (与 .h 文件和 EnemyBaseCharacter.cpp 中保持一致)
#define COLLISION_ENEMY ECC_GameTraceChannel1

// Define the log category
DEFINE_LOG_CATEGORY(LogWeaponHitNotify);

UWeaponHitNotify::UWeaponHitNotify()
{
	// 默认值设置
	WeaponStartSocketName = FName("weapon_start");
	WeaponEndSocketName = FName("weapon_end");
	TraceRadius = 2.0f;
	TraceChannel = COLLISION_ENEMY; // **默认使用 Enemy 通道**
	bDebugTrace = true; // 默认开启调试模式
	DebugDisplayTime = 2.0f;
	bApplyDamage = false;
	BaseDamage = 10.0f;
	HitReactionMontage = nullptr; // 默认无蒙太奇
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

	UE_LOG(LogWeaponHitNotify, Log, TEXT("FindAttachedWeaponComponent: Searching for weapon component with sockets '%s' and '%s' attached to '%s'."), *StartSocketName.ToString(), *EndSocketName.ToString(), *OwnerActor->GetName());

	TArray<AActor*> AttachedActors;
	OwnerActor->GetAttachedActors(AttachedActors); // 获取所有附加的子 Actor

	for (AActor* AttachedActor : AttachedActors)
	{
		if (!AttachedActor) continue;

		// 优先检查根组件
		UPrimitiveComponent* RootPrimComp = Cast<UPrimitiveComponent>(AttachedActor->GetRootComponent());
		if (RootPrimComp)
		{
			bool bHasStartSocket = RootPrimComp->DoesSocketExist(StartSocketName);
			bool bHasEndSocket = RootPrimComp->DoesSocketExist(EndSocketName);
			if (bHasStartSocket && bHasEndSocket)
			{
				UE_LOG(LogWeaponHitNotify, Log, TEXT("  Found Weapon Component (Root): '%s' on Actor '%s'"), *RootPrimComp->GetName(), *AttachedActor->GetName());
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

		// 如果根组件不是，则检查该 Actor 内的所有 PrimitiveComponent
		TArray<UPrimitiveComponent*> PrimitiveComponents;
		AttachedActor->GetComponents<UPrimitiveComponent>(PrimitiveComponents);

		for (UPrimitiveComponent* PrimComp : PrimitiveComponents)
		{
			if (!PrimComp || PrimComp == RootPrimComp) continue; // 跳过空指针或已检查过的根组件

			bool bHasStartSocket = PrimComp->DoesSocketExist(StartSocketName);
			bool bHasEndSocket = PrimComp->DoesSocketExist(EndSocketName);

			// 只在找到时或调试模式下记录详细信息，减少常规日志噪音
			if (bHasStartSocket && bHasEndSocket)
			{
				UE_LOG(LogWeaponHitNotify, Log, TEXT("  Found Weapon Component (Non-Root): '%s' on Actor '%s'"), *PrimComp->GetName(), *AttachedActor->GetName());
				// 如果启用调试，绘制插槽位置
				if (bDebug)
				{
					FVector StartLoc = PrimComp->GetSocketLocation(StartSocketName);
					FVector EndLoc = PrimComp->GetSocketLocation(EndSocketName);
					DrawDebugSphere(PrimComp->GetWorld(), StartLoc, 5.f, 12, FColor::Magenta, false, DebugTime);
					DrawDebugSphere(PrimComp->GetWorld(), EndLoc, 5.f, 12, FColor::Blue, false, DebugTime);
					if (GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugTime, FColor::Green, FString::Printf(TEXT("Found Weapon: %s on %s"), *PrimComp->GetName(), *AttachedActor->GetName())); // 简化屏幕消息
				}
				return PrimComp; // 找到即返回
			}
			else if (bDebug) // 如果是调试模式，记录哪个组件缺少插槽
			{
				UE_LOG(LogWeaponHitNotify, Verbose, TEXT("    Checked Comp: '%s'. Socket '%s': %s. Socket '%s': %s"), // 使用 Verbose 级别
					*PrimComp->GetName(), *StartSocketName.ToString(), bHasStartSocket ? TEXT("Exists") : TEXT("Missing"), *EndSocketName.ToString(), bHasEndSocket ? TEXT("Exists") : TEXT("Missing"));
			}
		}
	}

	// 如果遍历完所有附加 Actor 及其组件都未找到
	UE_LOG(LogWeaponHitNotify, Error, TEXT("FindAttachedWeaponComponent: Weapon component with sockets '%s' AND '%s' not found attached to '%s'."),
			*StartSocketName.ToString(),*EndSocketName.ToString(), *OwnerActor->GetName());
	if (bDebug && GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugTime, FColor::Red, FString::Printf(TEXT("Weapon component with sockets '%s' AND '%s' not found attached to '%s'."), // 简化屏幕消息
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
 *        执行扫描检测，过滤命中结果，对首次命中的敌人播放蒙太奇。
 *        扫描范围为当前帧武器起点到终点。
 */
void UWeaponHitNotify::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	// 检查 OwnerActor 和缓存的武器组件是否有效
	AActor* OwnerActor = MeshComp ? MeshComp->GetOwner() : nullptr;
	// 不再需要检查 PreviousEndLocation.IsZero()
	if (!OwnerActor || !CachedWeaponMeshComp)
	{
		if (!CachedWeaponMeshComp) // 仅在缓存丢失时记录错误
		{
			UE_LOG(LogWeaponHitNotify, Error, TEXT("NotifyTick: Cached Weapon component is NULL."));
			if (GEngine && bDebugTrace) GEngine->AddOnScreenDebugMessage(-1, DebugDisplayTime, FColor::Red, TEXT("NotifyTick: Cached Weapon component is NULL."));
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
		// PreviousEndLocation 不再需要更新
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

	// 定义扫描的起点和终点为当前帧的武器插槽位置
	FVector TraceStart = CurrentStartLocation;
	FVector TraceEnd = CurrentEndLocation;

	// 获取要使用的追踪通道类型
	TEnumAsByte<ETraceTypeQuery> TraceType = UEngineTypes::ConvertToTraceType(TraceChannel);

	// 根据 TraceRadius 选择球体扫描或射线扫描
	if (TraceRadius > 0.0f)
	{
		// 球形扫描 (现在扫描的是剑身当前位置)
		bHit = UKismetSystemLibrary::SphereTraceMulti(
			CachedWeaponMeshComp->GetWorld(),
			TraceStart,
			TraceEnd,
			TraceRadius,
			TraceType,
			false,
			ActorsToIgnore,
			bDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, // 调试线现在代表剑身
			HitResults,
			true,
			FLinearColor::Red,
			FLinearColor::Green,
			DebugDisplayTime
		);
	}
	else
	{
		// 射线扫描 (现在扫描的是剑身当前位置)
		bHit = UKismetSystemLibrary::LineTraceMulti(
			CachedWeaponMeshComp->GetWorld(),
			TraceStart,
			TraceEnd,
			TraceType,
			false,
			ActorsToIgnore,
			bDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, // 调试线现在代表剑身
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
			// 检查命中的 Actor 是否有效
			if (!HitActor)
			{
				continue;
			}

			// --- 过滤：只处理 EnemyBaseCharacter 派生类 ---
			AEnemyBaseCharacter* EnemyCharacter = Cast<AEnemyBaseCharacter>(HitActor);
			if (!EnemyCharacter)
			{
				// 如果不是敌人，可以选择记录日志或直接跳过
				// UE_LOG(LogWeaponHitNotify, Verbose, TEXT("Weapon Hit ignored: %s (Not an EnemyBaseCharacter)"), *HitActor->GetName());
				continue;
			}

			// --- 检查是否已在本轮通知中处理过此敌人 ---
			if (HitActors.Contains(EnemyCharacter))
			{
				// UE_LOG(LogWeaponHitNotify, Verbose, TEXT("Weapon Hit ignored: %s (Already processed in this notify)"), *EnemyCharacter->GetName());
				continue; // 跳过已记录的敌人
			}

			// --- 处理首次命中的敌人 ---
			HitActors.Add(EnemyCharacter); // 将有效且首次命中的敌人添加到列表

			UE_LOG(LogWeaponHitNotify, Log, TEXT("Enemy Hit Added: %s (Trace Channel: %s)"), *EnemyCharacter->GetName(), *UEnum::GetValueAsString(TraceChannel.GetValue()));
			if (GEngine && bDebugTrace)
			{
				// 在命中点绘制一个绿色的调试球体
				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 10.f, 12, FColor::Green, false, DebugDisplayTime);
				GEngine->AddOnScreenDebugMessage(-1, DebugDisplayTime, FColor::Green, FString::Printf(TEXT("武器命中敌人: %s (首次)"), *EnemyCharacter->GetName()));
			}

			// --- 尝试播放受击蒙太奇 ---
			if (HitReactionMontage)
			{
				UAnimInstance* AnimInstance = EnemyCharacter->GetMesh() ? EnemyCharacter->GetMesh()->GetAnimInstance() : nullptr;
				if (AnimInstance && !AnimInstance->Montage_IsPlaying(HitReactionMontage))
				{
					UE_LOG(LogWeaponHitNotify, Log, TEXT("  Playing Hit Reaction Montage '%s' on '%s'"), *HitReactionMontage->GetName(), *EnemyCharacter->GetName());
					AnimInstance->Montage_Play(HitReactionMontage, 1.0f);
				}
				// else if (AnimInstance && AnimInstance->Montage_IsPlaying(HitReactionMontage)) { /* Log already playing */ }
				// else if (!AnimInstance) { /* Log no anim instance */ }
			}
			else
			{
				UE_LOG(LogWeaponHitNotify, Verbose, TEXT("  No HitReactionMontage specified for this notify."));
			}

			// --- 伤害逻辑 (未来添加) ---
			/*
			if (bApplyDamage)
			{
				// ...
			}
			*/
		}
	}

	// PreviousEndLocation 不再需要更新
	// PreviousEndLocation = CurrentEndLocation;
}

/**
 * @brief 通知状态结束时调用。
 *        清理命中列表和缓存。
 */
void UWeaponHitNotify::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	// 清空已命中列表
	HitActors.Empty();
	// 重置上一帧位置 (虽然不再用于 Tick 起点，但保持清理习惯)
	PreviousEndLocation = FVector::ZeroVector;
	// 清除缓存的武器组件指针
	CachedWeaponMeshComp = nullptr;
	UE_LOG(LogWeaponHitNotify, Log, TEXT("WeaponHitNotify::NotifyEnd - Cleared HitActors and Cache"));
}
