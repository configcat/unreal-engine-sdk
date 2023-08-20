// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

// clang-format off
//TODO: This should go directly in evaluationdetails.h
#include <chrono>
// clang-format on

#include <ConfigCatCppSDK/Include/evaluationdetails.h>

#include "ConfigCatUser.h"
#include "ConfigCatValue.h"

#include "ConfigCatEvaluationDetails.generated.h"

USTRUCT()
struct FConfigCatRolloutPercentageItem
{
	GENERATED_BODY()

	FConfigCatRolloutPercentageItem() = default;
	FConfigCatRolloutPercentageItem(const configcat::RolloutPercentageItem& InValue);
};

USTRUCT()
struct FConfigCatRolloutRule
{
	GENERATED_BODY()

	FConfigCatRolloutRule() = default;
	FConfigCatRolloutRule(const configcat::RolloutRule& InValue);
};

USTRUCT(BlueprintType)
struct FConfigCatEvaluationDetails
{
	GENERATED_BODY()

	FConfigCatEvaluationDetails() = default;
	FConfigCatEvaluationDetails(const configcat::EvaluationDetails& InValue);

	FString Key;
	FConfigCatValue Value;
	FString VariationId;
	FDateTime FetchTime;
	FConfigCatUser User;
	bool bIsDefaultValue;
	FString Error;
	FConfigCatRolloutRule MatchedEvaluationRule;
	FConfigCatRolloutPercentageItem MatchedEvaluationPercentageRule;
};
