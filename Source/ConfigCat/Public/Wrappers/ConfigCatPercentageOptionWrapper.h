// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include "ConfigCatCppSDK/Include/config.h"

#include "ConfigCatPercentageOptionWrapper.generated.h"

class UConfigCatValueWrapper;

UCLASS(meta = (DisplayName = "ConfigCat Percentage Option"))
class CONFIGCAT_API UConfigCatPercentageOptionWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatPercentageOptionWrapper* CreatePercentageOption(const configcat::PercentageOption& InPercentageOption);

	UFUNCTION(BlueprintPure, Category = "ConfigCat|PercentageOption")
	uint8 GetPercentage() const;

	UFUNCTION(BlueprintPure, Category = "ConfigCat|PercentageOption")
	FString GetVariationId() const;
	
	UFUNCTION(BlueprintPure, Category = "ConfigCat|PercentageOption")
	UConfigCatValueWrapper* GetValue() const;
	
	configcat::PercentageOption PercentageOption;
};
