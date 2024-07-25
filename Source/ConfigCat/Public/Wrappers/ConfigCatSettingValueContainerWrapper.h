// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ConfigCatCppSDK/Include/config.h>

#include "UObject/Object.h"

#include "ConfigCatSettingValueContainerWrapper.generated.h"

class UConfigCatValueWrapper;
UCLASS(DisplayName="Config Cat Setting Value Container")
class CONFIGCAT_API UConfigCatSettingValueContainerWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatSettingValueContainerWrapper* CreateSettingValue(const configcat::SettingValueContainer& SettingValueContainer);

	UFUNCTION(BlueprintPure, Category = "ConfigCat|SettingValueContainer")
	FString GetVariationId() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|SettingValueContainer")
	UConfigCatValueWrapper* GetValue() const;

	configcat::SettingValueContainer SettingValueContainer;
};
