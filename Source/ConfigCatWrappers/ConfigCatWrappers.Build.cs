using UnrealBuildTool;

public class ConfigCatWrappers : ModuleRules
{
	public ConfigCatWrappers(ReadOnlyTargetRules Target) : base(Target)
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
			"ConfigCatCppSdk"
		});
		
		PrivateIncludePaths.Add("ThirdParty");
        
		bEnableExceptions = true;
	}
}