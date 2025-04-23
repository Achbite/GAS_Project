/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: EnemyAIController.cpp
* 功能描述： 实现敌人 AI 控制器 AEnemyAIController 的具体逻辑。
*            负责在 Possess Pawn 时初始化并运行行为树和黑板。
* 结构：
* - 构造函数：创建行为树组件。
* - OnPossess：当控制器控制 Pawn 时调用，获取必要的组件（AI 行为组件），初始化黑板，并运行行为树。
*/

#include "AI/EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Characters/EnemyBaseCharacter.h" // 需要包含 Pawn 类型以获取组件
#include "AI/AiBehaviorComponent.h"       // 需要包含 AI 行为组件
#include "GameFramework/Pawn.h" // 包含 Pawn 头文件
#include "BehaviorTree/BlackboardData.h" // 包含 BlackboardData

AEnemyAIController::AEnemyAIController()
{
	// 创建行为树组件
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

	// AAIController 基类已经有一个 BlackboardComponent，通常使用那个，无需自己创建
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// 检查传入的 Pawn 是否有效
	if (!InPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("AI控制器 OnPossess：传入的 Pawn 为空！"));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("AI控制器 OnPossess：正在控制 Pawn：%s"), *InPawn->GetName());

	// 尝试将 Pawn 转换为敌人基础角色类型
	AEnemyBaseCharacter* EnemyCharacter = Cast<AEnemyBaseCharacter>(InPawn);
	if (!EnemyCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("AI控制器 OnPossess：被控制的 Pawn '%s' 不是 AEnemyBaseCharacter 类型。"), *InPawn->GetName());
		return;
	}

	// 获取 AI 行为组件
	AiBehaviorComp = EnemyCharacter->FindComponentByClass<UAiBehaviorComponent>();
	if (!AiBehaviorComp)
	{
		UE_LOG(LogTemp, Error, TEXT("AI控制器 OnPossess：在 %s 上找不到 UAiBehaviorComponent。"), *EnemyCharacter->GetName());
		// 注意：AiBehaviorComponent 的 InitializeBehavior 应该在 Character 的初始化流程中被调用
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AI控制器 OnPossess：在 %s 上找到 AiBehaviorComponent。"), *EnemyCharacter->GetName());
	}

	// 初始化并运行行为树
	if (BehaviorTreeAsset) // 检查行为树资源是否已设置
	{
		UE_LOG(LogTemp, Log, TEXT("AI控制器 OnPossess：行为树资源已设置：%s"), *BehaviorTreeAsset->GetName());
		// 检查行为树是否关联了黑板资源
		if (!BehaviorTreeAsset->BlackboardAsset)
		{
			UE_LOG(LogTemp, Error, TEXT("AI控制器 OnPossess：行为树资源 '%s' 没有分配黑板资源！"), *BehaviorTreeAsset->GetName());
			return;
		}
		UE_LOG(LogTemp, Log, TEXT("AI控制器 OnPossess：正在使用黑板资源：%s"), *BehaviorTreeAsset->BlackboardAsset->GetName());

		// 获取或创建 BlackboardComponent
		// AAIController 基类自带 BlackboardComponent，UseBlackboard 会初始化它
		UBlackboardComponent* BlackboardCompPtr = Blackboard; // 获取基类的 BlackboardComponent 指针
		bool bSuccess = UseBlackboard(BehaviorTreeAsset->BlackboardAsset, BlackboardCompPtr); // 使用行为树的黑板资源初始化
		// UseBlackboard 成功后，基类的 BlackboardComponent (即 Blackboard) 会被正确设置
		if (bSuccess)
		{
			// 记录 UseBlackboard 成功
			UE_LOG(LogTemp, Log, TEXT("AI控制器 OnPossess：UseBlackboard 成功。BlackboardComponent 是否有效：%s"), Blackboard ? TEXT("是") : TEXT("否"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AI控制器 OnPossess：UseBlackboard 失败！"));
			return; // 如果 UseBlackboard 失败，则不继续
		}

		// 再次检查 BlackboardComponent 是否有效
		if (Blackboard)
		{
			// 可以在这里初始化 Blackboard 的一些初始值，例如 SelfActor
			// Blackboard->SetValueAsObject(FName("SelfActor"), EnemyCharacter); // 通常行为树会自动设置 SelfActor

			// 检查 SelfActor 是否已设置 (通常由引擎自动完成)
			AActor* SelfActor = Cast<AActor>(Blackboard->GetValueAsObject(FName("SelfActor")));
			UE_LOG(LogTemp, Log, TEXT("AI控制器 OnPossess：黑板 'SelfActor' 键值：%s"), SelfActor ? *SelfActor->GetName() : TEXT("空"));

			// 运行行为树
			bool bRunSuccess = RunBehaviorTree(BehaviorTreeAsset);
			if (!bRunSuccess)
			{
				UE_LOG(LogTemp, Error, TEXT("AI控制器 OnPossess：在 %s 上运行行为树 %s 失败。"), *EnemyCharacter->GetName(), *BehaviorTreeAsset->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("AI控制器 OnPossess：在 %s 上成功运行行为树 %s。"), *EnemyCharacter->GetName(), *BehaviorTreeAsset->GetName());
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AI控制器 OnPossess：在 %s 上执行 UseBlackboard 后 BlackboardComponent 仍然为空。"), *EnemyCharacter->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI控制器 OnPossess：未为 %s 设置行为树资源 BehaviorTreeAsset。"), *EnemyCharacter->GetName());
	}
}
