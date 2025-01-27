// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SelfStudyDungoenGen : ModuleRules
{
	public SelfStudyDungoenGen(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
