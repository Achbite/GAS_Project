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
/*
* 文件名: WeaponHitNotify.cpp
* 功能描述： 实现动画通知 UWeaponHitNotify 的逻辑。
*            在动画播放期间，根据武器插槽执行扫描检测，处理命中逻辑，包括应用伤害和播放受击动画。
* 结构：
* - 构造函数：初始化扫描参数、调试选项和默认值。
* - FindAttachedWeaponComponent：辅助函数，用于查找附加的武器组件。
* - NotifyBegin：通知开始时调用，清理状态，查找并缓存武器组件。
* - NotifyTick：通知 Tick 时调用，获取插槽位置，执行扫描（球形或线性），处理命中结果（防止重复命中、播放受击动画、应用伤害）。
* - NotifyEnd：通知结束时调用，清理状态。
*/

#include "Animation/WeaponHitNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequenceBase.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h" // 包含 GEngine
#include "Kismet/KismetSystemLibrary.h" // 包含扫描函数
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "CollisionQueryParams.h"
#include "Characters/EnemyBaseCharacter.h" // 包含敌人角色头文件
#include "Characters/AnabiosisOriginCharacter.h" // 包含玩家角色头文件
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Controller.h"
#include "Engine/DamageEvents.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h" // Include for Ability System functions
#include "Attributes/EnemyAttributeSet.h" // 包含敌人属性集头文件
#include "Attributes/AnabiosisAttributeSet.h" // 包含玩家属性集头文件
#include "Containers/Set.h" // 包含 TSet
#include "GameplayTagContainer.h" // Include Gameplay Tag Container

// 定义日志类别
DEFINE_LOG_CATEGORY(LogWeaponHitNotify);

UWeaponHitNotify::UWeaponHitNotify()
{
	// 初始化武器插槽名称
	WeaponStartSocketName = FName("weapon_start");
	WeaponEndSocketName = FName("weapon_end");
	// 初始化扫描参数
	TraceRadius = 2.0f;
	TraceChannel = COLLISION_ENEMY; // 使用预定义的敌人碰撞通道
	// 初始化调试选项
	bDebugTrace = true;
	DebugDisplayTime = 2.0f;
	// 初始化伤害和效果参数
	bApplyDamage = true;
	BaseDamage = 10.0f; // 默认基础伤害
	HitReactionMontage = nullptr; // 默认无备选受击蒙太奇
	// 初始化缓存指针
	CachedWeaponMeshComp = nullptr;
	HitReactTag = FGameplayTag::RequestGameplayTag(FName("State.HitReact")); // Ensure default is correct
}

/**
 * @brief 辅助函数：查找附加到 OwnerActor 上的、包含指定插槽的第一个 PrimitiveComponent。
 * @param OwnerActor 拥有此动画通知的角色 Actor。
 * @param StartSocketName 武器起点的插槽名称。
 * @param EndSocketName 武器终点的插槽名称。
 * @param bDebug 是否启用调试日志和绘制。
 * @param DebugTime 调试信息显示时长。
 * @return 找到的武器组件指针，如果未找到则返回 nullptr。
 */
UPrimitiveComponent* FindAttachedWeaponComponent(const AActor* OwnerActor, FName StartSocketName, FName EndSocketName, bool bDebug, float DebugTime)
{
	// 检查 OwnerActor 是否有效
	if (!OwnerActor)
	{
		UE_LOG(LogWeaponHitNotify, Error, TEXT("查找武器组件：OwnerActor 为空"));
		return nullptr;
	}

	// 优先检查 OwnerActor 自身的组件 (如果武器直接附加在角色骨骼上)
	TArray<UPrimitiveComponent*> OwnerComponents;
	OwnerActor->GetComponents<UPrimitiveComponent>(OwnerComponents);
	for (UPrimitiveComponent* PrimComp : OwnerComponents)
	{
		if (!PrimComp) continue;
		// 检查组件是否存在指定的两个插槽
		bool bHasStartSocket = PrimComp->DoesSocketExist(StartSocketName);
		bool bHasEndSocket = PrimComp->DoesSocketExist(EndSocketName);
		if (bHasStartSocket && bHasEndSocket)
		{
			// 如果启用调试，绘制插槽位置
			if (bDebug)
			{
				FVector StartLoc = PrimComp->GetSocketLocation(StartSocketName);
				FVector EndLoc = PrimComp->GetSocketLocation(EndSocketName);
				DrawDebugSphere(PrimComp->GetWorld(), StartLoc, 5.f, 12, FColor::Magenta, false, DebugTime);
				DrawDebugSphere(PrimComp->GetWorld(), EndLoc, 5.f, 12, FColor::Blue, false, DebugTime);
				if (GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugTime, FColor::Cyan, FString::Printf(TEXT("找到武器 (拥有者)：%s"), *PrimComp->GetName()));
			}
			return PrimComp; // 找到即返回
		}
	}

	// 然后检查附加到 OwnerActor 的子 Actor 上的组件
	TArray<AActor*> AttachedActors;
	OwnerActor->GetAttachedActors(AttachedActors, true); // true 表示递归查找所有层级的附加 Actor
	for (AActor* AttachedActor : AttachedActors)
	{
		if (!AttachedActor) continue;

		TArray<UPrimitiveComponent*> PrimitiveComponents;
		AttachedActor->GetComponents<UPrimitiveComponent>(PrimitiveComponents);

		for (UPrimitiveComponent* PrimComp : PrimitiveComponents)
		{
			if (!PrimComp) continue;

			// 检查组件是否存在指定的两个插槽
			bool bHasStartSocket = PrimComp->DoesSocketExist(StartSocketName);
			bool bHasEndSocket = PrimComp->DoesSocketExist(EndSocketName);

			if (bHasStartSocket && bHasEndSocket)
			{
				// 如果启用调试，绘制插槽位置
				if (bDebug)
				{
					FVector StartLoc = PrimComp->GetSocketLocation(StartSocketName);
					FVector EndLoc = PrimComp->GetSocketLocation(EndSocketName);
					DrawDebugSphere(PrimComp->GetWorld(), StartLoc, 5.f, 12, FColor::Magenta, false, DebugTime);
					DrawDebugSphere(PrimComp->GetWorld(), EndLoc, 5.f, 12, FColor::Blue, false, DebugTime);
					if (GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugTime, FColor::Cyan, FString::Printf(TEXT("找到武器 (附加)：%s 位于 %s"), *PrimComp->GetName(), *AttachedActor->GetName()));
				}
				return PrimComp; // 找到即返回
			}
		}
	}

	// 如果遍历完所有组件都未找到，记录错误
	UE_LOG(LogWeaponHitNotify, Error, TEXT("查找武器组件：在 '%s' 或其附加物上未找到同时包含插槽 '%s' 和 '%s' 的武器组件。"),
			*OwnerActor->GetName(), *StartSocketName.ToString(), *EndSocketName.ToString());
	if (bDebug && GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugTime, FColor::Red, FString::Printf(TEXT("未找到包含插槽 '%s' 和 '%s' 的武器组件。"),
			*StartSocketName.ToString(), *EndSocketName.ToString()));

	return nullptr; // 未找到武器组件
}

void UWeaponHitNotify::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	// 检查 MeshComp 是否有效
	if (!MeshComp)
	{
		UE_LOG(LogWeaponHitNotify, Error, TEXT("通知开始：MeshComp 为空"));
		return;
	}
	// 获取拥有者 Actor
	AActor* OwnerActor = MeshComp->GetOwner();
	if (!OwnerActor)
	{
		UE_LOG(LogWeaponHitNotify, Error, TEXT("通知开始：OwnerActor 为空"));
		return;
	}

	// 清理上一轮的状态
	HitActors.Empty(); // 清空已命中 Actor 集合
	CachedWeaponMeshComp = nullptr; // 清空缓存的武器组件指针

	// 查找并缓存武器组件
	CachedWeaponMeshComp = FindAttachedWeaponComponent(OwnerActor, WeaponStartSocketName, WeaponEndSocketName, bDebugTrace, DebugDisplayTime);

	// 如果未找到武器组件，FindAttachedWeaponComponent 内部已记录错误，这里不再重复记录
	if (!CachedWeaponMeshComp)
	{
		return;
	}
}

void UWeaponHitNotify::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	// 检查 OwnerActor 和缓存的武器组件是否有效
	AActor* OwnerActor = MeshComp ? MeshComp->GetOwner() : nullptr;
	if (!OwnerActor || !CachedWeaponMeshComp)
	{
		// NotifyBegin 中应已处理或记录错误，Tick 中不再重复记录
		return;
	}

	// 从缓存的武器组件获取当前插槽位置
	FVector CurrentStartLocation = CachedWeaponMeshComp->GetSocketLocation(WeaponStartSocketName);
	FVector CurrentEndLocation = CachedWeaponMeshComp->GetSocketLocation(WeaponEndSocketName);

	// 调试绘制当前插槽位置 (如果启用)
	if (bDebugTrace)
	{
		DrawDebugSphere(CachedWeaponMeshComp->GetWorld(), CurrentStartLocation, 5.f, 12, FColor::Magenta, false, 0.f); // 起点用洋红色
		DrawDebugSphere(CachedWeaponMeshComp->GetWorld(), CurrentEndLocation, 5.f, 12, FColor::Blue, false, 0.f);    // 终点用蓝色
	}

	// 检查获取的插槽位置是否有效 (避免无效扫描)
	if (CurrentStartLocation.IsZero() || CurrentEndLocation.IsZero())
	{
		UE_LOG(LogWeaponHitNotify, Warning, TEXT("通知 Tick：插槽 '%s' 或 '%s' 在组件 '%s' 上返回零位置。跳过扫描。"),
				*WeaponStartSocketName.ToString(), *WeaponEndSocketName.ToString(), *CachedWeaponMeshComp->GetName());
		return;
	}

	// --- 执行扫描检测 ---
	// 设置扫描参数
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwnerActor); // 忽略拥有者自身
	// 如果武器组件属于不同的 Actor (例如，附加的武器 Actor)，也忽略它
	if (CachedWeaponMeshComp->GetOwner() != OwnerActor)
	{
		QueryParams.AddIgnoredActor(CachedWeaponMeshComp->GetOwner());
	}
	QueryParams.bTraceComplex = true; // 使用复杂碰撞进行精确检测

	TArray<FHitResult> HitResults; // 存储命中结果
	bool bHit = false; // 标记是否发生命中

	// KismetSystemLibrary 的扫描函数需要一个 Actor 数组来忽略
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(OwnerActor);
	if (CachedWeaponMeshComp->GetOwner() != OwnerActor)
	{
		ActorsToIgnore.Add(CachedWeaponMeshComp->GetOwner());
	}

	FVector TraceStart = CurrentStartLocation; // 扫描起点
	FVector TraceEnd = CurrentEndLocation;   // 扫描终点
	TEnumAsByte<ETraceTypeQuery> TraceType = UEngineTypes::ConvertToTraceType(TraceChannel); // 将碰撞通道转换为 TraceTypeQuery

	// 根据扫描半径选择使用球形扫描还是线性扫描
	if (TraceRadius > 0.0f)
	{
		// 执行球形扫描 (SphereTraceMulti 用于检测多个目标)
		bHit = UKismetSystemLibrary::SphereTraceMulti(
			CachedWeaponMeshComp->GetWorld(), TraceStart, TraceEnd, TraceRadius, TraceType, false, ActorsToIgnore,
			bDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, // 根据 bDebugTrace 决定是否绘制调试线
			HitResults, true, // 忽略自身 Actor
			FLinearColor::Red, FLinearColor::Green, DebugDisplayTime); // 调试线颜色和持续时间
	}
	else
	{
		// 执行线性扫描 (LineTraceMulti 用于检测多个目标)
		bHit = UKismetSystemLibrary::LineTraceMulti(
			CachedWeaponMeshComp->GetWorld(), TraceStart, TraceEnd, TraceType, false, ActorsToIgnore,
			bDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
			HitResults, true,
			FLinearColor::Red, FLinearColor::Green, DebugDisplayTime);
	}

	// --- 处理命中结果 ---
	if (bHit)
	{
		// 遍历所有命中结果
		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			// 检查命中的 Actor 是否有效，是否是 Character 类型，以及是否已在本轮通知中处理过
			ACharacter* HitCharacter = Cast<ACharacter>(HitActor);
			if (!HitCharacter || HitActors.Contains(HitCharacter)) // 使用 TSet::Contains 检查是否已处理
			{
				continue; // 如果无效或已处理，则跳过
			}

			// --- 处理首次命中的 Character ---
			HitActors.Add(HitCharacter); // 将其添加到已处理集合

			UE_LOG(LogWeaponHitNotify, Log, TEXT("武器命中：%s (本轮通知首次命中)"), *HitCharacter->GetName());
			// 如果启用调试，绘制命中点
			if (bDebugTrace)
			{
				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 10.f, 12, FColor::Green, false, DebugDisplayTime);
				if (GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugDisplayTime, FColor::Green, FString::Printf(TEXT("命中：%s"), *HitCharacter->GetName()));
			}

			// --- 施加 Gameplay Tag ---
			UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitCharacter);
			if (TargetASC && HitReactTag.IsValid())
			{
				// --- 只添加 Tag，由 GA_HitReact 处理后续逻辑 ---
				TargetASC->AddLooseGameplayTag(HitReactTag);
				UE_LOG(LogWeaponHitNotify, Log, TEXT("  向 %s 添加了 Gameplay Tag: %s"), *HitCharacter->GetName(), *HitReactTag.ToString());
				// ---------------------------------------------
			}
			else if (!TargetASC)
			{
				UE_LOG(LogWeaponHitNotify, Warning, TEXT("  无法添加 Gameplay Tag：目标 %s 没有 AbilitySystemComponent。"), *HitCharacter->GetName());
			}
			else // Tag is not valid
			{
				UE_LOG(LogWeaponHitNotify, Warning, TEXT("  无法添加 Gameplay Tag：HitReactTag 未在通知 %s 中设置。"), *GetName());
			}

			// --- 应用伤害 ---
			float AppliedDamage = 0.0f; // 记录实际应用的伤害
			if (bApplyDamage) // 检查是否配置为应用伤害
			{
				ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerActor); // 获取攻击者角色
				AController* OwnerController = OwnerCharacter ? OwnerCharacter->GetController() : nullptr; // 获取攻击者控制器

				// 获取攻击者的攻击力作为伤害值
				float DamageToApply = BaseDamage; // 默认使用 BaseDamage 作为备选
				// 尝试获取攻击者的属性集以获取攻击力
				// 假设攻击者是玩家角色 AAnabiosisOriginCharacter
				AAnabiosisOriginCharacter* AttackerCharacter = Cast<AAnabiosisOriginCharacter>(OwnerActor);
				if (AttackerCharacter)
				{
					UAbilitySystemComponent* AttackerASC = AttackerCharacter->GetAbilitySystemComponent();
					if (AttackerASC)
					{
						// 获取玩家属性集
						const UAnabiosisAttributeSet* AttackerAttributeSet = AttackerASC->GetSet<UAnabiosisAttributeSet>();
						if (AttackerAttributeSet)
						{
							DamageToApply = AttackerAttributeSet->GetAttackPower(); // 使用玩家的攻击力
						}
						else
						{
							UE_LOG(LogWeaponHitNotify, Warning, TEXT("  攻击者 '%s' 没有 AnabiosisAttributeSet。回退到基础伤害 (%.1f)。"), *AttackerCharacter->GetName(), BaseDamage);
						}
					}
					else
					{
						UE_LOG(LogWeaponHitNotify, Warning, TEXT("  攻击者 '%s' 没有 AbilitySystemComponent。回退到基础伤害 (%.1f)。"), *AttackerCharacter->GetName(), BaseDamage);
					}
				}
				else
				{
					// 如果攻击者不是玩家角色 (例如是敌人)，可以尝试获取敌人属性集
					AEnemyBaseCharacter* AttackerEnemy = Cast<AEnemyBaseCharacter>(OwnerActor);
					if(AttackerEnemy)
					{
						UAbilitySystemComponent* AttackerASC = AttackerEnemy->GetAbilitySystemComponent();
						if (AttackerASC)
						{
							const UEnemyAttributeSet* AttackerAttributeSet = AttackerASC->GetSet<UEnemyAttributeSet>();
							if (AttackerAttributeSet)
							{
								DamageToApply = AttackerAttributeSet->GetAttackPower(); // 使用敌人的攻击力
							}
							else
							{
								UE_LOG(LogWeaponHitNotify, Warning, TEXT("  攻击者 '%s' 没有 EnemyAttributeSet。回退到基础伤害 (%.1f)。"), *AttackerEnemy->GetName(), BaseDamage);
							}
						}
						else
						{
							UE_LOG(LogWeaponHitNotify, Warning, TEXT("  攻击者 '%s' 没有 AbilitySystemComponent。回退到基础伤害 (%.1f)。"), *AttackerEnemy->GetName(), BaseDamage);
						}
					}
					else
					{
						// 如果攻击者既不是玩家也不是敌人，记录警告并回退到 BaseDamage
						UE_LOG(LogWeaponHitNotify, Warning, TEXT("  攻击者 '%s' 不是玩家或敌人角色。回退到基础伤害 (%.1f)。"), *OwnerActor->GetName(), BaseDamage);
					}
				}


				// 确保有攻击者控制器和伤害值才应用伤害
				if (OwnerController && DamageToApply > 0.f)
				{
					// 创建点伤害事件
					FPointDamageEvent DamageEvent(DamageToApply, Hit, (TraceEnd - TraceStart).GetSafeNormal(), UDamageType::StaticClass());
					// 调用命中角色的 TakeDamage 函数
					AppliedDamage = HitCharacter->TakeDamage(DamageToApply, DamageEvent, OwnerController, OwnerActor);

					UE_LOG(LogWeaponHitNotify, Log, TEXT("  对 %s 应用了 %.1f 点伤害 (请求 %.1f)"), *HitCharacter->GetName(), AppliedDamage, DamageToApply);
					// 如果启用调试，在屏幕上显示伤害信息
					if (bDebugTrace && GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugDisplayTime, FColor::Orange, FString::Printf(TEXT("伤害：%.1f -> %s"), AppliedDamage, *HitCharacter->GetName()));
				}
				else if (!OwnerController)
				{
					UE_LOG(LogWeaponHitNotify, Warning, TEXT("  无法应用伤害：攻击者控制器 OwnerController 为空。"));
				}
			}
		}
	}
}

void UWeaponHitNotify::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	// 清理状态
	HitActors.Empty(); // 清空已命中 Actor 集合
	CachedWeaponMeshComp = nullptr; // 清空缓存的武器组件指针
}

