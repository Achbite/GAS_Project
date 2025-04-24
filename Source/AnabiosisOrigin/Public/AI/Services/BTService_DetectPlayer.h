/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: BTService_DetectPlayer.h
* 功能描述： 定义行为树服务 UBTService_DetectPlayer。
*            该服务周期性地检测玩家，检查距离和视线，并更新黑板中的目标 Actor 和 AI 状态。
* 结构：
* - UBTService_DetectPlayer：行为树服务类。
*   - TickNode：服务周期的核心逻辑，执行检测和状态更新。
*   - TargetActorKey：黑板键，用于存储检测到的目标 Actor。
*   - AIStateKey：黑板键，用于存储当前的 AI 状态 (FName 类型)。
*   - HasLineOfSight：辅助函数，执行视线检查。
*   - 缓存成员：缓存指向行为组件、角色、控制器和黑板的指针以提高效率。
*   - CacheComponents：辅助函数，用于获取并缓存必要的组件。
*/

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_DetectPlayer.generated.h"

// 前向声明
class AEnemyBaseCharacter;
class UAiBehaviorComponent;
class AAIController; // 添加 AIController 前向声明
class UBlackboardComponent; // 添加 BlackboardComponent 前向声明

/**
 * 该服务负责检测范围内的玩家，进行视线检查，并根据结果更新 Blackboard 中的 TargetActor 和 AIState。
 */
UCLASS()
class ANABIOSISORIGIN_API UBTService_DetectPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_DetectPlayer();

protected:
	/** 服务周期性执行的函数，包含主要的检测逻辑 */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	/** Blackboard Key 选择器，用于设置/获取目标 Actor */
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TargetActorKey;

	/** Blackboard Key 选择器，用于设置/获取 AI 状态 (Name 类型) */
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector AIStateKey;

private:
	/** 辅助函数：执行视线检查 */
	bool HasLineOfSight(AAIController* OwnerController, const AActor* TargetActor) const;

	/** 缓存的 AiBehaviorComponent 指针 */
	UPROPERTY(Transient)
	TObjectPtr<UAiBehaviorComponent> CachedAiBehaviorComp;

	/** 缓存的 EnemyBaseCharacter 指针 */
	UPROPERTY(Transient)
	TObjectPtr<AEnemyBaseCharacter> CachedOwnerCharacter;

	/** 缓存的 AIController 指针 */
	UPROPERTY(Transient)
	TObjectPtr<AAIController> CachedOwnerController;

	/** 缓存的 BlackboardComponent 指针 */
	UPROPERTY(Transient)
	TObjectPtr<UBlackboardComponent> CachedBlackboardComp;

	/** 辅助函数：获取并缓存必要的组件，避免每次 Tick 都查找 */
	bool CacheComponents(UBehaviorTreeComponent& OwnerComp);
};
