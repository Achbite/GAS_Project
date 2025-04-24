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
*            在动画播放期间，根据武器插槽执行扫描检测，处理命中逻辑，包括应用伤害、播放受击动画和施加 Tag。
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
DEFINE_LOG_CATEGORY(LogWeaponHitNotify);

// --- 移除辅助函数：恢复玩家移动 ---
// void UWeaponHitNotify::RestorePlayerMovement(TWeakObjectPtr<ACharacter> CharacterPtr) { ... }
// ---------------------------------

UWeaponHitNotify::UWeaponHitNotify()
{
	WeaponStartSocketName = FName("weapon_start");
	WeaponEndSocketName = FName("weapon_end");
	TraceRadius = 2.0f;
	TraceChannel = COLLISION_ENEMY; 
	bDebugTrace = false; // 默认禁用调试追踪
	DebugDisplayTime = 2.0f;
	bApplyDamage = true;
	BaseDamage = 10.0f; 
	HitReactionMontage = nullptr; 
	CachedWeaponMeshComp = nullptr;
	HitReactTag = FGameplayTag::RequestGameplayTag(FName("State.HitReact")); 
}

// 辅助函数：查找附加的武器组件 (保持不变，但移除调试日志中的 GEngine 调用)
UPrimitiveComponent* FindAttachedWeaponComponent(const AActor* OwnerActor, FName StartSocketName, FName EndSocketName, bool bDebug, float DebugTime)
{
	if (!OwnerActor)
	{
		UE_LOG(LogWeaponHitNotify, Error, TEXT("查找武器组件：OwnerActor 为空"));
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
			return PrimComp; 
		}
	}

	TArray<AActor*> AttachedActors;
	OwnerActor->GetAttachedActors(AttachedActors, true); 
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
				return PrimComp; 
			}
		}
	}

	// 保留此警告，因为它指示了潜在的设置问题
	UE_LOG(LogWeaponHitNotify, Warning, TEXT("查找武器组件：在 '%s' 或其附加物上未找到同时包含插槽 '%s' 和 '%s' 的武器组件。"),
			*OwnerActor->GetName(), *StartSocketName.ToString(), *EndSocketName.ToString());

	return nullptr; 
}

void UWeaponHitNotify::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	AActor* OwnerActor = MeshComp ? MeshComp->GetOwner() : nullptr;
	if (!OwnerActor)
	{
		UE_LOG(LogWeaponHitNotify, Error, TEXT("通知开始：OwnerActor 为空"));
		return;
	}

	HitActors.Empty(); 
	CachedWeaponMeshComp = nullptr; 
	// CharacterMovementTimers.Empty(); // 已移除

	CachedWeaponMeshComp = FindAttachedWeaponComponent(OwnerActor, WeaponStartSocketName, WeaponEndSocketName, bDebugTrace, DebugDisplayTime);
}

void UWeaponHitNotify::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	AActor* OwnerActor = MeshComp ? MeshComp->GetOwner() : nullptr;
	if (!OwnerActor || !CachedWeaponMeshComp)
	{
		return;
	}

	FVector CurrentStartLocation = CachedWeaponMeshComp->GetSocketLocation(WeaponStartSocketName);
	FVector CurrentEndLocation = CachedWeaponMeshComp->GetSocketLocation(WeaponEndSocketName);

	if (CurrentStartLocation.IsZero() || CurrentEndLocation.IsZero())
	{
		// 保留此警告，因为它指示了设置问题
		UE_LOG(LogWeaponHitNotify, Warning, TEXT("通知 Tick：插槽 '%s' 或 '%s' 在组件 '%s' 上返回零位置。跳过扫描。"),
				*WeaponStartSocketName.ToString(), *WeaponEndSocketName.ToString(), *CachedWeaponMeshComp->GetName());
		return;
	}

	// --- 执行扫描检测 ---
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwnerActor); 
	if (CachedWeaponMeshComp->GetOwner() != OwnerActor)
	{
		QueryParams.AddIgnoredActor(CachedWeaponMeshComp->GetOwner());
	}
	QueryParams.bTraceComplex = true; 

	TArray<FHitResult> HitResults; 
	bool bHit = false; 

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(OwnerActor);
	if (CachedWeaponMeshComp->GetOwner() != OwnerActor)
	{
		ActorsToIgnore.Add(CachedWeaponMeshComp->GetOwner());
	}

	FVector TraceStart = CurrentStartLocation; 
	FVector TraceEnd = CurrentEndLocation;   
	TEnumAsByte<ETraceTypeQuery> TraceType = UEngineTypes::ConvertToTraceType(TraceChannel); 

	// KismetSystemLibrary 函数已包含基于 bDebugTrace 的调试绘制逻辑
	if (TraceRadius > 0.0f)
	{
		bHit = UKismetSystemLibrary::SphereTraceMulti(
			CachedWeaponMeshComp->GetWorld(), TraceStart, TraceEnd, TraceRadius, TraceType, false, ActorsToIgnore,
			bDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, // 调试绘制
			HitResults, true, 
			FLinearColor::Red, FLinearColor::Green, DebugDisplayTime); 
	}
	else
	{
		bHit = UKismetSystemLibrary::LineTraceMulti(
			CachedWeaponMeshComp->GetWorld(), TraceStart, TraceEnd, TraceType, false, ActorsToIgnore,
			bDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, // 调试绘制
			HitResults, true,
			FLinearColor::Red, FLinearColor::Green, DebugDisplayTime);
	}

	// --- 处理命中结果 ---
	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			ACharacter* HitCharacter = Cast<ACharacter>(HitActor);
			if (!HitCharacter || HitActors.Contains(HitCharacter)) 
			{
				continue; 
			}

			HitActors.Add(HitCharacter); 

			// --- 施加 Gameplay Tag ---
			UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitCharacter);
			if (TargetASC && HitReactTag.IsValid())
			{
				TargetASC->AddLooseGameplayTag(HitReactTag);
			}
			else if (!TargetASC)
			{
				UE_LOG(LogWeaponHitNotify, Warning, TEXT("  无法添加 Gameplay Tag：目标 %s 没有 AbilitySystemComponent。"), *HitCharacter->GetName());
			}
			else 
			{
				UE_LOG(LogWeaponHitNotify, Warning, TEXT("  无法添加 Gameplay Tag：HitReactTag 未在通知 %s 中设置。"), *GetName());
			}

			// --- 播放蒙太奇 ---
			UAnimMontage* MontageToPlay = nullptr;
			AEnemyBaseCharacter* EnemyChar = Cast<AEnemyBaseCharacter>(HitCharacter);
			AAnabiosisOriginCharacter* PlayerChar = Cast<AAnabiosisOriginCharacter>(HitCharacter); 

			if (EnemyChar)
			{
				MontageToPlay = EnemyChar->GetHitReactionMontage();
			}
			else if (PlayerChar) 
			{
				MontageToPlay = PlayerChar->GetHitReactionMontage();
			}

			if (!MontageToPlay)
			{
				MontageToPlay = HitReactionMontage; // 使用备用蒙太奇
			}

			if (MontageToPlay)
			{
				UAnimInstance* AnimInstance = HitCharacter->GetMesh() ? HitCharacter->GetMesh()->GetAnimInstance() : nullptr;
				if (AnimInstance)
				{
					const float MontagePlayRate = 1.0f;
					const float MontageDuration = AnimInstance->Montage_Play(MontageToPlay, MontagePlayRate);
				}
				else
				{
					UE_LOG(LogWeaponHitNotify, Warning, TEXT("  无法播放蒙太奇：AnimInstance 无效。"));
				}
			}
			else
			{
				UE_LOG(LogWeaponHitNotify, Warning, TEXT("  未找到可播放的受击蒙太奇。"));
			}
			// -----------------------------

			// --- 应用伤害 ---
			if (bApplyDamage) 
			{
				ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerActor); 
				AController* OwnerController = OwnerCharacter ? OwnerCharacter->GetController() : nullptr; 

				float DamageToApply = BaseDamage; 
				// 尝试从攻击者获取攻击力 (玩家或敌人)
				AAnabiosisOriginCharacter* AttackerCharacter = Cast<AAnabiosisOriginCharacter>(OwnerActor);
				if (AttackerCharacter)
				{
					UAbilitySystemComponent* AttackerASC = AttackerCharacter->GetAbilitySystemComponent();
					if (AttackerASC)
					{
						const UAnabiosisAttributeSet* AttackerAttributeSet = AttackerASC->GetSet<UAnabiosisAttributeSet>();
						if (AttackerAttributeSet)
						{
							DamageToApply = AttackerAttributeSet->GetAttackPower(); 
						}
					}
				}
				else
				{
					AEnemyBaseCharacter* AttackerEnemy = Cast<AEnemyBaseCharacter>(OwnerActor);
					if(AttackerEnemy)
					{
						UAbilitySystemComponent* AttackerASC = AttackerEnemy->GetAbilitySystemComponent();
						if (AttackerASC)
						{
							const UEnemyAttributeSet* AttackerAttributeSet = AttackerASC->GetSet<UEnemyAttributeSet>();
							if (AttackerAttributeSet)
							{
								DamageToApply = AttackerAttributeSet->GetAttackPower(); 
							}
						}
					}
				}

				if (OwnerController && DamageToApply > 0.f)
				{
					FPointDamageEvent DamageEvent(DamageToApply, Hit, (TraceEnd - TraceStart).GetSafeNormal(), UDamageType::StaticClass());
					float AppliedDamage = HitCharacter->TakeDamage(DamageToApply, DamageEvent, OwnerController, OwnerActor);
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
	HitActors.Empty(); 
	CachedWeaponMeshComp = nullptr; 
}

