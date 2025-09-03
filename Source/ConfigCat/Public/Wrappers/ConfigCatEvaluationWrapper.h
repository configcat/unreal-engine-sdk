// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ThirdParty/ConfigCatCppSDK/Include/evaluationdetails.h>

#include "Misc/DateTime.h"
#include <memory>

#include "ConfigCatEvaluationWrapper.generated.h"

class UConfigCatPercentageOptionWrapper;
class UConfigCatTargetingRuleWrapper;
class UConfigCatUserWrapper;
class UConfigCatValueWrapper;

UCLASS(meta = (DisplayName = "ConfigCat Evaluation"))
class CONFIGCAT_API UConfigCatEvaluationWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatEvaluationWrapper* CreateEvaluation(const configcat::EvaluationDetailsBase& InEvaluationDetails);

	UFUNCTION(BlueprintPure, Category = "EvaluationDetails", meta = (Keywords = "ConfigCat"))
	FString GetKey() const;
	UFUNCTION(BlueprintPure, Category = "EvaluationDetails", meta = (Keywords = "ConfigCat"))
	FString GetVariationId() const;
	UFUNCTION(BlueprintPure, Category = "EvaluationDetails", meta = (Keywords = "ConfigCat"))
	FDateTime GetFetchTime() const;
	UFUNCTION(BlueprintPure, Category = "EvaluationDetails", meta = (Keywords = "ConfigCat"))
	UConfigCatUserWrapper* GetUser() const;
	UFUNCTION(BlueprintPure, Category = "EvaluationDetails", meta = (Keywords = "ConfigCat"))
	bool IsDefaultValue() const;
	UFUNCTION(BlueprintPure, Category = "EvaluationDetails", meta = (Keywords = "ConfigCat"))
	FString GetError() const;
	UFUNCTION(BlueprintPure, Category = "EvaluationDetails", meta = (Keywords = "ConfigCat"))
	FString GetException() const;
	UFUNCTION(BlueprintPure, Category = "EvaluationDetails", meta = (Keywords = "ConfigCat"))
	UConfigCatTargetingRuleWrapper* GetMatchedTargetingRule() const;
	UFUNCTION(BlueprintPure, Category = "EvaluationDetails", meta = (Keywords = "ConfigCat"))
	UConfigCatPercentageOptionWrapper* GetMatchedPercentageOption() const;
	UFUNCTION(BlueprintPure, Category = "EvaluationDetails", meta = (Keywords = "ConfigCat"))
	UConfigCatValueWrapper* GetValue() const;

	std::shared_ptr<configcat::EvaluationDetails<>> EvaluationDetails;
};