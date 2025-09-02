﻿// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ThirdParty/ConfigCatCppSDK/Include/config.h>

#include "UObject/Object.h"

#include "ConfigCatSettingValueContainerWrapper.generated.h"

class UConfigCatValueWrapper;
UCLASS(meta = (DisplayName = "ConfigCat Setting Value Container"))
class CONFIGCAT_API UConfigCatSettingValueContainerWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatSettingValueContainerWrapper* CreateSettingValue(const configcat::SettingValueContainer& SettingValueContainer);

	UFUNCTION(BlueprintPure, Category = "SettingValueContainer", meta = (Keywords = "ConfigCat"))
	FString GetVariationId() const;
	UFUNCTION(BlueprintPure, Category = "SettingValueContainer", meta = (Keywords = "ConfigCat"))
	UConfigCatValueWrapper* GetValue() const;

	configcat::SettingValueContainer SettingValueContainer;
};
