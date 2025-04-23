/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: EnemyAIController.cpp
* 功能描述： 实现敌人 AI 控制器的具体逻辑。
*/

#include "AI/EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Characters/EnemyBaseCharacter.h" // 需要包含 Pawn 类型以获取组件
#include "AI/AiBehaviorComponent.h"       // 需要包含 AI 行为组件
#include "GameFramework/Pawn.h" // 包含 Pawn 头文件

AEnemyAIController::AEnemyAIController()
{
	// 创建行为树组件
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

	// 创建黑板组件 (AAIController 已经有一个 BlackboardComponent，我们通常使用那个)
	// BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent")); // 通常不需要自己创建

	// 初始化指针
	BehaviorTreeAsset = nullptr;
	AiBehaviorComp = nullptr;
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// --- 添加日志 ---
	if (!InPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::OnPossess: InPawn is NULL!"));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("AEnemyAIController::OnPossess: Possessing Pawn: %s"), *InPawn->GetName());
	// ---------------

	AEnemyBaseCharacter* EnemyCharacter = Cast<AEnemyBaseCharacter>(InPawn);
	if (!EnemyCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::OnPossess: Possessed Pawn '%s' is not an AEnemyBaseCharacter."), *InPawn->GetName());
		return;
	}

	// 获取 AI 行为组件
	AiBehaviorComp = EnemyCharacter->FindComponentByClass<UAiBehaviorComponent>();
	if (!AiBehaviorComp)
	{
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::OnPossess: Cannot find UAiBehaviorComponent on %s."), *EnemyCharacter->GetName());
		// 注意：AiBehaviorComponent 的 InitializeBehavior 应该在 Character 的 PostInitializeComponents 或 BeginPlay 中被调用
	}
	// --- 添加日志 ---
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AEnemyAIController::OnPossess: Found AiBehaviorComponent on %s."), *EnemyCharacter->GetName());
	}
	// ---------------


	// 初始化并运行行为树
	if (BehaviorTreeAsset)
	{
		// --- 添加日志 ---
		UE_LOG(LogTemp, Log, TEXT("AEnemyAIController::OnPossess: BehaviorTreeAsset is set: %s"), *BehaviorTreeAsset->GetName());
		if (!BehaviorTreeAsset->BlackboardAsset)
		{
			UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::OnPossess: BehaviorTreeAsset '%s' has no BlackboardAsset assigned!"), *BehaviorTreeAsset->GetName());
			return;
		}
		UE_LOG(LogTemp, Log, TEXT("AEnemyAIController::OnPossess: Using BlackboardAsset: %s"), *BehaviorTreeAsset->BlackboardAsset->GetName());
		// ---------------

		// 获取或创建 BlackboardComponent
		UBlackboardComponent* BlackboardCompPtr = BlackboardComponent.Get(); // 获取原始指针
		bool bSuccess = UseBlackboard(BehaviorTreeAsset->BlackboardAsset, BlackboardCompPtr); // 传递原始指针的引用
		if (bSuccess)
		{
			BlackboardComponent = BlackboardCompPtr; // 将可能更新的原始指针赋值回 TObjectPtr
			// --- 修改日志检查方式 ---
			UE_LOG(LogTemp, Log, TEXT("AEnemyAIController::OnPossess: UseBlackboard successful. BlackboardComponent valid: %s"), BlackboardComponent ? TEXT("true") : TEXT("false"));
			// -----------------------
		}
		// --- 添加日志 ---
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::OnPossess: UseBlackboard failed!"));
			return; // 如果 UseBlackboard 失败，则不继续
		}
		// ---------------

		// 检查 BlackboardComponent 是否有效 (UseBlackboard 成功后它应该被设置)
		if (BlackboardComponent)
		{
			// 可以在这里初始化 Blackboard 的一些值，如果需要的话
			// BlackboardComponent->SetValueAsVector(FName("HomeLocation"), EnemyCharacter->GetActorLocation());
			// --- 添加日志：检查 SelfActor ---
			AActor* SelfActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(FName("SelfActor")));
			UE_LOG(LogTemp, Log, TEXT("AEnemyAIController::OnPossess: Blackboard 'SelfActor' key value: %s"), SelfActor ? *SelfActor->GetName() : TEXT("NULL"));
			// -----------------------------

			// 运行行为树
			bool bRunSuccess = RunBehaviorTree(BehaviorTreeAsset);
			if (!bRunSuccess)
			{
				UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::OnPossess: Failed to run Behavior Tree %s on %s."), *BehaviorTreeAsset->GetName(), *EnemyCharacter->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("AEnemyAIController::OnPossess: Successfully running Behavior Tree %s on %s."), *BehaviorTreeAsset->GetName(), *EnemyCharacter->GetName());
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::OnPossess: BlackboardComponent is still NULL after UseBlackboard for %s."), *EnemyCharacter->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AEnemyAIController::OnPossess: BehaviorTreeAsset is not set for %s."), *EnemyCharacter->GetName());
	}
}
