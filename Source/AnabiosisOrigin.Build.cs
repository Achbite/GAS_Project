// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AnabiosisOrigin : ModuleRules
{
    public AnabiosisOrigin(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        IWYUSupport = IWYUSupport.None; // 或 IWYUSupport.Full

        PublicIncludePaths.AddRange(new string[] {
            "AnabiosisOrigin/Public"
        });

        PrivateIncludePaths.AddRange(new string[] {
            "AnabiosisOrigin/Private"
        });

        // 确保 AIModule 在 Public 中，因为 EnemyAIController.h 继承自 AAIController
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities", "GameplayTags", "GameplayTasks", "NavigationSystem", "AIModule" }); // 确认 AIModule 在这里

        // Private 中不需要重复添加 AIModule
        PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTasks" });

        bUseUnity = false;  // 禁用Unity构建以更精确地控制哪些文件被编译
    }
}