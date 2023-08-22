// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>

#include <memory>

#include "ConfigCatSetting.generated.h"


struct FConfigCatValue;
namespace configcat
{
	struct Setting;
}
/**
 * Wrapper class for configcat::Setting
 */
USTRUCT(BlueprintType)
struct CONFIGCAT_API FConfigCatSetting
{
	GENERATED_BODY()

	FConfigCatSetting() = default;
	FConfigCatSetting(const configcat::Setting& InSetting);

	/**
	 * Internal Setting we want to expose in blueprints
	 */
	std::shared_ptr<configcat::Setting> Setting;
};

/**
 * Getters for all the properties of the configcat::Setting stored inside a FConfigCatSetting wrapper
 */
UCLASS()
class CONFIGCAT_API UConfigCatSettingAccessorsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/**
	 * Gets the value of the feature flag / setting
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Setting")
	static FConfigCatValue GetSettingValue(const FConfigCatSetting& Struct);
	/**
	 * Gets the rollout rules of the feature flag / setting
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Setting")
	static TArray<FConfigCatRolloutRule> GetSettingRolloutRules(const FConfigCatSetting& Struct);
	/**
	 * Gets the rollout percentage items of the feature flag / setting
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Setting")
	static TArray<FConfigCatRolloutPercentageItem> GetSettingRolloutPercentageItem(const FConfigCatSetting& Struct);
	/**
	 * Gets the variation identifier of the feature flag / setting
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Setting")
	static FString GetSettingVariationId(const FConfigCatSetting& Struct);
};