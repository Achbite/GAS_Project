/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: AnabiosisOriginGameMode.h
* 功能描述： 定义游戏模式 AAnabiosisOriginGameMode。
*            负责管理游戏规则、状态和调试信息的显示。
* 结构：
* - 继承自 AGameModeBase。
* - 提供启用/禁用调试类别和显示调试信息的功能。
* - 存储当前启用的调试类别。
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AnabiosisOriginTypes.h" // 包含调试类别枚举
#include "AnabiosisOriginGameMode.generated.h"

/**
 * @brief 项目的游戏模式基类。
 */
UCLASS(minimalapi)
class AAnabiosisOriginGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** 构造函数 */
	AAnabiosisOriginGameMode();

	/**
	 * @brief 启用或禁用指定的调试类别。
	 * @param Category 要设置的调试类别。
	 * @param bEnabled 是否启用。
	 */
	UFUNCTION(BlueprintCallable, Category = "Debug")
	void SetDebugCategoryEnabled(EAnabiosisDebugCategory Category, bool bEnabled);

	/**
	 * @brief 检查指定的调试类别是否已启用。
	 * @param Category 要检查的调试类别。
	 * @return 如果已启用，则返回 true。
	 */
	UFUNCTION(BlueprintPure, Category = "Debug")
	bool IsDebugCategoryEnabled(EAnabiosisDebugCategory Category) const;

	/**
	 * @brief 显示调试信息（日志和屏幕）。
	 * @param Message 要显示的消息。
	 * @param Category 消息所属的调试类别。
	 */
	UFUNCTION(BlueprintCallable, Category = "Debug", meta = (WorldContext = "WorldContextObject"))
	static void DebugMessage(const FString& Message, EAnabiosisDebugCategory Category);

private:
	/** 当前启用的调试类别集合 */
	TSet<EAnabiosisDebugCategory> EnabledDebugCategories;
};
