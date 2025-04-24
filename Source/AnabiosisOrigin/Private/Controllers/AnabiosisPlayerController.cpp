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
* 文件名: AnabiosisPlayerController.cpp
* 功能描述： 实现玩家控制器 AAnabiosisPlayerController 的逻辑。
*            处理输入绑定、角色移动、视角控制、跳跃、攻击触发（通过切换模式间接触发）以及目标锁定。
* 结构：
* - 构造函数：初始化相机参数、锁定参数和默认状态。
* - BeginPlay：获取控制的角色并添加输入映射上下文。
* - SetupInputComponent：绑定输入 Action 到处理函数。
* - Move, Look, Jump, StopJumping, ToggleAttackLook：输入处理函数。
* - PlayerTick：处理目标锁定时的视角平滑插值和状态检查。
* - UpdateCharacterMovementState, SetCameraParameters：辅助函数，用于更新角色旋转和相机状态。
* - TryLockTarget, UnlockTarget：处理目标锁定和解锁的逻辑。
*/

#include "Controllers/AnabiosisPlayerController.h"
#include "Characters/AnabiosisOriginCharacter.h" // 包含玩家角色头文件
#include "Characters/EnemyBaseCharacter.h" // 包含敌人角色头文件
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h" // 包含基础角色类
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h" // 包含能力系统组件
#include "InputMappingContext.h" // 包含输入映射上下文
#include "InputAction.h" // 包含输入 Action
#include "Kismet/GameplayStatics.h" // 用于 GetAllActorsOfClass
#include "Kismet/KismetMathLibrary.h" // 用于 FindLookAtRotation, 角度计算
#include "Engine/World.h" // 用于 LineTrace
// #include "DrawDebugHelpers.h" // 如果不再需要调试绘制，可以移除

AAnabiosisPlayerController::AAnabiosisPlayerController()
{
	// 初始化相机臂长度和偏移量
	NormalCameraArmLength = 400.0f;
	CombatCameraArmLength = 300.0f;
	CombatCameraOffset = FVector(0.f, 50.f, 20.f);

	// 初始化视角转动速率 (注意：增强输入通常不直接使用速率，而是直接处理输入值)
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// 初始化战斗模式和锁定状态
	bIsInCombatMode = false;
	LockedTarget = nullptr;
	bIsTargetLocked = false;
	MaxLockDistance = 2000.0f; // 最大锁定距离
	LockConeAngleDegrees = 30.0f; // 锁定锥形半角
	LockInterpolationSpeed = 10.0f; // 视角插值速度
}

void AAnabiosisPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 获取并缓存控制的角色
	ControlledCharacter = Cast<AAnabiosisOriginCharacter>(GetPawn());
	if (!ControlledCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("玩家控制器：BeginPlay 时未能获取到玩家角色 AnabiosisOriginCharacter。"));
	}

	// 添加输入映射上下文
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			// 添加默认的输入映射上下文，优先级为 0
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("玩家控制器：未设置 DefaultMappingContext。"));
		}
	}
}

void AAnabiosisPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 尝试将输入组件转换为增强输入组件
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// --- 绑定输入 Action ---
		if (MoveAction)
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAnabiosisPlayerController::Move);
		else UE_LOG(LogTemp, Error, TEXT("玩家控制器：未设置 MoveAction。"));

		if (LookAction)
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAnabiosisPlayerController::Look);
		else UE_LOG(LogTemp, Error, TEXT("玩家控制器：未设置 LookAction。"));

		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AAnabiosisPlayerController::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AAnabiosisPlayerController::StopJumping);
		} else UE_LOG(LogTemp, Error, TEXT("玩家控制器：未设置 JumpAction。"));

		// 绑定切换战斗/锁定模式的 Action
		if (AttackLookAction)
			EnhancedInputComponent->BindAction(AttackLookAction, ETriggerEvent::Started, this, &AAnabiosisPlayerController::ToggleAttackLook);
		else UE_LOG(LogTemp, Error, TEXT("玩家控制器：未设置 AttackLookAction。"));

		// 注意：攻击输入通常通过 GAS 的 Input Binding 处理，而不是直接在 Controller 中绑定
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("玩家控制器：无法将 InputComponent 转换为 UEnhancedInputComponent。增强输入可能未启用或设置不正确。"));
	}
}

void AAnabiosisPlayerController::Move(const FInputActionValue& Value)
{
	if (!ControlledCharacter) return;

	FVector2D MovementVector = Value.Get<FVector2D>();
	if (MovementVector.IsZero()) return;

	// 根据控制器旋转计算移动方向
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// 添加移动输入
	ControlledCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
	ControlledCharacter->AddMovementInput(RightDirection, MovementVector.X);
}

void AAnabiosisPlayerController::Look(const FInputActionValue& Value)
{
	// 如果已锁定目标，则由 PlayerTick 处理主要旋转，忽略此处的输入
	if (bIsTargetLocked)
	{
		// 可以选择允许微小的输入来调整视角，但这会增加复杂性
		return;
	}

	if (!ControlledCharacter) return;

	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (LookAxisVector.IsZero()) return;

	// 添加 Yaw 和 Pitch 输入以控制视角
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AAnabiosisPlayerController::Jump()
{
	if (ControlledCharacter)
	{
		ControlledCharacter->Jump();
	}
}

void AAnabiosisPlayerController::StopJumping()
{
	if (ControlledCharacter)
	{
		ControlledCharacter->StopJumping();
	}
}

void AAnabiosisPlayerController::ToggleAttackLook(const FInputActionValue& Value)
{
	if (!ControlledCharacter) return;

	// 切换战斗模式状态
	bIsInCombatMode = !bIsInCombatMode;
	UE_LOG(LogTemp, Log, TEXT("切换战斗模式：%s"), bIsInCombatMode ? TEXT("开启") : TEXT("关闭"));

	// 更新角色旋转和相机设置
	UpdateCharacterMovementState(bIsInCombatMode);

	// 根据战斗模式处理锁定逻辑
	if (bIsInCombatMode)
	{
		TryLockTarget(); // 进入战斗模式时尝试锁定目标
	}
	else
	{
		UnlockTarget(); // 退出战斗模式时解除锁定
	}
}

void AAnabiosisPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// 处理目标锁定状态下的视角更新
	if (bIsTargetLocked && LockedTarget)
	{
		// 检查目标有效性 (死亡、不可见等)
		if (LockedTarget->IsDead() || !LockedTarget->GetMesh() || !LockedTarget->GetMesh()->IsVisible())
		{
			UE_LOG(LogTemp, Log, TEXT("锁定目标 %s 失效，解除锁定。"), *LockedTarget->GetName());
			UnlockTarget();
			return;
		}

		// 检查距离
		float DistanceSq = FVector::DistSquared(ControlledCharacter->GetActorLocation(), LockedTarget->GetActorLocation());
		if (DistanceSq > FMath::Square(MaxLockDistance))
		{
			UE_LOG(LogTemp, Log, TEXT("锁定目标 %s 超出最大距离，解除锁定。"), *LockedTarget->GetName());
			UnlockTarget();
			return;
		}

		// 可选：检查视线，如果需要更严格的锁定条件
		// FHitResult HitResult;
		// bool bHit = GetWorld()->LineTraceSingleByChannel(...);
		// if (bHit) { UnlockTarget(); return; }

		// 计算朝向目标的旋转
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(
			ControlledCharacter->GetActorLocation(),
			LockedTarget->GetActorLocation() // 可以优化为瞄准目标的特定部位
		);

		// 平滑插值当前视角到目标视角
		FRotator CurrentRotation = GetControlRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, LockInterpolationSpeed);

		// 应用新的 Yaw 和 Pitch，保持 Roll 不变
		SetControlRotation(FRotator(NewRotation.Pitch, NewRotation.Yaw, CurrentRotation.Roll));
	}
	else if (bIsTargetLocked && !LockedTarget)
	{
		// 状态不一致，解除锁定
		UnlockTarget();
	}
}

// --- 辅助函数 ---

void AAnabiosisPlayerController::SetCameraParameters(float ArmLength, const FVector& Offset)
{
	if (!ControlledCharacter) return;

	if (USpringArmComponent* CameraBoom = ControlledCharacter->GetCameraBoom())
	{
		// 设置相机臂长度和插槽偏移
		CameraBoom->TargetArmLength = ArmLength;
		CameraBoom->SocketOffset = Offset;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("设置相机参数：角色上的 CameraBoom 为空。"));
	}
}

void AAnabiosisPlayerController::UpdateCharacterMovementState(bool bIsCombatMode)
{
	if (!ControlledCharacter) return;

	// 更新角色旋转设置
	// 非战斗模式：朝向移动方向；战斗模式：使用控制器 Yaw 旋转
	ControlledCharacter->SetCharacterRotationMode(!bIsCombatMode, bIsCombatMode);

	// 更新相机设置
	float NewArmLength = bIsCombatMode ? CombatCameraArmLength : NormalCameraArmLength;
	FVector NewOffset = bIsCombatMode ? CombatCameraOffset : FVector::ZeroVector;
	SetCameraParameters(NewArmLength, NewOffset);
}

// --- 目标锁定函数 ---

void AAnabiosisPlayerController::TryLockTarget()
{
	if (!ControlledCharacter) return;

	UnlockTarget(); // 尝试锁定时先清除旧目标

	float MinAngleRad = FMath::DegreesToRadians(LockConeAngleDegrees);
	float BestScore = -1.0f; // 用于选择最佳目标
	AEnemyBaseCharacter* PotentialTarget = nullptr;

	FVector PlayerLocation = ControlledCharacter->GetActorLocation();
	FVector PlayerForward = GetControlRotation().Vector(); // 使用控制器（相机）朝向

	// 获取世界中的所有敌人
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBaseCharacter::StaticClass(), FoundEnemies);

	for (AActor* Actor : FoundEnemies)
	{
		AEnemyBaseCharacter* Enemy = Cast<AEnemyBaseCharacter>(Actor);
		// 检查敌人有效性、死亡状态和可见性
		if (!Enemy || Enemy->IsDead() || !Enemy->GetMesh() || !Enemy->GetMesh()->IsVisible())
		{
			continue;
		}

		FVector EnemyLocation = Enemy->GetActorLocation();
		FVector DirectionToEnemy = (EnemyLocation - PlayerLocation);
		float DistanceSq = DirectionToEnemy.SizeSquared();

		// 1. 检查距离
		if (DistanceSq > FMath::Square(MaxLockDistance))
		{
			continue; // 目标太远
		}

		DirectionToEnemy.Normalize();

		// 2. 检查角度
		float AngleRad = FMath::Acos(FVector::DotProduct(PlayerForward, DirectionToEnemy));
		if (AngleRad > MinAngleRad)
		{
			continue; // 目标在锁定锥形之外
		}

		// 3. 检查视线 (可选，如果需要严格的视线要求)
		// FHitResult HitResult;
		// bool bHit = GetWorld()->LineTraceSingleByChannel(...);
		// if (bHit) { continue; } // 视线被阻挡

		// 计算评分 (距离越近、角度越小，得分越高)
		float AngleScore = 1.0f - (AngleRad / MinAngleRad); // 角度评分
		float DistanceScore = 1.0f - (FMath::Sqrt(DistanceSq) / MaxLockDistance); // 距离评分
		float CurrentScore = AngleScore * 0.6f + DistanceScore * 0.4f; // 综合评分，角度权重更高

		// 选择评分最高的目标
		if (CurrentScore > BestScore)
		{
			BestScore = CurrentScore;
			PotentialTarget = Enemy;
		}
	}

	// 如果找到合适的目标，则锁定
	if (PotentialTarget)
	{
		LockedTarget = PotentialTarget;
		bIsTargetLocked = true;
		UE_LOG(LogTemp, Log, TEXT("已锁定目标: %s"), *LockedTarget->GetName());
		// 可选：立即将视角转向目标
		// FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, LockedTarget->GetActorLocation());
		// SetControlRotation(TargetRotation);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("未找到可锁定的目标。"));
	}
}

void AAnabiosisPlayerController::UnlockTarget()
{
	if (bIsTargetLocked)
	{
		UE_LOG(LogTemp, Log, TEXT("解除目标锁定 (之前目标: %s)"), LockedTarget ? *LockedTarget->GetName() : TEXT("无"));
	}
	LockedTarget = nullptr;
	bIsTargetLocked = false;
	// 如果锁定改变了角色或相机的状态，可以在这里恢复
}

