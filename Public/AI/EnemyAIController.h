/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: EnemyAIController.h
* 功能描述： 定义敌人 AI 控制器 AEnemyAIController。
*            负责控制敌人的行为树和黑板。
* 结构：
* - 继承自 AAIController。
* - 包含行为树组件和黑板组件的引用。
* - 存储行为树资源。
* - 在 OnPossess 中初始化行为树和黑板。
*/

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

// 前向声明
class UBehaviorTree;
class UBehaviorTreeComponent;
class UBlackboardComponent;
class UAiBehaviorComponent; // 添加 AI 行为组件的前向声明

/**
 * @brief 敌人 AI 控制器，负责运行行为树。
 */
UCLASS()
class ANABIOSISORIGIN_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	/** 构造函数 */
	AEnemyAIController();

protected:
	/**
	 * @brief 当控制器控制一个 Pawn 时调用。
	 * @param InPawn 被控制的 Pawn。
	 */
	virtual void OnPossess(APawn* InPawn) override;

	/** 要运行的行为树资源 */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;

	/** 行为树组件，用于执行行为树逻辑 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	// AAIController 基类已经包含 BlackboardComponent，通常直接使用它
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	// TObjectPtr<UBlackboardComponent> BlackboardComponent;

	/** 缓存的 AI 行为组件指针 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAiBehaviorComponent> AiBehaviorComp;
};
