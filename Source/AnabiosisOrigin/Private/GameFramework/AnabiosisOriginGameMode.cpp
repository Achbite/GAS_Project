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
/*
* 文件名: AnabiosisOriginGameMode.cpp
* 功能描述： 实现游戏模式 AAnabiosisOriginGameMode 的核心逻辑。
*            包括设置默认的 Pawn 和 PlayerController 类，以及管理调试信息的显示。
* 结构：
* - 构造函数：设置默认类。
* - SetDebugCategoryEnabled：启用或禁用调试类别。
* - IsDebugCategoryEnabled：检查调试类别是否启用。
* - DebugMessage：根据启用的类别显示调试信息（日志和屏幕）。
*/

#include "GameFramework/AnabiosisOriginGameMode.h"
#include "Characters/AnabiosisOriginCharacter.h" // 包含玩家角色头文件
#include "Controllers/AnabiosisPlayerController.h" // 包含玩家控制器头文件
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h" // 包含 GWorld
#include "Engine/Engine.h" // 包含 GEngine
#include "Misc/OutputDevice.h" // 包含日志相关

AAnabiosisOriginGameMode::AAnabiosisOriginGameMode()
{
	// 设置默认 Pawn 类为蓝图 BP_ThirdPersonCharacter
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	// else
	// {
		// 如果找不到蓝图，记录错误 (注释掉以清理日志)
		// UE_LOG(LogAnabiosisOrigin, Error, TEXT("Failed to find DefaultPawnClass blueprint '/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter'."));
	// }

	// 设置默认玩家控制器类
	PlayerControllerClass = AAnabiosisPlayerController::StaticClass();
}

void AAnabiosisOriginGameMode::SetDebugCategoryEnabled(EAnabiosisDebugCategory Category, bool bEnabled)
{
	if (bEnabled)
	{
		EnabledDebugCategories.Add(Category);
		// 如果启用 "All"，则添加所有其他类别
		if (Category == EAnabiosisDebugCategory::All)
		{
			// 遍历枚举值 (不包括 All 本身)
			for (uint8 i = 0; i < static_cast<uint8>(EAnabiosisDebugCategory::All); ++i)
			{
				EnabledDebugCategories.Add(static_cast<EAnabiosisDebugCategory>(i));
			}
		}
	}
	else
	{
		EnabledDebugCategories.Remove(Category);
		// 如果禁用 "All"，则清空所有类别
		if (Category == EAnabiosisDebugCategory::All)
		{
			EnabledDebugCategories.Empty();
		}
	}
}

bool AAnabiosisOriginGameMode::IsDebugCategoryEnabled(EAnabiosisDebugCategory Category) const
{
	// 检查是否直接启用了该类别，或者启用了 "All"
	return EnabledDebugCategories.Contains(Category) || EnabledDebugCategories.Contains(EAnabiosisDebugCategory::All);
}

void AAnabiosisOriginGameMode::DebugMessage(const FString& Message, EAnabiosisDebugCategory Category)
{
	// 检查 GWorld 是否有效
	if (!GWorld) return;

	// 获取当前游戏模式
	AAnabiosisOriginGameMode* GameMode = Cast<AAnabiosisOriginGameMode>(GWorld->GetAuthGameMode());
	if (GameMode)
	{
		// 检查调试类别是否启用
		if (GameMode->IsDebugCategoryEnabled(Category))
		{
			// 获取类别名称字符串
			const FString CategoryName = StaticEnum<EAnabiosisDebugCategory>()->GetNameStringByValue(static_cast<int64>(Category));

			// 输出到日志 (保留，由调试系统控制)
			UE_LOG(LogAnabiosisOrigin, Log, TEXT("[%s] %s"), *CategoryName, *Message);

			// 输出到屏幕 (如果 GEngine 有效) (保留，由调试系统控制)
			if (GEngine)
			{
				// 使用黄色显示调试信息
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("[%s] %s"), *CategoryName, *Message));
			}
		}
	}
}
