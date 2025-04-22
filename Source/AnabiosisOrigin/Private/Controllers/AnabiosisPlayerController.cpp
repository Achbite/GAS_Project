/* 
 * Copyright (C) 2024 [Wang] 
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 3 of the License, or 
 * (at your option) any later version. 
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
* 功能描述： 实现玩家控制器，处理输入绑定、角色移动、视角控制和战斗模式切换。
*/

#include "Controllers/AnabiosisPlayerController.h"
#include "Characters/AnabiosisOriginCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h" 

AAnabiosisPlayerController::AAnabiosisPlayerController()
{
	// 初始化默认值
	NormalCameraArmLength = 400.0f;
	CombatCameraArmLength = 300.0f;
	CombatCameraOffset = FVector(0.f, 50.f, 20.f);
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	bIsInCombatMode = false;
}

void AAnabiosisPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 获取并缓存控制的角色
	ControlledCharacter = Cast<AAnabiosisOriginCharacter>(GetPawn());
	if (!ControlledCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("AnabiosisPlayerController failed to get AnabiosisOriginCharacter on BeginPlay."));
	}

	// 添加输入映射上下文
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("DefaultMappingContext is not set in AnabiosisPlayerController."));
		}
	}
}

void AAnabiosisPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) // 使用 Cast 而非 CastChecked
	{
		// --- 绑定输入 Action ---
		if (MoveAction)
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAnabiosisPlayerController::Move);
		else UE_LOG(LogTemp, Error, TEXT("MoveAction is not set in AnabiosisPlayerController."));

		if (LookAction)
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAnabiosisPlayerController::Look);
		else UE_LOG(LogTemp, Error, TEXT("LookAction is not set in AnabiosisPlayerController."));
		
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AAnabiosisPlayerController::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AAnabiosisPlayerController::StopJumping);
		} else UE_LOG(LogTemp, Error, TEXT("JumpAction is not set in AnabiosisPlayerController."));
		
		// 攻击输入绑定 (如果需要，取消注释并确保 AttackAction 已设置)
		if (AttackAction)
			EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AAnabiosisPlayerController::OnAttackActionStarted);
		else UE_LOG(LogTemp, Warning, TEXT("AttackAction is not set in AnabiosisPlayerController. Attack input will not work."));
		
		if (AttackLookAction)
			EnhancedInputComponent->BindAction(AttackLookAction, ETriggerEvent::Started, this, &AAnabiosisPlayerController::ToggleAttackLook);
		else UE_LOG(LogTemp, Error, TEXT("AttackLookAction is not set in AnabiosisPlayerController."));
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Failed to cast InputComponent to UEnhancedInputComponent in AnabiosisPlayerController. Enhanced Input may not be enabled or set up correctly."));
	}
}

void AAnabiosisPlayerController::Move(const FInputActionValue& Value)
{
	if (!ControlledCharacter) return;

	FVector2D MovementVector = Value.Get<FVector2D>();
	if (MovementVector.IsZero()) return; // 避免零移动

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	ControlledCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
	ControlledCharacter->AddMovementInput(RightDirection, MovementVector.X);
}

void AAnabiosisPlayerController::Look(const FInputActionValue& Value)
{
	if (!ControlledCharacter) return;

	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (LookAxisVector.IsZero()) return; // 避免零输入

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

void AAnabiosisPlayerController::OnAttackActionStarted(const FInputActionValue& Value)
{
	if (!ControlledCharacter) return;

	UAbilitySystemComponent* AbilitySystem = ControlledCharacter->GetAbilitySystemComponent();
	if (!AbilitySystem)
	{
		UE_LOG(LogTemp, Error, TEXT("OnAttackActionStarted: AbilitySystemComponent is null on Character."));
		return;
	}

	FGameplayTag AttackTag = ControlledCharacter->GetAttackAbilityTag();
	if (!AttackTag.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("OnAttackActionStarted: AttackAbilityTag is invalid on Character. Cannot activate attack ability by tag."));
		return;
	}

	// 尝试通过标签激活能力
	FGameplayTagContainer AbilityTags;
	AbilityTags.AddTag(AttackTag);
	
	bool bSuccess = AbilitySystem->TryActivateAbilitiesByTag(AbilityTags);
	if (!bSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to activate ability with tag: %s. Is the ability granted and activatable?"), *AttackTag.ToString());
	}
}

void AAnabiosisPlayerController::ToggleAttackLook(const FInputActionValue& Value)
{
	if (!ControlledCharacter) return;

	// 切换战斗模式状态
	bIsInCombatMode = !bIsInCombatMode;
	UE_LOG(LogTemp, Log, TEXT("Toggled Combat Mode: %s"), bIsInCombatMode ? TEXT("ON") : TEXT("OFF"));

	// 更新角色移动和相机状态
	UpdateCharacterMovementState(bIsInCombatMode);
}

// --- Helper Functions (合并重复逻辑) ---

void AAnabiosisPlayerController::SetCameraParameters(float ArmLength, const FVector& Offset)
{
	if (!ControlledCharacter) return;

	if (USpringArmComponent* CameraBoom = ControlledCharacter->GetCameraBoom())
	{
		CameraBoom->TargetArmLength = ArmLength;
		CameraBoom->SocketOffset = Offset;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SetCameraParameters: CameraBoom is null on Character."));
	}
}

void AAnabiosisPlayerController::UpdateCharacterMovementState(bool bIsCombatMode)
{
	if (!ControlledCharacter) return;

	// 更新角色旋转设置
	ControlledCharacter->SetCharacterRotationMode(!bIsCombatMode, bIsCombatMode);

	// 更新相机设置
	float NewArmLength = bIsCombatMode ? CombatCameraArmLength : NormalCameraArmLength;
	FVector NewOffset = bIsCombatMode ? CombatCameraOffset : FVector::ZeroVector;
	SetCameraParameters(NewArmLength, NewOffset);
}
