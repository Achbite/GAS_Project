/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: EnemyAIController.cpp
* 功能描述： 实现敌人 AI 控制器 AEnemyAIController 的具体逻辑。
*            负责在 Possess Pawn 时初始化并运行行为树和黑板。
*/

#include "AI/EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Characters/EnemyBaseCharacter.h"
#include "AI/AiBehaviorComponent.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BlackboardData.h"

AEnemyAIController::AEnemyAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	// AAIController 基类已提供 BlackboardComponent
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!InPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController OnPossess: InPawn is NULL!"));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("AIController OnPossess: Possessing Pawn: %s"), *InPawn->GetName());

	AEnemyBaseCharacter* EnemyCharacter = Cast<AEnemyBaseCharacter>(InPawn);
	if (!EnemyCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController OnPossess: Possessed Pawn '%s' is not an AEnemyBaseCharacter."), *InPawn->GetName());
		return;
	}

	// 获取 AI 行为组件 (可选，取决于是否需要直接交互)
	AiBehaviorComp = EnemyCharacter->FindComponentByClass<UAiBehaviorComponent>();
	if (!AiBehaviorComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController OnPossess: UAiBehaviorComponent not found on %s."), *EnemyCharacter->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AIController OnPossess: Found AiBehaviorComponent on %s."), *EnemyCharacter->GetName());
	}

	// 初始化并运行行为树
	if (BehaviorTreeAsset)
	{
		UE_LOG(LogTemp, Log, TEXT("AIController OnPossess: BehaviorTreeAsset is set: %s"), *BehaviorTreeAsset->GetName());
		if (!BehaviorTreeAsset->BlackboardAsset)
		{
			UE_LOG(LogTemp, Error, TEXT("AIController OnPossess: BehaviorTreeAsset '%s' has no assigned BlackboardAsset!"), *BehaviorTreeAsset->GetName());
			return;
		}
		UE_LOG(LogTemp, Log, TEXT("AIController OnPossess: Using BlackboardAsset: %s"), *BehaviorTreeAsset->BlackboardAsset->GetName());

		// 使用行为树的黑板资源初始化基类的 BlackboardComponent
		UBlackboardComponent* BlackboardCompPtr = Blackboard;
		bool bSuccess = UseBlackboard(BehaviorTreeAsset->BlackboardAsset, BlackboardCompPtr);

		if (bSuccess && Blackboard) // 确保 UseBlackboard 成功且 Blackboard 指针有效
		{
			UE_LOG(LogTemp, Log, TEXT("AIController OnPossess: UseBlackboard successful. BlackboardComponent is valid."));

			// 运行行为树
			bool bRunSuccess = RunBehaviorTree(BehaviorTreeAsset);
			if (!bRunSuccess)
			{
				UE_LOG(LogTemp, Error, TEXT("AIController OnPossess: Failed to run BehaviorTree %s on %s."), *BehaviorTreeAsset->GetName(), *EnemyCharacter->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("AIController OnPossess: Successfully running BehaviorTree %s on %s."), *BehaviorTreeAsset->GetName(), *EnemyCharacter->GetName());
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AIController OnPossess: UseBlackboard failed or BlackboardComponent is still NULL after UseBlackboard on %s."), *EnemyCharacter->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController OnPossess: BehaviorTreeAsset is not set for %s."), *EnemyCharacter->GetName());
	}
}
