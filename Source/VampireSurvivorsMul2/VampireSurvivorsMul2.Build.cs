// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VampireSurvivorsMul2 : ModuleRules
{
	public VampireSurvivorsMul2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "VampireSurvivorsMul2" });
        
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "UMG", "VampireSurvivorsMulPlugin", "ActorOwnableUserWidgetPlugin", "AIStatePlugin", "LobbyPlugin" });
	}
}
