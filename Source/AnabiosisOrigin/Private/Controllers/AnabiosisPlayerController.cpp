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
*            处理输入绑定、角色移动、视角控制、跳跃、攻击以及战斗模式切换。
* 结构：
* - 构造函数：初始化相机参数和默认状态。
* - BeginPlay：获取控制的角色并添加输入映射上下文。
* - SetupInputComponent：绑定输入 Action 到处理函数。
* - Move, Look, Jump, StopJumping, OnAttackActionStarted, ToggleAttackLook：输入处理函数。
* - UpdateCharacterMovementState, SetCameraParameters：辅助函数，用于更新角色和相机状态。
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
#include "Kismet/GameplayStatics.h" // For GetAllActorsOfClass
#include "Kismet/KismetMathLibrary.h" // For LookAtRotation, Angle calculations
#include "Engine/World.h" // For LineTrace
#include "DrawDebugHelpers.h" // For debug drawing

AAnabiosisPlayerController::AAnabiosisPlayerController()
{
	// 初始化相机臂长度和偏移量
	NormalCameraArmLength = 400.0f;
	CombatCameraArmLength = 300.0f;
	CombatCameraOffset = FVector(0.f, 50.f, 20.f);

	// 初始化视角转动速率
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// 初始化战斗模式状态
	bIsInCombatMode = false;
	// 初始化锁定状态
	LockedTarget = nullptr;
	bIsTargetLocked = false;
	MaxLockDistance = 2000.0f;
	LockConeAngleDegrees = 30.0f;
	LockInterpolationSpeed = 10.0f;
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
		// 绑定移动 Action
		if (MoveAction)
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAnabiosisPlayerController::Move);
		else UE_LOG(LogTemp, Error, TEXT("玩家控制器：未设置 MoveAction。"));

		// 绑定视角 Action
		if (LookAction)
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAnabiosisPlayerController::Look);
		else UE_LOG(LogTemp, Error, TEXT("玩家控制器：未设置 LookAction。"));

		// 绑定跳跃 Action
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AAnabiosisPlayerController::Jump); // 跳跃开始
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AAnabiosisPlayerController::StopJumping); // 跳跃结束
		} else UE_LOG(LogTemp, Error, TEXT("玩家控制器：未设置 JumpAction。"));

		// 绑定切换攻击/锁定视角 Action
		if (AttackLookAction)
			EnhancedInputComponent->BindAction(AttackLookAction, ETriggerEvent::Started, this, &AAnabiosisPlayerController::ToggleAttackLook);
		else UE_LOG(LogTemp, Error, TEXT("玩家控制器：未设置 AttackLookAction。"));
	}
	else
	{
		// 如果转换失败，记录致命错误
		UE_LOG(LogTemp, Fatal, TEXT("玩家控制器：无法将 InputComponent 转换为 UEnhancedInputComponent。增强输入可能未启用或设置不正确。"));
	}
}

void AAnabiosisPlayerController::Move(const FInputActionValue& Value)
{
	// 检查角色是否有效
	if (!ControlledCharacter) return;

	// 获取二维移动向量
	FVector2D MovementVector = Value.Get<FVector2D>();
	// 如果移动向量为零，则不执行操作
	if (MovementVector.IsZero()) return;

	// 获取控制器旋转，并只取 Yaw 方向
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// 计算前方向和右方向
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// 向角色添加移动输入
	ControlledCharacter->AddMovementInput(ForwardDirection, MovementVector.Y); // 前后移动
	ControlledCharacter->AddMovementInput(RightDirection, MovementVector.X);   // 左右移动
}

void AAnabiosisPlayerController::Look(const FInputActionValue& Value)
{
	// 如果已锁定目标，则由 PlayerTick 处理旋转，忽略或修改此处的输入
	if (bIsTargetLocked)
	{
		// 可选：允许轻微的输入来调整围绕目标的视角，但这会更复杂
		// FVector2D LookAxisVector = Value.Get<FVector2D>();
		// AddYawInput(LookAxisVector.X * 0.1f); // Example: Reduced input
		// AddPitchInput(LookAxisVector.Y * 0.1f);
		return; // 主要旋转由 Tick 处理
	}

	// 检查角色是否有效
	if (!ControlledCharacter) return;

	// 获取二维视角向量
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	// 如果视角向量为零，则不执行操作
	if (LookAxisVector.IsZero()) return;

	// 添加 Yaw 和 Pitch 输入
	AddYawInput(LookAxisVector.X);   // 左右视角转动
	AddPitchInput(LookAxisVector.Y); // 上下视角转动
}

void AAnabiosisPlayerController::Jump()
{
	// 如果角色有效，则调用其跳跃函数
	if (ControlledCharacter)
	{
		ControlledCharacter->Jump();
	}
}

void AAnabiosisPlayerController::StopJumping()
{
	// 如果角色有效，则调用其停止跳跃函数
	if (ControlledCharacter)
	{
		ControlledCharacter->StopJumping();
	}
}

void AAnabiosisPlayerController::ToggleAttackLook(const FInputActionValue& Value)
{
	// 检查角色是否有效
	if (!ControlledCharacter) return;

	// 切换战斗模式状态
	bIsInCombatMode = !bIsInCombatMode;
	UE_LOG(LogTemp, Log, TEXT("切换战斗模式：%s"), bIsInCombatMode ? TEXT("开启") : TEXT("关闭"));

	// 更新角色移动和相机状态
	UpdateCharacterMovementState(bIsInCombatMode);

	// 根据战斗模式处理锁定逻辑
	if (bIsInCombatMode)
	{
		TryLockTarget(); // 进入战斗模式时尝试锁定
	}
	else
	{
		UnlockTarget(); // 退出战斗模式时解除锁定
	}
}

void AAnabiosisPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bIsTargetLocked && LockedTarget)
	{
		// 检查目标有效性
		if (LockedTarget->IsDead() || !LockedTarget->GetMesh() || !LockedTarget->GetMesh()->IsVisible())
		{
			UE_LOG(LogTemp, Log, TEXT("锁定目标 %s 失效 (死亡或不可见)，解除锁定。"), *LockedTarget->GetName());
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

		// 检查视线 (可选，如果性能允许可以频繁检查)
		// FHitResult HitResult;
		// FVector Start = ControlledCharacter->GetActorLocation();
		// FVector End = LockedTarget->GetActorLocation();
		// FCollisionQueryParams QueryParams;
		// QueryParams.AddIgnoredActor(ControlledCharacter); // 忽略玩家自身
		// QueryParams.AddIgnoredActor(LockedTarget); // 忽略目标自身 (可选)

		// bool bHit = GetWorld()->LineTraceSingleByChannel(
		// 	HitResult,
		// 	Start,
		// 	End,
		// 	ECC_Visibility, // 使用可见性通道
		// 	QueryParams
		// );

		// if (bHit)
		// {
		// 	// UE_LOG(LogTemp, Log, TEXT("锁定目标 %s 视线被 %s 阻挡，解除锁定。"), *LockedTarget->GetName(), *HitResult.GetActor()->GetName());
		// 	// UnlockTarget(); // 暂时不因短暂遮挡解除锁定，除非设计需要
		// 	// return;
		// }

		// 计算目标旋转
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(
			ControlledCharacter->GetActorLocation(),
			LockedTarget->GetActorLocation() // 可以瞄准目标的特定骨骼或组件位置
		);

		// 平滑插值到目标旋转
		FRotator CurrentRotation = GetControlRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, LockInterpolationSpeed);

		// 只应用 Yaw 和 Pitch，Roll 保持不变
		SetControlRotation(FRotator(NewRotation.Pitch, NewRotation.Yaw, CurrentRotation.Roll));
	}
	else if (bIsTargetLocked && !LockedTarget)
	{
		// 如果标记为锁定但目标为空，则解除锁定
		UnlockTarget();
	}
}

// --- 辅助函数 ---

void AAnabiosisPlayerController::SetCameraParameters(float ArmLength, const FVector& Offset)
{
	// 检查角色是否有效
	if (!ControlledCharacter) return;

	// 获取角色的相机弹簧臂组件
	if (USpringArmComponent* CameraBoom = ControlledCharacter->GetCameraBoom())
	{
		// 设置弹簧臂长度和插槽偏移
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
	// 检查角色是否有效
	if (!ControlledCharacter) return;

	// 更新角色旋转设置
	// 非战斗模式：朝向移动方向；战斗模式：使用控制器 Yaw 旋转
	ControlledCharacter->SetCharacterRotationMode(!bIsCombatMode, bIsCombatMode);

	// 更新相机设置
	float NewArmLength = bIsCombatMode ? CombatCameraArmLength : NormalCameraArmLength;
	FVector NewOffset = bIsCombatMode ? CombatCameraOffset : FVector::ZeroVector;
	SetCameraParameters(NewArmLength, NewOffset);
}

// --- 新增锁定函数 ---

void AAnabiosisPlayerController::TryLockTarget()
{
	if (!ControlledCharacter) return;

	UnlockTarget(); // 先清除旧目标

	float MinAngleRad = FMath::DegreesToRadians(LockConeAngleDegrees);
	float BestScore = -1.0f; // 使用评分系统选择最佳目标
	AEnemyBaseCharacter* PotentialTarget = nullptr;

	FVector PlayerLocation = ControlledCharacter->GetActorLocation();
	FVector PlayerForward = GetControlRotation().Vector(); // 使用控制器旋转作为前向

	// 获取世界中的所有敌人
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBaseCharacter::StaticClass(), FoundEnemies);

	for (AActor* Actor : FoundEnemies)
	{
		AEnemyBaseCharacter* Enemy = Cast<AEnemyBaseCharacter>(Actor);
		if (!Enemy || Enemy->IsDead() || !Enemy->GetMesh() || !Enemy->GetMesh()->IsVisible()) // 检查有效性、死亡状态和可见性
		{
			continue;
		}

		FVector EnemyLocation = Enemy->GetActorLocation();
		FVector DirectionToEnemy = (EnemyLocation - PlayerLocation);
		float DistanceSq = DirectionToEnemy.SizeSquared();

		// 1. 检查距离
		if (DistanceSq > FMath::Square(MaxLockDistance))
		{
			continue; // 太远
		}

		DirectionToEnemy.Normalize();

		// 2. 检查角度
		float AngleRad = FMath::Acos(FVector::DotProduct(PlayerForward, DirectionToEnemy));
		if (AngleRad > MinAngleRad)
		{
			continue; // 在锁定锥形外
		}

		// 3. 检查视线
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(ControlledCharacter); // 忽略玩家
		QueryParams.AddIgnoredActor(Enemy); // 忽略敌人自身

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			PlayerLocation,
			EnemyLocation,
			ECC_Visibility, // 可见性通道
			QueryParams
		);

		// if (bHit)
		// {
		// 	continue; // 视线被阻挡
		// }

		// 计算评分 (距离越近、角度越小，得分越高)
		// 简单的评分：角度越小越好 (1 - 角度/最大角度)，距离越近越好 (1 - 距离/最大距离)
		float AngleScore = 1.0f - (AngleRad / MinAngleRad);
		float DistanceScore = 1.0f - (FMath::Sqrt(DistanceSq) / MaxLockDistance);
		float CurrentScore = AngleScore * 0.6f + DistanceScore * 0.4f; // 角度权重更高

		if (CurrentScore > BestScore)
		{
			BestScore = CurrentScore;
			PotentialTarget = Enemy;
		}
	}

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
	// 可选：重置相机设置或旋转模式，如果锁定改变了它们
}

