/* 
 * Copyright (C) 2025 [Wang]
 * ... (Copy license header) ...
 */
/*
* 文件名: AIWeaponHitNotify.cpp
* 功能描述： 实现 AI 武器命中通知 UAIWeaponHitNotify 的逻辑。
*            在动画播放期间，根据武器插槽执行扫描检测，处理对玩家的命中逻辑，
*            包括应用基于 AI 攻击力的伤害、播放玩家受击动画和施加 Gameplay Tag。
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
#include "Characters/EnemyBaseCharacter.h" // AI 角色
#include "Characters/AnabiosisOriginCharacter.h" // 玩家角色
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Controller.h"
#include "Engine/DamageEvents.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h" // Include for Ability System functions
#include "Attributes/EnemyAttributeSet.h" // AI 属性集
#include "Attributes/AnabiosisAttributeSet.h" // 玩家属性集 (可能需要检查防御等)
#include "Containers/Set.h" 
#include "GameplayTagContainer.h" // Include Gameplay Tag Container

// 定义日志类别
DEFINE_LOG_CATEGORY(LogAIWeaponHitNotify);

// 辅助函数声明 (可以共享或复制) - 确保这个函数也被定义了
UPrimitiveComponent* FindAttachedWeaponComponent_AI(const AActor* OwnerActor, FName StartSocketName, FName EndSocketName, bool bDebug, float DebugTime);


UAIWeaponHitNotify::UAIWeaponHitNotify()
{
	// 初始化武器插槽名称
	WeaponStartSocketName = FName("weapon_start");
	WeaponEndSocketName = FName("weapon_end");
	// 初始化扫描参数
	TraceRadius = 2.0f;
	TraceChannel = COLLISION_PLAYER; // 默认检测玩家通道
	// 初始化调试选项
	bDebugTrace = true;
	DebugDisplayTime = 2.0f;
	// 初始化伤害和效果参数
	bApplyDamage = true;
	BaseDamage = 5.0f; // 默认基础伤害 (备选)
	FallbackPlayerHitReactionMontage = nullptr; // 默认无备选玩家受击蒙太奇
	HitReactTag = FGameplayTag::RequestGameplayTag(FName("State.HitReact")); // 默认设置受击 Tag
	// 初始化缓存指针
	CachedWeaponMeshComp = nullptr;
}

// 辅助函数定义
UPrimitiveComponent* FindAttachedWeaponComponent_AI(const AActor* OwnerActor, FName StartSocketName, FName EndSocketName, bool bDebug, float DebugTime)
{
	if (!OwnerActor)
	{
		UE_LOG(LogAIWeaponHitNotify, Error, TEXT("查找武器组件：OwnerActor 为空"));
		return nullptr;
	}

	// 优先检查 OwnerActor 自身的组件
	TArray<UPrimitiveComponent*> OwnerComponents;
	OwnerActor->GetComponents<UPrimitiveComponent>(OwnerComponents);
	for (UPrimitiveComponent* PrimComp : OwnerComponents)
	{
		if (!PrimComp) continue;
		bool bHasStartSocket = PrimComp->DoesSocketExist(StartSocketName);
		bool bHasEndSocket = PrimComp->DoesSocketExist(EndSocketName);
		if (bHasStartSocket && bHasEndSocket)
		{
			if (bDebug)
			{
				FVector StartLoc = PrimComp->GetSocketLocation(StartSocketName);
				FVector EndLoc = PrimComp->GetSocketLocation(EndSocketName);
				DrawDebugSphere(PrimComp->GetWorld(), StartLoc, 5.f, 12, FColor::Magenta, false, DebugTime);
				DrawDebugSphere(PrimComp->GetWorld(), EndLoc, 5.f, 12, FColor::Blue, false, DebugTime);
				if (GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugTime, FColor::Cyan, FString::Printf(TEXT("找到武器 (拥有者)：%s"), *PrimComp->GetName()));
			}
			return PrimComp; 
		}
	}

	// 然后检查附加的子 Actor
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
				if (bDebug)
				{
					FVector StartLoc = PrimComp->GetSocketLocation(StartSocketName);
					FVector EndLoc = PrimComp->GetSocketLocation(EndSocketName);
					DrawDebugSphere(PrimComp->GetWorld(), StartLoc, 5.f, 12, FColor::Magenta, false, DebugTime);
					DrawDebugSphere(PrimComp->GetWorld(), EndLoc, 5.f, 12, FColor::Blue, false, DebugTime);
					if (GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugTime, FColor::Cyan, FString::Printf(TEXT("找到武器 (附加)：%s 位于 %s"), *PrimComp->GetName(), *AttachedActor->GetName()));
				}
				return PrimComp; 
			}
		}
	}

	UE_LOG(LogAIWeaponHitNotify, Error, TEXT("查找武器组件：在 '%s' 或其附加物上未找到同时包含插槽 '%s' 和 '%s' 的武器组件。"),
			*OwnerActor->GetName(), *StartSocketName.ToString(), *EndSocketName.ToString());
	if (bDebug && GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugTime, FColor::Red, FString::Printf(TEXT("未找到包含插槽 '%s' 和 '%s' 的武器组件。"),
			*StartSocketName.ToString(), *EndSocketName.ToString()));

	return nullptr; 
}


void UAIWeaponHitNotify::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	if (!MeshComp)
	{
		UE_LOG(LogAIWeaponHitNotify, Error, TEXT("通知开始：MeshComp 为空"));
		return;
	}
	AActor* OwnerActor = MeshComp->GetOwner(); // AI Character
	if (!OwnerActor)
	{
		UE_LOG(LogAIWeaponHitNotify, Error, TEXT("通知开始：OwnerActor (AI) 为空"));
		return;
	}

	HitActors.Empty(); 
	CachedWeaponMeshComp = nullptr; 

	// 使用辅助函数查找武器组件
	CachedWeaponMeshComp = FindAttachedWeaponComponent_AI(OwnerActor, WeaponStartSocketName, WeaponEndSocketName, bDebugTrace, DebugDisplayTime);

	if (!CachedWeaponMeshComp)
	{
		// 错误已在 FindAttachedWeaponComponent_AI 中记录
		return;
	}
}

void UAIWeaponHitNotify::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	AActor* OwnerActor = MeshComp ? MeshComp->GetOwner() : nullptr; // AI Character
	if (!OwnerActor || !CachedWeaponMeshComp)
	{
		// NotifyBegin 中应已处理或记录错误
		return;
	}

	FVector CurrentStartLocation = CachedWeaponMeshComp->GetSocketLocation(WeaponStartSocketName);
	FVector CurrentEndLocation = CachedWeaponMeshComp->GetSocketLocation(WeaponEndSocketName);

	if (bDebugTrace)
	{
		DrawDebugSphere(CachedWeaponMeshComp->GetWorld(), CurrentStartLocation, 5.f, 12, FColor::Magenta, false, 0.f); 
		DrawDebugSphere(CachedWeaponMeshComp->GetWorld(), CurrentEndLocation, 5.f, 12, FColor::Blue, false, 0.f);    
	}

	if (CurrentStartLocation.IsZero() || CurrentEndLocation.IsZero())
	{
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

			// --- 处理首次命中的玩家 Character ---
			HitActors.Add(HitPlayerCharacter); 

			UE_LOG(LogAIWeaponHitNotify, Log, TEXT("AI 武器命中玩家：%s (本轮通知首次命中)"), *HitPlayerCharacter->GetName());
			if (bDebugTrace)
			{
				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 10.f, 12, FColor::Yellow, false, DebugDisplayTime); // 用黄色表示命中玩家
				if (GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugDisplayTime, FColor::Yellow, FString::Printf(TEXT("AI 命中：%s"), *HitPlayerCharacter->GetName()));
			}

			// --- 施加 Gameplay Tag ---
			UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitPlayerCharacter);
			if (TargetASC && HitReactTag.IsValid())
			{
				// --- 只添加 Tag，由 GA_HitReact 处理后续逻辑 ---
				TargetASC->AddLooseGameplayTag(HitReactTag);
				UE_LOG(LogAIWeaponHitNotify, Log, TEXT("  向玩家 %s 添加了 Gameplay Tag: %s"), *HitPlayerCharacter->GetName(), *HitReactTag.ToString());
				// ---------------------------------------------
			}
			else if (!TargetASC)
			{
				UE_LOG(LogAIWeaponHitNotify, Warning, TEXT("  无法添加 Gameplay Tag：目标玩家 %s 没有 AbilitySystemComponent。"), *HitPlayerCharacter->GetName());
			}
			else // Tag is not valid
			{
				UE_LOG(LogAIWeaponHitNotify, Warning, TEXT("  无法添加 Gameplay Tag：HitReactTag 未在通知 %s 中设置。"), *GetName());
			}

            // --- 确认没有播放蒙太奇的代码 ---
            // UAnimMontage* MontageToPlay = nullptr;
            // ... (No logic here to find or play montage) ...
            // ---------------------------------

			// --- 应用伤害 ---
			float AppliedDamage = 0.0f; 
			if (bApplyDamage) 
			{
				ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerActor); // AI Character
				AController* OwnerController = OwnerCharacter ? OwnerCharacter->GetController() : nullptr; // AI Controller

				// 获取攻击者 (AI) 的攻击力
				float DamageToApply = BaseDamage; // 默认使用 BaseDamage 作为备选
				AEnemyBaseCharacter* AttackerEnemy = Cast<AEnemyBaseCharacter>(OwnerActor);
				if(AttackerEnemy)
				{
					UAbilitySystemComponent* AttackerASC = AttackerEnemy->GetAbilitySystemComponent();
					if (AttackerASC)
					{
						const UEnemyAttributeSet* AttackerAttributeSet = AttackerASC->GetSet<UEnemyAttributeSet>();
						if (AttackerAttributeSet)
						{
							DamageToApply = AttackerAttributeSet->GetAttackPower(); // 使用 AI 的攻击力
						}
						else
						{
							UE_LOG(LogAIWeaponHitNotify, Warning, TEXT("  攻击者 AI '%s' 没有 EnemyAttributeSet。回退到基础伤害 (%.1f)。"), *AttackerEnemy->GetName(), BaseDamage);
						}
					}
					else
					{
						UE_LOG(LogAIWeaponHitNotify, Warning, TEXT("  攻击者 AI '%s' 没有 AbilitySystemComponent。回退到基础伤害 (%.1f)。"), *AttackerEnemy->GetName(), BaseDamage);
					}
				}
				else
				{
					UE_LOG(LogAIWeaponHitNotify, Warning, TEXT("  攻击者 '%s' 不是 EnemyBaseCharacter。回退到基础伤害 (%.1f)。"), *OwnerActor->GetName(), BaseDamage);
				}


				if (OwnerController && DamageToApply > 0.f)
				{
					FPointDamageEvent DamageEvent(DamageToApply, Hit, (TraceEnd - TraceStart).GetSafeNormal(), UDamageType::StaticClass());
					// 对玩家角色应用伤害
					AppliedDamage = HitPlayerCharacter->TakeDamage(DamageToApply, DamageEvent, OwnerController, OwnerActor);

					UE_LOG(LogAIWeaponHitNotify, Log, TEXT("  AI 对玩家 %s 应用了 %.1f 点伤害 (请求 %.1f)"), *HitPlayerCharacter->GetName(), AppliedDamage, DamageToApply);
					if (bDebugTrace && GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugDisplayTime, FColor::Red, FString::Printf(TEXT("AI 伤害：%.1f -> %s"), AppliedDamage, *HitPlayerCharacter->GetName()));
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
	// 清理状态
	HitActors.Empty(); 
	CachedWeaponMeshComp = nullptr; 
}
