// Copyright (c) ConfigCat 2024. All Rights Reserved.

using UnrealBuildTool;

public class ConfigCatEditor : ModuleRules
{
	public ConfigCatEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"DeveloperToolSettings",
			"EditorSubsystem",
			"Engine",
			"Projects",

			"ConfigCat"
		});
	}
}