// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>

#include <memory>

#include "ConfigCatSetting.generated.h"

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

	///**
	// * Checks if the struct holds any type value
	// */
	// UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	// static bool HasAnyValue(const FConfigCatValue& Struct);
};