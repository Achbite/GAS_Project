/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: BTService_DetectPlayer.h
* 功能描述： 定义行为树服务节点 UBTService_DetectPlayer。
*            该服务用于周期性地检测玩家，并更新黑板中的目标和 AI 状态。
* 结构：
* - 继承自 UBTService_BlackboardBase。
* - 包含用于配置检测逻辑的属性（如目标 Actor 键、AI 状态键）。
* - 缓存常用组件以提高性能。
* - 实现 TickNode 函数执行核心检测逻辑。
* - 实现 HasLineOfSight 函数进行视线检查。
*/

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_DetectPlayer.generated.h"

// 前向声明
class AAIController;
class AEnemyBaseCharacter;
class UAiBehaviorComponent;
class UBlackboardComponent;
class UBehaviorTreeComponent;

/**
 * @brief 行为树服务，用于周期性检测玩家并更新黑板。
 */
UCLASS()
class ANABIOSISORIGIN_API UBTService_DetectPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	/** 构造函数，设置节点名称和默认值 */
	UBTService_DetectPlayer();

protected:
	/**
	 * @brief 服务节点的核心逻辑，在每个 Tick 执行。
	 * @param OwnerComp 行为树组件。
	 * @param NodeMemory 节点内存。
	 * @param DeltaSeconds 时间增量。
	 */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	/** 黑板键：用于存储检测到的目标 Actor */
	UPROPERTY(EditAnywhere, Category = "AI|Blackboard")
	FBlackboardKeySelector TargetActorKey;

	/** 黑板键：用于存储当前的 AI 状态 (Gameplay Tag Name) */
	UPROPERTY(EditAnywhere, Category = "AI|Blackboard")
	FBlackboardKeySelector AIStateKey;

private:
	/**
	 * @brief 缓存必要的组件引用以提高性能。
	 * @param OwnerComp 行为树组件。
	 * @return 如果所有必要的组件都有效，则返回 true。
	 */
	bool CacheComponents(UBehaviorTreeComponent& OwnerComp);

	/**
	 * @brief 检查拥有者 AI 是否对目标 Actor 有视线。
	 * @param OwnerController 拥有者 AI 控制器。
	 * @param TargetActor 目标 Actor。
	 * @return 如果有视线，则返回 true。
	 */
	bool HasLineOfSight(AAIController* OwnerController, const AActor* TargetActor) const;

	// --- 缓存的组件指针 ---
	/** 缓存的 AI 行为组件 */
	UPROPERTY(Transient)
	TObjectPtr<UAiBehaviorComponent> CachedAiBehaviorComp;

	/** 缓存的拥有者角色 */
	UPROPERTY(Transient)
	TObjectPtr<AEnemyBaseCharacter> CachedOwnerCharacter;

	/** 缓存的拥有者 AI 控制器 */
	UPROPERTY(Transient)
	TObjectPtr<AAIController> CachedOwnerController;

	/** 缓存的黑板组件 */
	UPROPERTY(Transient)
	TObjectPtr<UBlackboardComponent> CachedBlackboardComp;
};
