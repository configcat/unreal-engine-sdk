// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "ConfigCat.h"

#include <Misc/Paths.h>

FString FConfigCatModule::GetContentFolder()
{
	return FPaths::ProjectContentDir() + TEXT("ConfigCat");
}

IMPLEMENT_MODULE(FConfigCatModule, ConfigCat)
