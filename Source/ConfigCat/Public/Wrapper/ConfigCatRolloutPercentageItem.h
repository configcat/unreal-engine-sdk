// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>

#include <memory>

#include "ConfigCatRolloutPercentageItem.generated.h"

namespace configcat
{
	struct RolloutPercentageItem;
} // namespace configcat

/**
 * Wrapper class for configcat::RolloutPercentageItem
 */
USTRUCT(BlueprintType)
struct FConfigCatRolloutPercentageItem
{
	GENERATED_BODY()

	FConfigCatRolloutPercentageItem() = default;
	FConfigCatRolloutPercentageItem(const configcat::RolloutPercentageItem& InPercentageItem);

	/**
	 * Internal percentage item we want to expose in blueprints
	 */
	std::shared_ptr<configcat::RolloutPercentageItem> PercentageItem;
};

/**
 * Getters for all the properties of the configcat::RolloutPercentageItem stored inside a FConfigCatRolloutPercentageItem wrapper
 */
UCLASS()
class CONFIGCAT_API UConfigCatPercentageItemAccessorsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/**
	 * Checks if the underlying percentage item is valid
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Percentage")
	static bool IsValid(const FConfigCatRolloutPercentageItem& Struct);
	/**
	 * Gets the value of the percentage item
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Percentage")
	static FConfigCatValue GetPercentageValue(const FConfigCatRolloutPercentageItem& Struct);
	/**
	 * Gets the percentage of the percentage item
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Percentage")
	static double GetPercentagePercentage(const FConfigCatRolloutPercentageItem& Struct);
	/**
	 * Gets the variation identifier of the percentage item
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Percentage")
	static FString GetPercentageVariationId(const FConfigCatRolloutPercentageItem& Struct);
};