// Copyright (c) ConfigCat 2024. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class ConfigCatPlatformNetwork : ModuleRules
{
	protected virtual bool bPlatformSupportsLibCurl
	{
		get
		{
			return (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows) && !Target.WindowsPlatform.bUseXCurl) ||
			       Target.IsInPlatformGroup(UnrealPlatformGroup.Unix) ||
			       Target.IsInPlatformGroup(UnrealPlatformGroup.Android);
		}
	}

	protected virtual bool bPlatformSupportsXCurl
	{
		get { return Target.Platform.IsInGroup(UnrealPlatformGroup.Windows) && Target.WindowsPlatform.bUseXCurl; }
	}

	public ConfigCatPlatformNetwork(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", 
			"HTTP",
		});

		PrivateDefinitions.Add("WITH_CURL= " + ((bPlatformSupportsLibCurl || bPlatformSupportsXCurl) ? "1" : "0"));

		PrivateIncludePaths.Add(Path.Combine(EngineDirectory, "Source/Runtime/Online/HTTP/Private"));

		AddEngineThirdPartyPrivateStaticDependencies(Target, "libcurl");
		AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");
		AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");
		AddEngineThirdPartyPrivateStaticDependencies(Target, "nghttp2");
	}
}