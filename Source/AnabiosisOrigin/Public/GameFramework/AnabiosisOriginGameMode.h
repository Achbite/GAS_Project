/* 
 * Copyright (C) 2025 [Wang]
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 3 of the License, or 
 * (at any later version. 
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with this program.  If not, see https://www.gnu.org/licenses/. 
 */
// Copyright Epic Games, Inc. All Rights Reserved.

/*
* 文件名: AnabiosisOriginGameMode.h
* 功能描述：
* - 管理游戏核心规则
* - 处理调试系统
* - 控制游戏流程
*
* 核心系统：
* - 调试系统：控制调试信息的显示
* - 游戏规则：定义基本游戏规则
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AnabiosisOriginTypes.h"
#include "AnabiosisOriginGameMode.generated.h"

UCLASS(minimalapi)
class AAnabiosisOriginGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AAnabiosisOriginGameMode();

    // 调试功能
    /** 设置调试类别的启用状态 */
    UFUNCTION(BlueprintCallable, Category = "调试")
    void SetDebugCategoryEnabled(EAnabiosisDebugCategory Category, bool bEnabled);

    /** 获取指定调试类别是否启用 */
    UFUNCTION(BlueprintPure, Category = "调试")
    bool IsDebugCategoryEnabled(EAnabiosisDebugCategory Category) const;

    /** 输出调试信息 */
    static void DebugMessage(const FString& Message, EAnabiosisDebugCategory Category = EAnabiosisDebugCategory::None);

protected:
    /** 已启用的调试类别集合 */
    UPROPERTY()
    TSet<EAnabiosisDebugCategory> EnabledDebugCategories;
};
