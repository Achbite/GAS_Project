/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: BTTask_ActivateAbilityByTag.h
* 功能描述： 行为树任务，用于随机激活拥有者拥有的、符合筛选标签的 Gameplay Ability。
*/

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h" // Keep base class for potential future BB interactions if needed, or change to BTTask_Node
#include "GameplayTagContainer.h" // Include for FGameplayTagContainer
#include "BTTask_ActivateAbilityByTag.generated.h"

/**
 * 尝试随机激活 AI 控制的 Pawn 上的一个 Gameplay Ability。
 * 可以通过 AbilityFilterTags 筛选允许激活的能力。
 */
UCLASS()
class ANABIOSISORIGIN_API UBTTask_ActivateAbilityByTag : public UBTTask_BlackboardBase // Consider changing base class if BB is truly unused
{
	GENERATED_BODY()

public:
	UBTTask_ActivateAbilityByTag();

protected:
	/** 执行任务逻辑 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/** 获取任务描述字符串 */
	virtual FString GetStaticDescription() const override;

	/**
	 * 用于筛选可随机激活能力的标签容器。
	 * 如果为空，则所有可激活能力都可能被选中。
	 * 如果不为空，则只有同时拥有这些标签中至少一个的能力才会被选中。
	 */
	UPROPERTY(EditAnywhere, Category = Ability)
	FGameplayTagContainer AbilityFilterTags;

	// Removed AbilityTagKey
	// FBlackboardKeySelector AbilityTagKey;

private:
	// Removed IsAbilityTagKeyValid
	// bool IsAbilityTagKeyValid() const;
};
