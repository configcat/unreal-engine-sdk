// Copyright (c) ConfigCat 2023. All Rights Reserved.

using System.Collections.Generic;
using System.IO;
using UnrealBuildTool;

public class ConfigCatCppSdk : ModuleRules
{
	public ConfigCatCppSdk(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		AddEngineThirdPartyPrivateStaticDependencies(Target, "libcurl");
		AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");


		string libraryPath = Path.Combine(ModuleDirectory, "Binaries", Target.Platform.ToString());
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add(Path.Combine(libraryPath, "cpr" + ".lib"));
			PublicAdditionalLibraries.Add(Path.Combine(libraryPath, "libcurl" + ".lib"));
			PublicAdditionalLibraries.Add(Path.Combine(libraryPath, "hash-library" + ".lib"));
			PublicAdditionalLibraries.Add(Path.Combine(libraryPath, "configcat" + ".lib"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			//TODO: add mac libraries
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			PublicAdditionalLibraries.Add(Path.Combine(libraryPath, "libcpr" + ".a"));
			PublicAdditionalLibraries.Add(Path.Combine(libraryPath, "libhash-library" + ".a"));
			PublicAdditionalLibraries.Add(Path.Combine(libraryPath, "libconfigcat" + ".a"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PublicAdditionalLibraries.Add(Path.Combine(libraryPath, "libcpr" + ".a"));
			PublicAdditionalLibraries.Add(Path.Combine(libraryPath, "libhash-library" + ".a"));
			PublicAdditionalLibraries.Add(Path.Combine(libraryPath, "libconfigcat" + ".a"));
		}
	}
}
