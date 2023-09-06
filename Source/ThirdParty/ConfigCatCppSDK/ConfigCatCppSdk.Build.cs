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
			string Folder = Path.Combine(ModuleDirectory, "Binaries", "Win64");
			AddPrecompiledLibraries(Folder, "*.lib");
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			if(Target.Architecture == UnrealArch.Arm64)
			{
				string Folder = Path.Combine(ModuleDirectory, "Binaries", "Mac", "Arm64");
				AddPrecompiledLibraries(Folder, "*.a");
			}
			else
			{
				string Folder = Path.Combine(ModuleDirectory, "Binaries", "Mac", "X64");
				AddPrecompiledLibraries(Folder, "*.a");
			}
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			string Folder = Path.Combine(ModuleDirectory, "Binaries", "Linux");
			AddPrecompiledLibraries(Folder, "*.a");
		}
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			string Folder = Path.Combine(ModuleDirectory, "Binaries", "Android");
			AddPrecompiledLibraries(Folder, "*.a");
		}
		else if(Target.Platform == UnrealTargetPlatform.IOS)
		{
			string Folder = Path.Combine(ModuleDirectory, "Binaries", "iOS");
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
