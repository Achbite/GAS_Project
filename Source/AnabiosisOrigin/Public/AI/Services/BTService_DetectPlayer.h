/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: BTService_DetectPlayer.h
* 功能描述： 行为树服务，用于周期性检测玩家，更新目标和 AI 状态。
*/

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_DetectPlayer.generated.h"

class AEnemyBaseCharacter;
class UAiBehaviorComponent;

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
	/** 更新节点内存时调用 */
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

	/** 缓存的 AiBehaviorComponent */
	UPROPERTY(Transient) // 不需要保存
	TObjectPtr<UAiBehaviorComponent> CachedAiBehaviorComp;

	/** 缓存的 EnemyBaseCharacter */
	UPROPERTY(Transient)
	TObjectPtr<AEnemyBaseCharacter> CachedOwnerCharacter;

	/** 缓存的 AIController */
	UPROPERTY(Transient)
	TObjectPtr<AAIController> CachedOwnerController;

	/** 缓存的 BlackboardComponent */
	UPROPERTY(Transient)
	TObjectPtr<UBlackboardComponent> CachedBlackboardComp;

	/** 辅助函数：获取并缓存必要的组件 */
	bool CacheComponents(UBehaviorTreeComponent& OwnerComp);
};
