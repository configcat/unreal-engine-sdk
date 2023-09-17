// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "ConfigCatEditorSubsystem.h"

#include <Settings/ProjectPackagingSettings.h>

#include "ConfigCat.h"
#include "ConfigCatLog.h"

#include <Interfaces/IPluginManager.h>


void UConfigCatEditorSubsystem::EnsureContentIsPackaged()
{
	FString FolderName = FConfigCatModule::GetContentFolder();
	FPaths::MakePathRelativeTo(FolderName, *FPaths::ProjectContentDir());

	const FDirectoryPath ConfigCatContentFolder = {FolderName};
	UProjectPackagingSettings* ProjectPackagingSettings = GetMutableDefault<UProjectPackagingSettings>();
	const bool bContainsPath = ProjectPackagingSettings->DirectoriesToAlwaysStageAsNonUFS.ContainsByPredicate(
		[ConfigCatContentFolder](const FDirectoryPath& Path)
		{
			return Path.Path == ConfigCatContentFolder.Path;
		}
	);

	if (!bContainsPath)
	{
		ProjectPackagingSettings->DirectoriesToAlwaysStageAsNonUFS.Add(ConfigCatContentFolder);
		ProjectPackagingSettings->SaveConfig();

		UE_LOG(LogConfigCat, Display, TEXT("ConfigCat folder was added to Additional Non-Asset Directories To Copy"));
	}
	else
	{
		UE_LOG(LogConfigCat, Display, TEXT("ConfigCat folder was already part of Additional Non-Asset Directories To Copy"));
	}
}

void UConfigCatEditorSubsystem::CopyLatestSslCertificate()
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	const FString ConfigCatContent = FPaths::ConvertRelativePathToFull(FConfigCatModule::GetContentFolder());
	const bool bFolderCreated = PlatformFile.CreateDirectoryTree(*ConfigCatContent);
	if(!bFolderCreated)
	{
		UE_LOG(LogConfigCat, Warning, TEXT("Failed to create ConfigCat content folder."));
		return;
	}

	FString PluginCertificate = IPluginManager::Get().FindPlugin(TEXT("ConfigCat"))->GetBaseDir() + TEXT("/Extras/certificates/globalsign-root-ca.pem");
	PluginCertificate = FPaths::ConvertRelativePathToFull(PluginCertificate);

	const FString ContentCertificate = ConfigCatContent + TEXT("/globalsign-root-ca.pem");
	const bool bCopySuccess = PlatformFile.CopyFile(*ContentCertificate, *PluginCertificate);
	if(!bCopySuccess)
	{
		UE_LOG(LogConfigCat, Warning, TEXT("Failed to copy SSL certificate to ConfigCat content folder."))
	}

	UE_LOG(LogConfigCat, Display, TEXT("Copied SSL certificate from %s to %s. Success: %s"), *PluginCertificate, *ContentCertificate);
}

void UConfigCatEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	EnsureContentIsPackaged();

	CopyLatestSslCertificate();
}
