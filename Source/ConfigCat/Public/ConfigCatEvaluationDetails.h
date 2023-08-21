// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>

#include <memory>

#include "ConfigCatEvaluationDetails.generated.h"

struct FConfigCatUser;
struct FConfigCatValue;
namespace configcat
{
	struct EvaluationDetails;
}

/**
 * Wrapper class for configcat::EvaluationDetails
 */
USTRUCT(BlueprintType)
struct CONFIGCAT_API FConfigCatEvaluationDetails
{
	GENERATED_BODY()

	FConfigCatEvaluationDetails() = default;
	FConfigCatEvaluationDetails(configcat::EvaluationDetails InValue);
	/**
	 * Internal evaluation details we want to expose in blueprints
	 */
	std::shared_ptr<configcat::EvaluationDetails> EvaluationDetails;
};


/**
 * Getters for all the properties of the configcat::EvaluationDetails stored inside a FConfigCatEvaluationDetails wrapper
 */
UCLASS()
class CONFIGCAT_API UConfigCatEvaluationDetailsAccessorsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/**
	 * Gets the identifier Key of the evaluated feature flag
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	static FString GetKey(const FConfigCatEvaluationDetails& Struct);
	/**
	 * Gets the value of the evaluated feature flag
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	static FConfigCatValue GetValue(const FConfigCatEvaluationDetails& Struct);
	/**
	 * Gets the variation identifier of the evaluated feature flag
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	static FString GetVariationId(const FConfigCatEvaluationDetails& Struct);
	/**
	 * Gets the timestamp of the last fetch at the time of evaluation
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	static FDateTime GetFetchTime(const FConfigCatEvaluationDetails& Struct);
	/**
	 * Gets the user the evaluation was performed against
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	static FConfigCatUser GetUser(const FConfigCatEvaluationDetails& Struct);
	/**
	 * Gets if the value returned is the default value of the feature flag
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	static bool IsDefaultValue(const FConfigCatEvaluationDetails& Struct);
	/**
	 * Gets the error associated with the evaluation (if any)
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	static FString GetError(const FConfigCatEvaluationDetails& Struct);
	/**
	 * Gets the rollout rule that determined the resulting value (if any)
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Rule")
	static bool HasRolloutRule(const FConfigCatEvaluationDetails& Struct);
	/**
	 * Gets the value of the rollout rule that attributed the resulting value (if any)
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Rule")
	static FConfigCatValue GetRuleValue(const FConfigCatEvaluationDetails& Struct);
	/**
	 * Gets the comparison attribute of the rollout rule that determined the resulting value (if any)
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Rule")
	static FString GetRuleComparisonAttribute(const FConfigCatEvaluationDetails& Struct);
	/**
	 * Gets the comparator of the rollout rule that determined the resulting value (if any)
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Rule")
	static FString GetRuleComparator(const FConfigCatEvaluationDetails& Struct);
	/**
	 * Gets the comparison value of the rollout rule that determined the resulting value (if any)
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Rule")
	static FString GetRuleComparisonValue(const FConfigCatEvaluationDetails& Struct);
	/**
	 * Gets the variation identifier of the rollout rule that determined the resulting value (if any)
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Rule")
	static FString GetRuleVariationId(const FConfigCatEvaluationDetails& Struct);
	/**
	 * Gets the percentage item that determined the resulting value (if any)
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Percentage")
	static bool HasPercentageItem(const FConfigCatEvaluationDetails& Struct);
	/**
	 * Gets the value of the percentage item that determined the resulting value (if any)
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Percentage")
	static FConfigCatValue GetPercentageValue(const FConfigCatEvaluationDetails& Struct);
	/**
	 * Gets the percentage of the percentage item that determined the resulting value (if any)
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Percentage")
	static double GetPercentagePercentage(const FConfigCatEvaluationDetails& Struct);
	/**
	 * Gets the variation identifier of the percentage item that determined the resulting value (if any)
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails|Percentage")
	static FString GetPercentageVariationId(const FConfigCatEvaluationDetails& Struct);
};
