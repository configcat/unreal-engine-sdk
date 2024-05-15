// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ConfigCatCppSDK/Include/evaluationdetails.h>

#include "Misc/DateTime.h"
#include <memory>

#include "ConfigCatEvaluationWrapper.generated.h"

class UConfigCatPercentageOptionWrapper;
class UConfigCatTargetingRuleWrapper;
class UConfigCatUserWrapper;
class UConfigCatValueWrapper;

UCLASS(DisplayName="Config Cat Evaluation", Hidden)
class CONFIGCATWRAPPERS_API UConfigCatEvaluationWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatEvaluationWrapper* CreateEvaluation(const configcat::EvaluationDetailsBase& InEvaluationDetails);

	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	FString GetKey() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	FString GetVariationId() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	FDateTime GetFetchTime() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	UConfigCatUserWrapper* GetUser() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	bool IsDefaultValue() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	FString GetError() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	FString GetException() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	UConfigCatTargetingRuleWrapper* GetMatchedTargetingRule() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	UConfigCatPercentageOptionWrapper* GetMatchedPercentageOption() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	UConfigCatValueWrapper* GetValue() const;

	std::shared_ptr<configcat::EvaluationDetails<>> EvaluationDetails;
};