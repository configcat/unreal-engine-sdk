// Copyright (c) ConfigCat 2023. All Rights Reserved.

using UnrealBuildTool;

public class ConfigCat : ModuleRules
{
	public ConfigCat(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] {
			//TODO: Check if we can move some of them to Private
			"Core",
			"CoreUObject",
			"DeveloperSettings",
			"Projects", 
			"Engine",

			"ConfigCatCppSdk",
		});
	}
}
