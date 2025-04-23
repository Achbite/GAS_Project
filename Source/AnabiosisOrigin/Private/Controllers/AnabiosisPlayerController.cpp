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
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h" // 包含基础角色类
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h" // 包含能力系统组件
#include "InputMappingContext.h" // 包含输入映射上下文
#include "InputAction.h" // 包含输入 Action

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

		// 绑定攻击 Action
		if (AttackAction)
			EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AAnabiosisPlayerController::OnAttackActionStarted);
		else UE_LOG(LogTemp, Warning, TEXT("玩家控制器：未设置 AttackAction。攻击输入将无效。"));

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

void AAnabiosisPlayerController::OnAttackActionStarted(const FInputActionValue& Value)
{
	// 检查角色是否有效
	if (!ControlledCharacter) return;

	// 获取角色的能力系统组件
	UAbilitySystemComponent* AbilitySystem = ControlledCharacter->GetAbilitySystemComponent();
	if (!AbilitySystem)
	{
		UE_LOG(LogTemp, Error, TEXT("攻击输入：角色上的 AbilitySystemComponent 为空。"));
		return;
	}

	// 获取角色当前设置的攻击能力标签
	FGameplayTag AttackTag = ControlledCharacter->GetAttackAbilityTag();
	if (!AttackTag.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("攻击输入：角色上的 AttackAbilityTag 无效。无法通过标签激活攻击能力。"));
		return;
	}

	// 尝试通过标签激活能力
	FGameplayTagContainer AbilityTags;
	AbilityTags.AddTag(AttackTag);

	bool bSuccess = AbilitySystem->TryActivateAbilitiesByTag(AbilityTags);
	if (!bSuccess)
	{
		// 如果激活失败，记录警告
		UE_LOG(LogTemp, Warning, TEXT("无法激活标签为 %s 的能力。能力是否已授予且可激活？"), *AttackTag.ToString());
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

