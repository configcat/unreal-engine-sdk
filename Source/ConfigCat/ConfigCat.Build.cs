// Copyright (c) ConfigCat 2024. All Rights Reserved.

using UnrealBuildTool;

public class ConfigCat : ModuleRules
{
	public ConfigCat(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"DeveloperSettings",
			"Projects",
			"Engine",
			"HTTP"
		});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"ConfigCatWrappers",
			"ConfigCatCppSdk"
		});

		PrivateIncludePaths.Add("ThirdParty");

		if (Target.Version.MajorVersion < 5 || (Target.Version.MajorVersion == 5 && Target.Version.MinorVersion < 3))
		{
			// The first request using the Auto Polling mode blocks the main thread until the HTTP requests on a secondary thread are complete
			// Before UE 5.3, HTTP requests need to be completed on the main thread, which results in a deadlock
			// To avoid this, we will perform a manual fetch on the main thread before the user gets the chance to request a config

			PrivateDefinitions.Add("CONFIGCAT_HTTPTHREAD_WORKAROUND");
		}

		bEnableExceptions = true;
	}
}