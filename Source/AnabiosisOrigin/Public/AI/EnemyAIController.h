/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: EnemyAIController.h
* 功能描述： 定义敌人 AI 的控制器。负责管理行为树和黑板。
*/

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI/AiBehaviorComponent.h" // <--- 保持包含完整的头文件
#include "EnemyAIController.generated.h"

class UBehaviorTree;
class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS()
class ANABIOSISORIGIN_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

protected:
	//~ Begin AAIController Interface
	/** 当控制器控制一个 Pawn 时调用 */
	virtual void OnPossess(APawn* InPawn) override;
	//~ End AAIController Interface

	/** 行为树组件 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Components")
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	/** 黑板组件 (由 AAIController 基类提供，但我们保留一个指针以便访问) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Components")
	TObjectPtr<UBlackboardComponent> BlackboardComponent;

	/** 要运行的行为树资源 */
	UPROPERTY(EditDefaultsOnly, Category = "AI Config")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;

private:
	/** 缓存的 AI 行为组件指针 */
	UPROPERTY(Transient) // 不需要保存
	TObjectPtr<UAiBehaviorComponent> AiBehaviorComp;
};
