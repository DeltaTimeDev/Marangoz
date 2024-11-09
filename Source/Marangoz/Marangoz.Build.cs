// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Marangoz : ModuleRules
{
	public Marangoz(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
