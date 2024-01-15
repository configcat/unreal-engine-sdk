// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "ConfigCatEditorSubsystem.h"

#include <Settings/ProjectPackagingSettings.h>

#include "ConfigCat.h"
#include "ConfigCatLog.h"

void UConfigCatEditorSubsystem::EnsureContentIsPackaged()
{
	FString FolderName = FConfigCatModule::GetContentFolder();
	if (!FPaths::DirectoryExists(FolderName))
	{
		UE_LOG(LogConfigCat, Display, TEXT("ConfigCat folder doesn't exist. Skipping packaging."));
		return;
	}

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
		ProjectPackagingSettings->TryUpdateDefaultConfigFile();

		UE_LOG(LogConfigCat, Display, TEXT("ConfigCat folder was added to Additional Non-Asset Directories To Copy"));
	}
	else
	{
		UE_LOG(LogConfigCat, Display, TEXT("ConfigCat folder was already part of Additional Non-Asset Directories To Copy"));
	}
}

void UConfigCatEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	EnsureContentIsPackaged();
}
