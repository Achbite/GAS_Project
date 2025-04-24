/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: BTTask_ActivateAbilityByTag.h
* 功能描述： 定义行为树任务 UBTTask_ActivateAbilityByTag。
*            该任务用于随机激活 AI 拥有的、符合筛选标签的 Gameplay Ability。
* 结构：
* - UBTTask_ActivateAbilityByTag：行为树任务类。
*   - ExecuteTask：执行任务的核心逻辑，查找并尝试激活能力。
*   - GetStaticDescription：提供任务在编辑器中的描述。
*   - AbilityFilterTags：用于筛选可激活能力的标签容器。
*/

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h" // 基类提供访问 Blackboard 的能力
#include "GameplayTagContainer.h" // 包含 FGameplayTagContainer
#include "BTTask_ActivateAbilityByTag.generated.h"

/**
 * 尝试随机激活 AI 控制的 Pawn 上的一个 Gameplay Ability。
 * 可以通过 AbilityFilterTags 筛选允许激活的能力。
 */
UCLASS()
class ANABIOSISORIGIN_API UBTTask_ActivateAbilityByTag : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_ActivateAbilityByTag();

protected:
	/** 执行任务逻辑：查找匹配标签的能力并尝试激活 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/** 获取任务在行为树编辑器中的描述字符串 */
	virtual FString GetStaticDescription() const override;

	/**
	 * 用于筛选可随机激活能力的标签容器。
	 * 如果为空，则所有可激活能力都可能被选中。
	 * 如果不为空，则只有同时拥有这些标签中至少一个的能力才会被选中。
	 */
	UPROPERTY(EditAnywhere, Category = Ability)
	FGameplayTagContainer AbilityFilterTags;

	// 已移除 AbilityTagKey 和 IsAbilityTagKeyValid
};
