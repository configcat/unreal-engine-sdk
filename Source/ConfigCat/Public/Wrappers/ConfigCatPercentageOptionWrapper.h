// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ThirdParty/ConfigCatCppSDK/Include/config.h>

#include "ConfigCatPercentageOptionWrapper.generated.h"

class UConfigCatValueWrapper;

UCLASS(meta = (DisplayName = "ConfigCat Percentage Option"))
class CONFIGCAT_API UConfigCatPercentageOptionWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatPercentageOptionWrapper* CreatePercentageOption(const configcat::PercentageOption& InPercentageOption);

	UFUNCTION(BlueprintPure, Category = "PercentageOption", meta = (Keywords = "ConfigCat"))
	uint8 GetPercentage() const;

	UFUNCTION(BlueprintPure, Category = "PercentageOption", meta = (Keywords = "ConfigCat"))
	FString GetVariationId() const;
	
	UFUNCTION(BlueprintPure, Category = "PercentageOption", meta = (Keywords = "ConfigCat"))
	UConfigCatValueWrapper* GetValue() const;
	
	configcat::PercentageOption PercentageOption;
};
