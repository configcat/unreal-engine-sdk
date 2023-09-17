// Copyright (c) ConfigCat 2023. All Rights Reserved.

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using UnrealBuildTool;

public class ConfigCatCppSdk : ModuleRules
{
	public ConfigCatCppSdk(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		AddEngineThirdPartyPrivateStaticDependencies(Target, "libcurl");
		AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");
		AddEngineThirdPartyPrivateStaticDependencies(Target, "nghttp2");

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			string Folder = Path.Combine(ModuleDirectory, "Binaries", "Win64", "x64-windows");
			AddPrecompiledLibraries(Folder, "*.lib");
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			if(Target.Architecture == UnrealArch.Arm64)
			{
				//TODO: Change to match other naming convention when GitHub adds arm-64 macos runners
				string Folder = Path.Combine(ModuleDirectory, "Binaries", "Mac", "Arm64");
				AddPrecompiledLibraries(Folder, "*.a");
			}
			else
			{
				string Folder = Path.Combine(ModuleDirectory, "Binaries", "Mac", "x64-osx");
				AddPrecompiledLibraries(Folder, "*.a");
			}
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			string Folder = Path.Combine(ModuleDirectory, "Binaries", "Linux", "x64-linux-unreal");
			AddPrecompiledLibraries(Folder, "*.a");
		}
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			string Folder = Path.Combine(ModuleDirectory, "Binaries", "Android", "arm64-android");
			AddPrecompiledLibraries(Folder, "*.a");
		}
		else if(Target.Platform == UnrealTargetPlatform.IOS)
		{
			string Folder = Path.Combine(ModuleDirectory, "Binaries", "iOS", "arm64-ios");
			AddPrecompiledLibraries(Folder, "*.a");
		}
	}

	public void AddPrecompiledLibraries(string FolderPath, string Extension)
	{
		List<string> Files = Directory.GetFiles(FolderPath, Extension, SearchOption.AllDirectories).ToList();
		foreach (string File in Files)
		{
			PublicAdditionalLibraries.Add(Path.Combine(FolderPath, File));
			Console.WriteLine("Adding library:" + File);
		}
	}
}
