/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: BTTask_ActivateAbilityByTag.cpp
* 功能描述： 实现 UBTTask_ActivateAbilityByTag 的逻辑。随机激活一个符合筛选条件的能力。
*/

#include "AI/Tasks/BTTask_ActivateAbilityByTag.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "BehaviorTree/BlackboardComponent.h" // Still included if base class remains BTTask_BlackboardBase
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Name.h" // <--- 重新添加此行

UBTTask_ActivateAbilityByTag::UBTTask_ActivateAbilityByTag()
{
	NodeName = "Activate Random Ability"; // Updated node name
}

EBTNodeResult::Type UBTTask_ActivateAbilityByTag::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	// 1. 验证控制器
	if (!AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: AIController is NULL."), *NodeName);
		return EBTNodeResult::Failed;
	}

	// 2. 获取 Pawn 和能力系统组件
	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: AIController does not possess a Pawn."), *NodeName);
		return EBTNodeResult::Failed;
	}

	UAbilitySystemComponent* AbilitySystemComponent = nullptr;
	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(ControlledPawn);
	if (AbilitySystemInterface)
	{
		AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();
	}

	if (!AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Could not find AbilitySystemComponent on Pawn %s."), *NodeName, *ControlledPawn->GetName());
		return EBTNodeResult::Failed;
	}

	// 3. 获取所有可激活的能力规格 (使用正确的函数名和返回类型)
	TArray<FGameplayAbilitySpec> ActivatableAbilities = AbilitySystemComponent->GetActivatableAbilities();

	// 4. 筛选能力 (如果设置了筛选标签)
	TArray<FGameplayAbilitySpec*> FilteredAbilities; // 存储指向符合条件的 Spec 的指针
	if (AbilityFilterTags.IsEmpty())
	{
		// 如果没有筛选标签，则所有可激活能力都符合条件
		for (const FGameplayAbilitySpec& Spec : ActivatableAbilities)
		{
			// Add pointers to all specs (const_cast needed if modification is intended, but here just for selection)
			// It's generally safer to work with indices if possible, but pointers are okay for read-only selection.
			FilteredAbilities.Add(const_cast<FGameplayAbilitySpec*>(&Spec));
		}
	}
	else
	{
		// 否则，只保留包含至少一个筛选标签的能力
		for (const FGameplayAbilitySpec& Spec : ActivatableAbilities)
		{
			if (Spec.Ability && Spec.Ability->AbilityTags.HasAny(AbilityFilterTags))
			{
				FilteredAbilities.Add(const_cast<FGameplayAbilitySpec*>(&Spec));
			}
		}
	}

	// 5. 检查是否有符合条件的能力
	if (FilteredAbilities.Num() == 0)
	{
		UE_LOG(LogTemp, Verbose, TEXT("%s: No activatable abilities found matching the filter criteria on %s."), *NodeName, *ControlledPawn->GetName());
		return EBTNodeResult::Failed; // 没有找到可激活的能力
	}

	// 6. 随机选择一个能力
	int32 RandomIndex = FMath::RandRange(0, FilteredAbilities.Num() - 1);
	FGameplayAbilitySpec* SelectedSpec = FilteredAbilities[RandomIndex]; // Now SelectedSpec is a pointer

	if (!SelectedSpec || !SelectedSpec->Ability) // Check pointer and ability within the spec
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Randomly selected ability spec or ability is invalid on %s."), *NodeName, *ControlledPawn->GetName());
		return EBTNodeResult::Failed;
	}

	// 7. 尝试激活选中的能力 (使用 Spec 的 Handle)
	bool bActivated = AbilitySystemComponent->TryActivateAbility(SelectedSpec->Handle);

	if (bActivated)
	{
		UE_LOG(LogTemp, Verbose, TEXT("%s: Successfully activated or attempted to activate random ability %s on %s."), *NodeName, *SelectedSpec->Ability->GetName(), *ControlledPawn->GetName());
		return EBTNodeResult::Succeeded; // 激活尝试成功
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("%s: Failed to activate random ability %s on %s (Could be on cooldown, lacking resources, blocked, etc.)."), *NodeName, *SelectedSpec->Ability->GetName(), *ControlledPawn->GetName());
		return EBTNodeResult::Failed; // 激活尝试失败
	}
}

FString UBTTask_ActivateAbilityByTag::GetStaticDescription() const
{
	// 提供在行为树编辑器中显示的描述
	if (AbilityFilterTags.IsEmpty())
	{
		return FString::Printf(TEXT("%s: Activate Random Ability"), *Super::GetStaticDescription());
	}
	else
	{
		return FString::Printf(TEXT("%s: Activate Random Ability (Filtered by: %s)"), *Super::GetStaticDescription(), *AbilityFilterTags.ToStringSimple());
	}
}
