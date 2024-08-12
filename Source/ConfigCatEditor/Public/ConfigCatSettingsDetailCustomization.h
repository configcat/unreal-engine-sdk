// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <IDetailCustomization.h>
#include <Templates/SharedPointer.h>

class FConfigCatSettingsDetailCustomization final : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

private:
	// Begin IDetailCustomization interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	// End IDetailCustomization interface
};
