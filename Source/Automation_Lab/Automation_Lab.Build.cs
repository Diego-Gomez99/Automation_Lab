// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Automation_Lab : ModuleRules
{
	public Automation_Lab(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
        
        // Modules to can scrite and eject Automations Tests
        if (Target.Type == TargetType.Editor)
        {
	        PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "AutomationController"});
        }
	}
}
