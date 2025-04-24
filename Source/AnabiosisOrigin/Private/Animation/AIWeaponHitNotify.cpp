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
// #include "GameFramework/CharacterMovementComponent.h" // Removed
// #include "TimerManager.h" // Removed

// 定义日志类别
DEFINE_LOG_CATEGORY(LogAIWeaponHitNotify);

// --- 移除辅助函数：恢复玩家移动 ---
// void UAIWeaponHitNotify::RestorePlayerMovement(TWeakObjectPtr<ACharacter> CharacterPtr) { ... }
// ---------------------------------

// 辅助函数声明 (保持不变)
UPrimitiveComponent* FindAttachedWeaponComponent_AI(const AActor* OwnerActor, FName StartSocketName, FName EndSocketName, bool bDebug, float DebugTime);


UAIWeaponHitNotify::UAIWeaponHitNotify()
{
	WeaponStartSocketName = FName("weapon_start");
	WeaponEndSocketName = FName("weapon_end");
	TraceRadius = 2.0f;
	TraceChannel = COLLISION_PLAYER; 
	bDebugTrace = false; // Default to false
	DebugDisplayTime = 2.0f;
	bApplyDamage = true;
	BaseDamage = 5.0f; 
	FallbackPlayerHitReactionMontage = nullptr; 
	HitReactTag = FGameplayTag::RequestGameplayTag(FName("State.HitReact")); 
	CachedWeaponMeshComp = nullptr;
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

	UE_LOG(LogAIWeaponHitNotify, Warning, TEXT("查找武器组件：在 '%s' 或其附加物上未找到同时包含插槽 '%s' 和 '%s' 的武器组件。"),
			*OwnerActor->GetName(), *StartSocketName.ToString(), *EndSocketName.ToString());

	return nullptr; 
}


void UAIWeaponHitNotify::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	AActor* OwnerActor = MeshComp ? MeshComp->GetOwner() : nullptr; 
	if (!OwnerActor)
	{
		UE_LOG(LogAIWeaponHitNotify, Error, TEXT("通知开始：OwnerActor (AI) 为空"));
		return;
	}

	HitActors.Empty(); 
	CachedWeaponMeshComp = nullptr; 
	// CharacterMovementTimers.Empty(); // Removed

	CachedWeaponMeshComp = FindAttachedWeaponComponent_AI(OwnerActor, WeaponStartSocketName, WeaponEndSocketName, bDebugTrace, DebugDisplayTime);
}

void UAIWeaponHitNotify::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
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
		// Keep this warning
		UE_LOG(LogAIWeaponHitNotify, Warning, TEXT("通知 Tick：插槽 '%s' 或 '%s' 在组件 '%s' 上返回零位置。跳过扫描。"),
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

	if (TraceRadius > 0.0f)
	{
		bHit = UKismetSystemLibrary::SphereTraceMulti(
			CachedWeaponMeshComp->GetWorld(), TraceStart, TraceEnd, TraceRadius, TraceType, false, ActorsToIgnore,
			bDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, 
			HitResults, true, 
			FLinearColor::Red, FLinearColor::Green, DebugDisplayTime); 
	}
	else
	{
		bHit = UKismetSystemLibrary::LineTraceMulti(
			CachedWeaponMeshComp->GetWorld(), TraceStart, TraceEnd, TraceType, false, ActorsToIgnore,
			bDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
			HitResults, true,
			FLinearColor::Red, FLinearColor::Green, DebugDisplayTime);
	}

	// --- 处理命中结果 ---
	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			AAnabiosisOriginCharacter* HitPlayerCharacter = Cast<AAnabiosisOriginCharacter>(HitActor); 
			if (!HitPlayerCharacter || HitActors.Contains(HitPlayerCharacter)) 
			{
				continue; 
			}

			HitActors.Add(HitPlayerCharacter); 

			// UE_LOG(LogAIWeaponHitNotify, Log, TEXT("AI 武器命中玩家：%s (本轮通知首次命中)"), *HitPlayerCharacter->GetName()); // Optional Log

			// --- 施加 Gameplay Tag ---
			UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitPlayerCharacter);
			if (TargetASC && HitReactTag.IsValid())
			{
				TargetASC->AddLooseGameplayTag(HitReactTag);
				// UE_LOG(LogAIWeaponHitNotify, Log, TEXT("  向玩家 %s 添加了 Gameplay Tag: %s"), *HitPlayerCharacter->GetName(), *HitReactTag.ToString()); // Optional Log
			}
			else if (!TargetASC)
			{
				UE_LOG(LogAIWeaponHitNotify, Warning, TEXT("  无法添加 Gameplay Tag：目标玩家 %s 没有 AbilitySystemComponent。"), *HitPlayerCharacter->GetName());
			}
			else 
			{
				UE_LOG(LogAIWeaponHitNotify, Warning, TEXT("  无法添加 Gameplay Tag：HitReactTag 未在通知 %s 中设置。"), *GetName());
			}

			// --- 播放蒙太奇 ---
			UAnimMontage* MontageToPlay = HitPlayerCharacter->GetHitReactionMontage();
			if (!MontageToPlay)
			{
				MontageToPlay = FallbackPlayerHitReactionMontage; // Use fallback
			}

			if (MontageToPlay)
			{
				UAnimInstance* AnimInstance = HitPlayerCharacter->GetMesh() ? HitPlayerCharacter->GetMesh()->GetAnimInstance() : nullptr;
				if (AnimInstance)
				{
					const float MontagePlayRate = 1.0f;
					const float MontageDuration = AnimInstance->Montage_Play(MontageToPlay, MontagePlayRate);
					// UE_LOG(LogAIWeaponHitNotify, Log, TEXT("  播放蒙太奇 %s (时长: %.2f) 在玩家 %s 上。"), *MontageToPlay->GetName(), MontageDuration, *HitPlayerCharacter->GetName()); // Optional Log

					// --- 移除移动禁用和定时器逻辑 ---
					// if (MontageDuration > 0.f) { ... }
					// ---------------------------------
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
			if (bApplyDamage) 
			{
				ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerActor); 
				AController* OwnerController = OwnerCharacter ? OwnerCharacter->GetController() : nullptr; 

				float DamageToApply = BaseDamage; 
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



				if (OwnerController && DamageToApply > 0.f)
				{
					FPointDamageEvent DamageEvent(DamageToApply, Hit, (TraceEnd - TraceStart).GetSafeNormal(), UDamageType::StaticClass());
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
	HitActors.Empty(); 
	CachedWeaponMeshComp = nullptr; 
}
