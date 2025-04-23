/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: AnabiosisPlayerController.h
* 功能描述： 定义玩家控制器 AAnabiosisPlayerController。
*            负责处理玩家输入、控制角色行为（移动、视角、攻击、跳跃）以及相机模式切换。
* 结构：
* - 继承自 APlayerController。
* - 使用增强输入系统 (Enhanced Input System)。
* - 包含输入 Action 和输入映射上下文的引用。
* - 定义处理各种输入的函数。
* - 管理普通模式和战斗模式下的相机参数。
* - 提供切换战斗模式和更新角色状态的功能。
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h" // 包含 InputActionValue
#include "GameplayTagContainer.h" // 包含 GameplayTagContainer
#include "AnabiosisPlayerController.generated.h"

// 前向声明
class UInputMappingContext;
class UInputAction;
class AAnabiosisOriginCharacter; // 明确包含角色类
class USpringArmComponent; // 包含弹簧臂组件

/**
 * @brief 玩家控制器类，处理输入和控制玩家角色。
 */
UCLASS()
class ANABIOSISORIGIN_API AAnabiosisPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** 构造函数 */
	AAnabiosisPlayerController();

	/** 弹簧臂在普通模式下的长度 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	float NormalCameraArmLength;

	/** 弹簧臂在战斗模式下的长度 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	float CombatCameraArmLength;

	/** 战斗模式下相机的偏移量 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	FVector CombatCameraOffset;

	/** 基础转向速率 (度/秒) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** 基础仰视速率 (度/秒) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

protected:
	/** 默认输入映射上下文 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** 跳跃输入 Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	/** 移动输入 Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	/** 视角输入 Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	/** 攻击输入 Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> AttackAction;

	/** 切换攻击/锁定视角输入 Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> AttackLookAction;

	/** 游戏开始时调用 */
	virtual void BeginPlay() override;

	/** 设置输入组件 */
	virtual void SetupInputComponent() override;

	/** 处理移动输入 */
	void Move(const FInputActionValue& Value);

	/** 处理视角输入 */
	void Look(const FInputActionValue& Value);

	/** 处理跳跃开始 */
	void Jump();

	/** 处理跳跃结束 */
	void StopJumping();

	/** 处理攻击输入开始 */
	void OnAttackActionStarted(const FInputActionValue& Value);

	/** 处理切换攻击/锁定视角输入 */
	void ToggleAttackLook(const FInputActionValue& Value);

	/**
	 * @brief 更新角色的移动和旋转状态。
	 * @param bIsCombatMode 是否进入战斗模式。
	 */
	void UpdateCharacterMovementState(bool bIsCombatMode);

	/**
	 * @brief 设置相机参数。
	 * @param ArmLength 弹簧臂长度。
	 * @param Offset 相机偏移量。
	 */
	void SetCameraParameters(float ArmLength, const FVector& Offset);

private:
	/** 缓存控制的角色指针 */
	UPROPERTY(Transient) // Transient 表示不需要保存
	TObjectPtr<AAnabiosisOriginCharacter> ControlledCharacter;

	/** 当前是否处于战斗模式 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	bool bIsInCombatMode;
};
