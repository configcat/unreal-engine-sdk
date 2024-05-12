// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include "ConfigCatCppSDK/Include/config.h"

#include "ConfigCatPercentageOptionWrapper.generated.h"

UCLASS(DisplayName="Config Cat Percentage Option", Hidden)
class UConfigCatPercentageOptionWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatPercentageOptionWrapper* CreatePercentageOption(const configcat::PercentageOption& InPercentageOption);
	
	configcat::PercentageOption PercentageOption;
};
