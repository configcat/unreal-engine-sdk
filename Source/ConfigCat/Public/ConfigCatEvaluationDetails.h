// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include <memory>

#include "ConfigCatEvaluationDetails.generated.h"


struct FConfigCatUser;
struct FConfigCatValue;
namespace configcat
{
	struct EvaluationDetails;
}

USTRUCT(BlueprintType)
struct FConfigCatEvaluationDetails
{
	GENERATED_BODY()

	FConfigCatEvaluationDetails() = default;
	FConfigCatEvaluationDetails(configcat::EvaluationDetails InValue);

	std::shared_ptr<configcat::EvaluationDetails> EvaluationDetails;
};


UCLASS()
class UConfigCatEvaluationDetailsAccessorsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails")
	static FString GetKey(const FConfigCatEvaluationDetails& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails")
	static FConfigCatValue GetValue(const FConfigCatEvaluationDetails& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails")
	static FString GetVariationId(const FConfigCatEvaluationDetails& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails")
	static FDateTime GetFetchTime(const FConfigCatEvaluationDetails& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails")
	static FConfigCatUser GetUser(const FConfigCatEvaluationDetails& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails")
	static bool IsDefaultValue(const FConfigCatEvaluationDetails& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails")
	static FString GetError(const FConfigCatEvaluationDetails& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails|Rule")
	static bool HasRolloutRule(const FConfigCatEvaluationDetails& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails|Rule")
	static FConfigCatValue GetRuleValue(const FConfigCatEvaluationDetails& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails|Rule")
	static FString GetRuleComparisonAttribute(const FConfigCatEvaluationDetails& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails|Rule")
	static FString GetRuleComparator(const FConfigCatEvaluationDetails& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails|Rule")
	static FString GetRuleComparisonValue(const FConfigCatEvaluationDetails& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails|Rule")
	static FString GetRuleVariationId(const FConfigCatEvaluationDetails& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails|Percentage")
	static bool HasPercentageItem(const FConfigCatEvaluationDetails& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails|Percentage")
	static FConfigCatValue GetPercentageValue(const FConfigCatEvaluationDetails& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails|Percentage")
	static double GetPercentagePercentage(const FConfigCatEvaluationDetails& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|EvaluationDetails|Percentage")
	static FString GetPercentageVariationId(const FConfigCatEvaluationDetails& Struct);
};
