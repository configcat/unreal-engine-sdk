// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "ConfigCatSettings.h"

FName UConfigCatSettings::GetContainerName() const
{
	return TEXT("Project");
}

FName UConfigCatSettings::GetCategoryName() const
{
	return TEXT("Feature Flags");
}
FName UConfigCatSettings::GetSectionName() const
{
	return TEXT("ConfigCat");
}

#if WITH_EDITOR
FText UConfigCatSettings::GetSectionText() const
{
	const FName DisplaySectionName = GetSectionName();
	return FText::FromName(DisplaySectionName);
}
#endif