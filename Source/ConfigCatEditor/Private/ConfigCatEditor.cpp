// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "ConfigCatEditor.h"

#include <PropertyEditorModule.h>

#include "ConfigCatSettings.h"
#include "ConfigCatSettingsDetailCustomization.h"

void FConfigCatEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(UConfigCatSettings::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FConfigCatSettingsDetailCustomization::MakeInstance));
}

void FConfigCatEditorModule::ShutdownModule()
{
	if (FPropertyEditorModule* PropertyModule = FModuleManager::GetModulePtr<FPropertyEditorModule>("PropertyEditor"))
	{
		PropertyModule->UnregisterCustomClassLayout(UConfigCatSettings::StaticClass()->GetFName());
	}
}

IMPLEMENT_MODULE(FConfigCatEditorModule, ConfigCatEditor)