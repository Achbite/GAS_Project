#include "Animation/WeaponHitNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequenceBase.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"
// 添加必要的伤害系统头文件
#include "GameFramework/DamageType.h"
#include "GameFramework/Controller.h"
#include "Engine/DamageEvents.h"

UWeaponHitNotify::UWeaponHitNotify()
{
    // 默认设置
    WeaponStartSocketName = FName("weapon_start");
    WeaponEndSocketName = FName("weapon_end");
    TraceRadius = 2.0f;
    bDebugTrace = true;
    DebugDisplayTime = 2.0f;
    bApplyDamage = false;
    BaseDamage = 10.0f;
}

void UWeaponHitNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp || !MeshComp->GetOwner())
    {
        return;
    }
    
    // 获取起点位置
    FVector TraceStart = MeshComp->GetSocketLocation(WeaponStartSocketName);
    
    // 获取终点位置
    FVector TraceEnd = MeshComp->GetSocketLocation(WeaponEndSocketName);
    
    // 检查骨骼/插槽是否存在
    if (TraceStart.IsZero() || TraceEnd.IsZero())
    {
        // 如果找不到起点或终点骨骼，打印警告
        if (GEngine && bDebugTrace)
        {
            FString ErrorMsg = FString::Printf(TEXT("骨骼/插槽未找到: %s 或 %s"), 
                *WeaponStartSocketName.ToString(), *WeaponEndSocketName.ToString());
            GEngine->AddOnScreenDebugMessage(-1, DebugDisplayTime, FColor::Red, ErrorMsg);
        }
        return;
    }
    
    // 设置碰撞查询参数
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(MeshComp->GetOwner());  // 忽略自己
    QueryParams.bTraceComplex = true;  // 使用复杂碰撞
    
    TArray<FHitResult> HitResults;
    bool bHit = false;
    
    // 忽略的Actor数组
    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(MeshComp->GetOwner());
    
    // 进行射线检测
    if (TraceRadius > 0.0f)
    {
        // 球形扫描检测 (更适合武器攻击检测)
        bHit = UKismetSystemLibrary::SphereTraceMulti(
            MeshComp->GetWorld(),
            TraceStart,
            TraceEnd,
            TraceRadius,
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
    else
    {
        // 线形检测
        bHit = UKismetSystemLibrary::LineTraceMulti(
            MeshComp->GetWorld(),
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
    
    // 已命中的Actor列表 (避免多次伤害计算)
    TArray<AActor*> HitActors;
    
    // 处理命中结果
    if (bHit)
    {
        for (const FHitResult& Hit : HitResults)
        {
            if (!Hit.GetActor() || HitActors.Contains(Hit.GetActor()))
            {
                continue;
            }
            
            // 添加到已命中列表
            HitActors.Add(Hit.GetActor());
            
            // 在屏幕上显示命中的Actor信息
            if (GEngine && bDebugTrace)
            {
                FString HitMessage = FString::Printf(
                    TEXT("武器命中: %s (骨骼: %s)"),
                    *Hit.GetActor()->GetName(),
                    *Hit.BoneName.ToString()
                );
                GEngine->AddOnScreenDebugMessage(-1, DebugDisplayTime, FColor::Green, HitMessage);
            }
            
            // 应用伤害
            if (bApplyDamage)
            {
                ACharacter* OwnerCharacter = Cast<ACharacter>(MeshComp->GetOwner());
                if (OwnerCharacter && OwnerCharacter->GetController())
                {
                    FVector Direction = (TraceEnd - TraceStart).GetSafeNormal();
                    
                    // 创建点伤害事件
                    FDamageEvent DamageEvent;
                    Hit.GetActor()->TakeDamage(BaseDamage, DamageEvent, OwnerCharacter->GetController(), MeshComp->GetOwner());
                    
                    if (GEngine && bDebugTrace)
                    {
                        GEngine->AddOnScreenDebugMessage(-1, DebugDisplayTime, FColor::Orange, 
                            FString::Printf(TEXT("对 %s 造成 %.1f 伤害"), *Hit.GetActor()->GetName(), BaseDamage));
                    }
                }
            }
        }
    }
    else if (GEngine && bDebugTrace)
    {
        // 未命中任何目标
        GEngine->AddOnScreenDebugMessage(-1, DebugDisplayTime, FColor::Yellow, TEXT("武器未命中任何目标"));
    }
}
