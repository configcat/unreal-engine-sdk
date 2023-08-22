// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>

#include <memory>

#include "ConfigCatRolloutRule.generated.h"

namespace configcat
{
	struct RolloutRule;
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
 * Getters for all the properties of the configcat::RolloutRule stored inside a FConfigCatRolloutRule wrapper
 */
UCLASS()
class CONFIGCAT_API UConfigCatRuleAccessorsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/**
	 * Checks if the underlying rule is valid
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Rule")
	static bool IsValid(const FConfigCatRolloutRule& Struct);
	/**
	 * Gets the value of the rollout rule
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Rule")
	static FConfigCatValue GetRuleValue(const FConfigCatRolloutRule& Struct);
	/**
	 * Gets the comparison attribute of the rollout rule
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Rule")
	static FString GetRuleComparisonAttribute(const FConfigCatRolloutRule& Struct);
	/**
	 * Gets the comparator of the rollout rule
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Rule")
	static FString GetRuleComparator(const FConfigCatRolloutRule& Struct);
	/**
	 * Gets the comparison value of the rollout rule
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Rule")
	static FString GetRuleComparisonValue(const FConfigCatRolloutRule& Struct);
	/**
	 * Gets the variation identifier of the rollout rule
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Rule")
	static FString GetRuleVariationId(const FConfigCatRolloutRule& Struct);
};
