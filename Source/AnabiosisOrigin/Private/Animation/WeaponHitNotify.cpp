/**
 * @file WeaponHitNotify.cpp
 * @brief 实现 UWeaponHitNotify 类，用于在动画播放期间执行武器命中检测。
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
#include "Characters/AnabiosisOriginCharacter.h" // 包含玩家角色头文件
#include "Animation/AnimInstance.h"      
#include "Animation/AnimMontage.h"       
#include "GameFramework/DamageType.h"   
#include "GameFramework/Controller.h"   
#include "Engine/DamageEvents.h"      
#include "AbilitySystemComponent.h"      
#include "Attributes/EnemyAttributeSet.h" 
#include "Attributes/AnabiosisAttributeSet.h" // 包含玩家属性集头文件
#include "Containers/Set.h" // 包含 TSet

// 定义日志类别
DEFINE_LOG_CATEGORY(LogWeaponHitNotify);

UWeaponHitNotify::UWeaponHitNotify()
{
	WeaponStartSocketName = FName("weapon_start");
	WeaponEndSocketName = FName("weapon_end");
	TraceRadius = 2.0f;
	TraceChannel = COLLISION_ENEMY; 
	bDebugTrace = true; 
	DebugDisplayTime = 2.0f;
	bApplyDamage = true; 
	BaseDamage = 10.0f;
	HitReactionMontage = nullptr; 
	CachedWeaponMeshComp = nullptr; 
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
	if (!OwnerActor)
	{
		UE_LOG(LogWeaponHitNotify, Error, TEXT("FindAttachedWeaponComponent: OwnerActor is NULL"));
		return nullptr;
	}

	UE_LOG(LogWeaponHitNotify, Verbose, TEXT("FindAttachedWeaponComponent: Searching for weapon component with sockets '%s' and '%s' attached to '%s'."), *StartSocketName.ToString(), *EndSocketName.ToString(), *OwnerActor->GetName());

	TArray<AActor*> AttachedActors;
	OwnerActor->GetAttachedActors(AttachedActors, true); // true 表示递归查找所有附加的 Actor

	// 优先检查 OwnerActor 自身的组件 (如果武器直接附加在角色身上)
	TArray<UPrimitiveComponent*> OwnerComponents;
	OwnerActor->GetComponents<UPrimitiveComponent>(OwnerComponents);
	for (UPrimitiveComponent* PrimComp : OwnerComponents)
	{
		if (!PrimComp) continue;
		bool bHasStartSocket = PrimComp->DoesSocketExist(StartSocketName);
		bool bHasEndSocket = PrimComp->DoesSocketExist(EndSocketName);
		if (bHasStartSocket && bHasEndSocket)
		{
			UE_LOG(LogWeaponHitNotify, Verbose, TEXT("  Found Weapon Component (Owner): '%s'"), *PrimComp->GetName());
			if (bDebug)
			{
				FVector StartLoc = PrimComp->GetSocketLocation(StartSocketName);
				FVector EndLoc = PrimComp->GetSocketLocation(EndSocketName);
				DrawDebugSphere(PrimComp->GetWorld(), StartLoc, 5.f, 12, FColor::Magenta, false, DebugTime);
				DrawDebugSphere(PrimComp->GetWorld(), EndLoc, 5.f, 12, FColor::Blue, false, DebugTime);
				if (GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugTime, FColor::Cyan, FString::Printf(TEXT("Found Weapon (Owner): %s"), *PrimComp->GetName()));
			}
			return PrimComp;
		}
	}


	// 然后检查附加的 Actor
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
				UE_LOG(LogWeaponHitNotify, Verbose, TEXT("  Found Weapon Component (Attached): '%s' on Actor '%s'"), *PrimComp->GetName(), *AttachedActor->GetName());
				if (bDebug)
				{
					FVector StartLoc = PrimComp->GetSocketLocation(StartSocketName);
					FVector EndLoc = PrimComp->GetSocketLocation(EndSocketName);
					DrawDebugSphere(PrimComp->GetWorld(), StartLoc, 5.f, 12, FColor::Magenta, false, DebugTime);
					DrawDebugSphere(PrimComp->GetWorld(), EndLoc, 5.f, 12, FColor::Blue, false, DebugTime);
					if (GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugTime, FColor::Cyan, FString::Printf(TEXT("Found Weapon (Attached): %s on %s"), *PrimComp->GetName(), *AttachedActor->GetName()));
				}
				return PrimComp; // 找到即返回
			}
		}
	}

	// 如果遍历完所有组件都未找到
	UE_LOG(LogWeaponHitNotify, Error, TEXT("FindAttachedWeaponComponent: Weapon component with sockets '%s' AND '%s' not found on or attached to '%s'."),
			*StartSocketName.ToString(),*EndSocketName.ToString(), *OwnerActor->GetName());
	if (bDebug && GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugTime, FColor::Red, FString::Printf(TEXT("Weapon component with sockets '%s' AND '%s' not found."),
			*StartSocketName.ToString(),*EndSocketName.ToString()));

	return nullptr; // 未找到武器组件
}

void UWeaponHitNotify::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	UE_LOG(LogWeaponHitNotify, Verbose, TEXT("WeaponHitNotify::NotifyBegin - Anim: %s"), *GetNameSafe(Animation));

	if (!MeshComp)
	{
		UE_LOG(LogWeaponHitNotify, Error, TEXT("NotifyBegin: MeshComp is NULL"));
		return;
	}
	AActor* OwnerActor = MeshComp->GetOwner();
	if (!OwnerActor)
	{
		UE_LOG(LogWeaponHitNotify, Error, TEXT("NotifyBegin: OwnerActor is NULL"));
		return;
	}

	// 清理状态
	HitActors.Empty();
	CachedWeaponMeshComp = nullptr;

	// 查找并缓存武器组件
	CachedWeaponMeshComp = FindAttachedWeaponComponent(OwnerActor, WeaponStartSocketName, WeaponEndSocketName, bDebugTrace, DebugDisplayTime);
	
	if (!CachedWeaponMeshComp)
	{
		// FindAttachedWeaponComponent 内部已记录错误
		return; 
	}
	
	UE_LOG(LogWeaponHitNotify, Verbose, TEXT("NotifyBegin: Cached weapon component '%s'"), *CachedWeaponMeshComp->GetName());
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

	// 调试绘制当前插槽位置
	if (bDebugTrace)
	{
		DrawDebugSphere(CachedWeaponMeshComp->GetWorld(), CurrentStartLocation, 5.f, 12, FColor::Magenta, false, 0.f); 
		DrawDebugSphere(CachedWeaponMeshComp->GetWorld(), CurrentEndLocation, 5.f, 12, FColor::Blue, false, 0.f);    
	}

	// 检查获取的插槽位置是否有效 (避免无效扫描)
	if (CurrentStartLocation.IsZero() || CurrentEndLocation.IsZero())
	{
		UE_LOG(LogWeaponHitNotify, Warning, TEXT("NotifyTick: Socket '%s' or '%s' returned zero location on component '%s'. Skipping trace."),
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

	TArray<AActor*> ActorsToIgnore; // KismetSystemLibrary 需要
	ActorsToIgnore.Add(OwnerActor);
	if (CachedWeaponMeshComp->GetOwner() != OwnerActor)
	{
		ActorsToIgnore.Add(CachedWeaponMeshComp->GetOwner());
	}

	FVector TraceStart = CurrentStartLocation;
	FVector TraceEnd = CurrentEndLocation;
	TEnumAsByte<ETraceTypeQuery> TraceType = UEngineTypes::ConvertToTraceType(TraceChannel);

	// 根据 TraceRadius 选择扫描类型
	if (TraceRadius > 0.0f)
	{
		bHit = UKismetSystemLibrary::SphereTraceMulti(
			CachedWeaponMeshComp->GetWorld(), TraceStart, TraceEnd, TraceRadius, TraceType, false, ActorsToIgnore,
			bDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitResults, true,
			FLinearColor::Red, FLinearColor::Green, DebugDisplayTime);
	}
	else
	{
		bHit = UKismetSystemLibrary::LineTraceMulti(
			CachedWeaponMeshComp->GetWorld(), TraceStart, TraceEnd, TraceType, false, ActorsToIgnore,
			bDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitResults, true,
			FLinearColor::Red, FLinearColor::Green, DebugDisplayTime);
	}

	// --- 处理命中结果 ---
	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			// 检查 Actor 是否有效，是否是 Character，以及是否已在本轮通知中处理过
			ACharacter* HitCharacter = Cast<ACharacter>(HitActor); 
			if (!HitCharacter || HitActors.Contains(HitCharacter)) // 使用 TSet::Contains 效率更高
			{
				continue; 
			}

			// --- 处理首次命中的 Character ---
			HitActors.Add(HitCharacter); // 添加到已处理集合

			UE_LOG(LogWeaponHitNotify, Log, TEXT("Weapon Hit: %s (First Hit This Notify)"), *HitCharacter->GetName());
			if (bDebugTrace)
			{
				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 10.f, 12, FColor::Green, false, DebugDisplayTime);
				if (GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugDisplayTime, FColor::Green, FString::Printf(TEXT("Hit: %s"), *HitCharacter->GetName()));
			}

			// --- 获取并播放受击蒙太奇 ---
			UAnimMontage* MontageToPlay = nullptr;
			AEnemyBaseCharacter* EnemyCharacter = Cast<AEnemyBaseCharacter>(HitCharacter);
			if (EnemyCharacter)
			{
				MontageToPlay = EnemyCharacter->GetHitReactionMontage();
				if (!MontageToPlay)
				{
					 UE_LOG(LogWeaponHitNotify, Verbose, TEXT("  Enemy '%s' has no specific montage, checking fallback."), *EnemyCharacter->GetName());
					 MontageToPlay = this->HitReactionMontage; // 使用 Notify 自身的蒙太奇作为备选
				}
			}
			else
			{
				 // 如果命中的不是 EnemyBaseCharacter，也尝试使用备选蒙太奇
				 UE_LOG(LogWeaponHitNotify, Verbose, TEXT("  Hit Character '%s' is not EnemyBaseCharacter, checking fallback."), *HitCharacter->GetName());
				 MontageToPlay = this->HitReactionMontage;
			}

			if (MontageToPlay) 
			{
				UAnimInstance* AnimInstance = HitCharacter->GetMesh() ? HitCharacter->GetMesh()->GetAnimInstance() : nullptr;
				if (AnimInstance && !AnimInstance->Montage_IsPlaying(MontageToPlay)) // 避免重复播放同一蒙太奇
				{
					UE_LOG(LogWeaponHitNotify, Verbose, TEXT("  Playing Montage '%s' on '%s'"), *MontageToPlay->GetName(), *HitCharacter->GetName());
					AnimInstance->Montage_Play(MontageToPlay, 1.0f);
				}
				else if (AnimInstance && AnimInstance->Montage_IsPlaying(MontageToPlay))
				{
					UE_LOG(LogWeaponHitNotify, Verbose, TEXT("  Montage '%s' already playing on '%s'"), *MontageToPlay->GetName(), *HitCharacter->GetName());
				}
			}
			else 
			{ 
				UE_LOG(LogWeaponHitNotify, Verbose, TEXT("  No Hit Reaction Montage found for '%s'."), *HitCharacter->GetName());
			}

			// --- 应用伤害 ---
			float AppliedDamage = 0.0f; 
			if (bApplyDamage)
			{
				ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerActor);
				AController* OwnerController = OwnerCharacter ? OwnerCharacter->GetController() : nullptr;
				
				// 获取攻击者的 AttackPower
				float DamageToApply = BaseDamage; // 默认使用 BaseDamage 作为备选
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
							UE_LOG(LogWeaponHitNotify, Verbose, TEXT("  Using Attacker's AttackPower: %.1f"), DamageToApply);
						}
						else
						{
							UE_LOG(LogWeaponHitNotify, Warning, TEXT("  Attacker '%s' has no AnabiosisAttributeSet. Falling back to BaseDamage (%.1f)."), *AttackerCharacter->GetName(), BaseDamage);
						}
					}
					else
					{
						UE_LOG(LogWeaponHitNotify, Warning, TEXT("  Attacker '%s' has no AbilitySystemComponent. Falling back to BaseDamage (%.1f)."), *AttackerCharacter->GetName(), BaseDamage);
					}
				}
				else
				{
					// 如果攻击者不是玩家角色，也回退到 BaseDamage
					UE_LOG(LogWeaponHitNotify, Warning, TEXT("  Attacker '%s' is not AnabiosisOriginCharacter. Falling back to BaseDamage (%.1f)."), *OwnerActor->GetName(), BaseDamage);
				}


				if (OwnerController && DamageToApply > 0.f) // 确保有伤害值才应用
				{
					FPointDamageEvent DamageEvent(DamageToApply, Hit, (TraceEnd - TraceStart).GetSafeNormal(), UDamageType::StaticClass());
					AppliedDamage = HitCharacter->TakeDamage(DamageToApply, DamageEvent, OwnerController, OwnerActor);

					UE_LOG(LogWeaponHitNotify, Log, TEXT("  Applied %.1f damage (requested %.1f) to %s"), AppliedDamage, DamageToApply, *HitCharacter->GetName());
					if (bDebugTrace && GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugDisplayTime, FColor::Orange, FString::Printf(TEXT("Damage: %.1f -> %s"), AppliedDamage, *HitCharacter->GetName()));
				}
				else if (!OwnerController)
				{ 
					UE_LOG(LogWeaponHitNotify, Warning, TEXT("  Cannot apply damage: OwnerController is NULL."));
				}
				else // DamageToApply <= 0.f
				{
					UE_LOG(LogWeaponHitNotify, Log, TEXT("  Skipping damage application as calculated damage (%.1f) is zero or less."), DamageToApply);
				}
			}

			// --- 检查生命值并处理死亡 (仅在造成伤害后) ---
			// 注意：如果 TakeDamage 没有正确更新生命值，这里的检查会无效
			if (AppliedDamage > 0.f) 
			{
				UAbilitySystemComponent* HitASC = HitCharacter->FindComponentByClass<UAbilitySystemComponent>(); 
				if (HitASC)
				{
					// 假设敌人和玩家都使用某种 AttributeSet 来获取 Health
					// 尝试获取通用的 Health 属性，而不是特定于 EnemyAttributeSet
					// 这需要你的 AttributeSet 基类或接口定义 Health
					// 如果没有通用接口，需要分别处理 Enemy 和 Player
					// 这里我们仍然假设 Enemy 使用 EnemyAttributeSet
					const UEnemyAttributeSet* HitEnemyAttributeSet = HitASC->GetSet<UEnemyAttributeSet>(); 
					if (HitEnemyAttributeSet)
					{
						float CurrentHealth = HitEnemyAttributeSet->GetHealth();
						UE_LOG(LogWeaponHitNotify, Verbose, TEXT("  %s health after damage: %.1f"), *HitCharacter->GetName(), CurrentHealth);

						if (CurrentHealth <= 0.0f)
						{
							UE_LOG(LogWeaponHitNotify, Log, TEXT("  %s health is <= 0. Destroying actor."), *HitCharacter->GetName());
							if (bDebugTrace && GEngine) GEngine->AddOnScreenDebugMessage(-1, DebugDisplayTime, FColor::Red, FString::Printf(TEXT("%s Died!"), *HitCharacter->GetName()));
							
							// TODO: 触发死亡动画/效果，然后延迟销毁
							// 例如：HitCharacter->PlayAnimMontage(DeathMontage);
							// FTimerHandle DestroyTimer;
							// GetWorld()->GetTimerManager().SetTimer(DestroyTimer, [HitCharacter]() { if(HitCharacter) HitCharacter->Destroy(); }, DeathAnimationDuration, false);
							
							// 临时：立即销毁
							HitCharacter->Destroy(); 
						}
					}
					// else { // 可以添加对玩家 AttributeSet 的检查 }
				}
				 else
				{
					 UE_LOG(LogWeaponHitNotify, Warning, TEXT("  Cannot check health: Hit character '%s' does not have AbilitySystemComponent."), *HitCharacter->GetName());
				}
			}
		}
	}
}

void UWeaponHitNotify::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	// 清理状态
	HitActors.Empty();
	CachedWeaponMeshComp = nullptr;
	UE_LOG(LogWeaponHitNotify, Verbose, TEXT("WeaponHitNotify::NotifyEnd - Cleared HitActors and Cache"));
}
