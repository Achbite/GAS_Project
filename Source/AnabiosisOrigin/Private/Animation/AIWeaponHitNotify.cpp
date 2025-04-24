/* 
 * Copyright (C) 2025 [Wang]
 * ... (Copyleft header) ...
 */
/*
* 文件名: AIWeaponHitNotify.cpp
* 功能描述： 实现 AI 武器命中通知 UAIWeaponHitNotify 的逻辑。
*            在动画播放期间，根据武器插槽执行扫描检测，处理对玩家的命中逻辑，
*            包括应用伤害、播放玩家受击动画和施加 Tag。
*/

#include "Animation/AIWeaponHitNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequenceBase.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h" 
#include "Kismet/KismetSystemLibrary.h" 
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "CollisionQueryParams.h"
#include "Characters/EnemyBaseCharacter.h" 
#include "Characters/AnabiosisOriginCharacter.h" 
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Controller.h"
#include "Engine/DamageEvents.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h" 
#include "Attributes/EnemyAttributeSet.h" 
#include "Attributes/AnabiosisAttributeSet.h" 
#include "Containers/Set.h" 
#include "GameplayTagContainer.h" 
// #include "GameFramework/CharacterMovementComponent.h" // 已移除
// #include "TimerManager.h" // 已移除

// 定义日志类别
DEFINE_LOG_CATEGORY(LogAIWeaponHitNotify);

// --- 移除辅助函数：恢复玩家移动 ---
// void UAIWeaponHitNotify::RestorePlayerMovement(TWeakObjectPtr<ACharacter> CharacterPtr) { ... }
// ---------------------------------

// 辅助函数声明 (保持不变)
UPrimitiveComponent* FindAttachedWeaponComponent_AI(const AActor* OwnerActor, FName StartSocketName, FName EndSocketName, bool bDebug, float DebugTime);


UAIWeaponHitNotify::UAIWeaponHitNotify()
{
	WeaponStartSocketName = FName("weapon_start"); // 武器起始插槽名
	WeaponEndSocketName = FName("weapon_end"); // 武器结束插槽名
	TraceRadius = 2.0f; // 追踪半径
	TraceChannel = COLLISION_PLAYER; // 追踪通道，默认为玩家
	bDebugTrace = false; // 默认禁用调试追踪
	DebugDisplayTime = 2.0f; // 调试显示时间
	bApplyDamage = true; // 默认应用伤害
	BaseDamage = 5.0f; // 基础伤害值
	FallbackPlayerHitReactionMontage = nullptr; // 备用玩家受击反应蒙太奇
	HitReactTag = FGameplayTag::RequestGameplayTag(FName("State.HitReact")); // 受击反应标签
	CachedWeaponMeshComp = nullptr; // 缓存的武器网格组件
}

// 辅助函数定义 (保持不变，但移除调试日志中的 GEngine 调用)
UPrimitiveComponent* FindAttachedWeaponComponent_AI(const AActor* OwnerActor, FName StartSocketName, FName EndSocketName, bool bDebug, float DebugTime)
{
	if (!OwnerActor)
	{
		UE_LOG(LogAIWeaponHitNotify, Error, TEXT("查找武器组件：OwnerActor 为空"));
		return nullptr;
	}

	TArray<UPrimitiveComponent*> OwnerComponents;
	OwnerActor->GetComponents<UPrimitiveComponent>(OwnerComponents);
	for (UPrimitiveComponent* PrimComp : OwnerComponents)
	{
		if (!PrimComp) continue;
		bool bHasStartSocket = PrimComp->DoesSocketExist(StartSocketName);
		bool bHasEndSocket = PrimComp->DoesSocketExist(EndSocketName);
		if (bHasStartSocket && bHasEndSocket)
		{
			// 找到包含两个插槽的组件
			return PrimComp; 
		}
	}

	// 如果在 Owner 自身上找不到，则检查附加的 Actor
	TArray<AActor*> AttachedActors;
	OwnerActor->GetAttachedActors(AttachedActors, true); // 递归检查
	for (AActor* AttachedActor : AttachedActors)
	{
		if (!AttachedActor) continue;
		TArray<UPrimitiveComponent*> PrimitiveComponents;
		AttachedActor->GetComponents<UPrimitiveComponent>(PrimitiveComponents);
		for (UPrimitiveComponent* PrimComp : PrimitiveComponents)
		{
			if (!PrimComp) continue;
			bool bHasStartSocket = PrimComp->DoesSocketExist(StartSocketName);
			bool bHasEndSocket = PrimComp->DoesSocketExist(EndSocketName);
			if (bHasStartSocket && bHasEndSocket)
			{
				// 在附加 Actor 上找到包含两个插槽的组件
				return PrimComp; 
			}
		}
	}

	// 保留此警告，因为它指示了潜在的设置问题
	UE_LOG(LogAIWeaponHitNotify, Warning, TEXT("查找武器组件：在 '%s' 或其附加物上未找到同时包含插槽 '%s' 和 '%s' 的武器组件。"),
			*OwnerActor->GetName(), *StartSocketName.ToString(), *EndSocketName.ToString());

	return nullptr; // 未找到
}


void UAIWeaponHitNotify::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	AActor* OwnerActor = MeshComp ? MeshComp->GetOwner() : nullptr; // 获取拥有者 Actor (AI)
	if (!OwnerActor)
	{
		UE_LOG(LogAIWeaponHitNotify, Error, TEXT("通知开始：OwnerActor (AI) 为空"));
		return;
	}

	HitActors.Empty(); // 清空已命中 Actor 列表
	CachedWeaponMeshComp = nullptr; // 重置缓存的武器组件

	// 查找并缓存武器组件
	CachedWeaponMeshComp = FindAttachedWeaponComponent_AI(OwnerActor, WeaponStartSocketName, WeaponEndSocketName, bDebugTrace, DebugDisplayTime);
}

void UAIWeaponHitNotify::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	AActor* OwnerActor = MeshComp ? MeshComp->GetOwner() : nullptr; // 获取拥有者 Actor (AI)
	if (!OwnerActor || !CachedWeaponMeshComp) // 如果没有拥有者或武器组件，则返回
	{
		return;
	}

	// 获取武器插槽的当前位置
	FVector CurrentStartLocation = CachedWeaponMeshComp->GetSocketLocation(WeaponStartSocketName);
	FVector CurrentEndLocation = CachedWeaponMeshComp->GetSocketLocation(WeaponEndSocketName);

	// 检查插槽位置是否有效
	if (CurrentStartLocation.IsZero() || CurrentEndLocation.IsZero())
	{
		// 保留此警告
		UE_LOG(LogAIWeaponHitNotify, Warning, TEXT("通知 Tick：插槽 '%s' 或 '%s' 在组件 '%s' 上返回零位置。跳过扫描。"),
				*WeaponStartSocketName.ToString(), *WeaponEndSocketName.ToString(), *CachedWeaponMeshComp->GetName());
		return;
	}

	// --- 执行扫描检测 ---
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwnerActor); // 忽略 AI 自身
	if (CachedWeaponMeshComp->GetOwner() != OwnerActor) // 如果武器组件不属于 AI Actor，也忽略武器的拥有者
	{
		QueryParams.AddIgnoredActor(CachedWeaponMeshComp->GetOwner());
	}
	QueryParams.bTraceComplex = true; // 使用复杂碰撞

	TArray<FHitResult> HitResults; // 存储命中结果
	bool bHit = false; // 标记是否发生命中

	// 设置要忽略的 Actor 列表
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(OwnerActor);
	if (CachedWeaponMeshComp->GetOwner() != OwnerActor)
	{
		ActorsToIgnore.Add(CachedWeaponMeshComp->GetOwner());
	}

	// 设置追踪参数
	FVector TraceStart = CurrentStartLocation; // 追踪起点
	FVector TraceEnd = CurrentEndLocation;   // 追踪终点
	TEnumAsByte<ETraceTypeQuery> TraceType = UEngineTypes::ConvertToTraceType(TraceChannel); // 转换碰撞通道为追踪类型

	// KismetSystemLibrary 函数已包含基于 bDebugTrace 的调试绘制逻辑
	if (TraceRadius > 0.0f) // 球形扫描
	{
		bHit = UKismetSystemLibrary::SphereTraceMulti(
			CachedWeaponMeshComp->GetWorld(), TraceStart, TraceEnd, TraceRadius, TraceType, false, ActorsToIgnore,
			bDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, // 调试绘制
			HitResults, true, // 忽略自身
			FLinearColor::Red, FLinearColor::Green, DebugDisplayTime); // 调试颜色和时间
	}
	else // 线形扫描
	{
		bHit = UKismetSystemLibrary::LineTraceMulti(
			CachedWeaponMeshComp->GetWorld(), TraceStart, TraceEnd, TraceType, false, ActorsToIgnore,
			bDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, // 调试绘制
			HitResults, true, // 忽略自身
			FLinearColor::Red, FLinearColor::Green, DebugDisplayTime); // 调试颜色和时间
	}

	// --- 处理命中结果 ---
	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor(); // 获取命中的 Actor
			AAnabiosisOriginCharacter* HitPlayerCharacter = Cast<AAnabiosisOriginCharacter>(HitActor); // 尝试转换为玩家角色
			
			// 检查是否是有效的玩家角色，并且在本轮通知中尚未命中过
			if (!HitPlayerCharacter || HitActors.Contains(HitPlayerCharacter)) 
			{
				continue; // 跳过无效目标或已处理的目标
			}

			// 将命中的玩家添加到集合中，防止重复处理
			HitActors.Add(HitPlayerCharacter); 

			// --- 施加 Gameplay Tag ---
			UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitPlayerCharacter); // 获取目标玩家的 ASC
			if (TargetASC && HitReactTag.IsValid()) // 如果目标有 ASC 且 Tag 有效
			{
				TargetASC->AddLooseGameplayTag(HitReactTag); // 添加松散 Gameplay Tag
			}
			else if (!TargetASC)
			{
				UE_LOG(LogAIWeaponHitNotify, Warning, TEXT("  无法添加 Gameplay Tag：目标玩家 %s 没有 AbilitySystemComponent。"), *HitPlayerCharacter->GetName());
			}
			else // Tag 无效
			{
				UE_LOG(LogAIWeaponHitNotify, Warning, TEXT("  无法添加 Gameplay Tag：HitReactTag 未在通知 %s 中设置。"), *GetName());
			}

			// --- 播放蒙太奇 ---
			UAnimMontage* MontageToPlay = HitPlayerCharacter->GetHitReactionMontage(); // 尝试获取玩家角色定义的受击蒙太奇
			if (!MontageToPlay) // 如果玩家角色没有定义，则使用通知中设置的备用蒙太奇
			{
				MontageToPlay = FallbackPlayerHitReactionMontage; // 使用备用蒙太奇
			}

			if (MontageToPlay) // 如果找到了要播放的蒙太奇
			{
				UAnimInstance* AnimInstance = HitPlayerCharacter->GetMesh() ? HitPlayerCharacter->GetMesh()->GetAnimInstance() : nullptr; // 获取玩家的动画实例
				if (AnimInstance) // 如果动画实例有效
				{
					const float MontagePlayRate = 1.0f; // 播放速率
					const float MontageDuration = AnimInstance->Montage_Play(MontageToPlay, MontagePlayRate); // 播放蒙太奇并获取时长
				}
				else
				{
					UE_LOG(LogAIWeaponHitNotify, Warning, TEXT("  无法播放蒙太奇：AnimInstance 无效。"));
				}
			}
			else
			{
				UE_LOG(LogAIWeaponHitNotify, Warning, TEXT("  未找到可播放的受击蒙太奇。"));
			}
			// -----------------------------

			// --- 应用伤害 ---
			if (bApplyDamage) // 如果设置了应用伤害
			{
				ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerActor); // 获取攻击者 Character
				AController* OwnerController = OwnerCharacter ? OwnerCharacter->GetController() : nullptr; // 获取攻击者控制器

				float DamageToApply = BaseDamage; // 默认使用基础伤害
				// 尝试从攻击者 (Enemy) 的属性集获取攻击力
				AEnemyBaseCharacter* AttackerEnemy = Cast<AEnemyBaseCharacter>(OwnerActor);
				if(AttackerEnemy)
				{
					UAbilitySystemComponent* AttackerASC = AttackerEnemy->GetAbilitySystemComponent();
					if (AttackerASC)
					{
						const UEnemyAttributeSet* AttackerAttributeSet = AttackerASC->GetSet<UEnemyAttributeSet>();
						if (AttackerAttributeSet)
						{
							DamageToApply = AttackerAttributeSet->GetAttackPower(); // 使用敌人属性集中的攻击力
						}
					}
				}

				// 确保控制器有效且伤害值大于 0
				if (OwnerController && DamageToApply > 0.f)
				{
					// 创建点伤害事件
					FPointDamageEvent DamageEvent(DamageToApply, Hit, (TraceEnd - TraceStart).GetSafeNormal(), UDamageType::StaticClass());
					// 应用伤害
					float AppliedDamage = HitPlayerCharacter->TakeDamage(DamageToApply, DamageEvent, OwnerController, OwnerActor);
				}
				else if (!OwnerController)
				{
					UE_LOG(LogAIWeaponHitNotify, Warning, TEXT("  无法应用伤害：攻击者 AI 控制器 OwnerController 为空。"));
				}
			}
		}
	}
}

void UAIWeaponHitNotify::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	HitActors.Empty(); // 清空已命中 Actor 列表
	CachedWeaponMeshComp = nullptr; // 清除缓存的武器组件指针
}
