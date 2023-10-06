// Copyright (c) ConfigCat 2023. All Rights Reserved.

using UnrealBuildTool;

public class ConfigCat : ModuleRules
{
	public ConfigCat(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new[] {
			"Core",
			"CoreUObject",
			"DeveloperSettings",
			"Projects", 
			"Engine",
		});
		
		PrivateDependencyModuleNames.AddRange(new [] {
			"ConfigCatCppSdk",
		});

		PrivateIncludePaths.Add("ThirdParty");
	}
}
