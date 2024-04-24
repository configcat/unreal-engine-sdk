// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>

#include <memory>

#include "ConfigCatEvaluationDetails.generated.h"

struct FConfigCatUser;
struct FConfigCatValue;

namespace configcat 
{
	struct EvaluationDetailsBase;
}

/**
 * Wrapper class for configcat::EvaluationDetails
 */
USTRUCT(BlueprintType)
struct CONFIGCAT_API FConfigCatEvaluationDetails
{
	GENERATED_BODY()

	FConfigCatEvaluationDetails() = default;
	FConfigCatEvaluationDetails(const configcat::EvaluationDetailsBase& InDetails);

	FString GetKey() const;
	FConfigCatValue GetValue() const;
	FString GetVariationId() const;
	FDateTime GetFetchTime() const;
	FConfigCatUserWrapper GetUser() const;
	bool IsDefaultValue() const;
	FString GetError() const;

	/**
	 * Internal evaluation details we want to expose in blueprints
	 */
	std::shared_ptr<configcat::EvaluationDetailsBase> EvaluationDetails;
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
	static FConfigCatUserWrapper GetUser(const FConfigCatEvaluationDetails& Struct);
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
};
