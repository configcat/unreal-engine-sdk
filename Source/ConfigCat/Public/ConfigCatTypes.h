// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>

#include <memory>

#include "ConfigCatTypes.generated.h"

namespace configcat
{
	struct RolloutRule;
	struct RolloutPercentageItem;
} // namespace configcat

/**
 * Wrapper class for configcat::RolloutRule
 */
USTRUCT(BlueprintType)
struct FConfigCatRolloutRule
{
	GENERATED_BODY()

	FConfigCatRolloutRule() = default;
	FConfigCatRolloutRule(const configcat::RolloutRule& InRule);

	/**
	 * Internal rule we want to expose in blueprints
	 */
	std::shared_ptr<configcat::RolloutRule> Rule;
};

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
 * Getters for all the properties of the configcat::RolloutRule stored inside a FConfigCatRolloutRule wrapper
 */
UCLASS()
class CONFIGCAT_API UConfigCatRuleAccessorsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/**
	 * Checks if the underlying rule is valid
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Rule")
	static bool IsValid(const FConfigCatRolloutRule& Struct);
	/**
	 * Gets the value of the rollout rule
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Rule")
	static FConfigCatValue GetRuleValue(const FConfigCatRolloutRule& Struct);
	/**
	 * Gets the comparison attribute of the rollout rule
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Rule")
	static FString GetRuleComparisonAttribute(const FConfigCatRolloutRule& Struct);
	/**
	 * Gets the comparator of the rollout rule
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Rule")
	static FString GetRuleComparator(const FConfigCatRolloutRule& Struct);
	/**
	 * Gets the comparison value of the rollout rule
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Rule")
	static FString GetRuleComparisonValue(const FConfigCatRolloutRule& Struct);
	/**
	 * Gets the variation identifier of the rollout rule
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Rule")
	static FString GetRuleVariationId(const FConfigCatRolloutRule& Struct);
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
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Percentage")
	static bool IsValid(const FConfigCatRolloutPercentageItem& Struct);
	/**
	 * Gets the value of the percentage item
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Percentage")
	static FConfigCatValue GetPercentageValue(const FConfigCatRolloutPercentageItem& Struct);
	/**
	 * Gets the percentage of the percentage item
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Percentage")
	static double GetPercentagePercentage(const FConfigCatRolloutPercentageItem& Struct);
	/**
	 * Gets the variation identifier of the percentage item
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Percentage")
	static FString GetPercentageVariationId(const FConfigCatRolloutPercentageItem& Struct);
};