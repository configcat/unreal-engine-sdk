// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "ConfigCatSettingsDetailCustomization.h"

#include <DetailLayoutBuilder.h>

TSharedRef<IDetailCustomization> FConfigCatSettingsDetailCustomization::MakeInstance()
{
	return MakeShared<FConfigCatSettingsDetailCustomization>();
}

void FConfigCatSettingsDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	// By default, Unreal splits the category display name based on capitalization (ConfigCat → Config Cat)
	// To avoid this we are overriding the ConfigCat category and forcing it to show up as ConfigCat (without a space)
	DetailBuilder.EditCategory("ConfigCat", INVTEXT("ConfigCat"));
}