// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "ConfigCatEvaluationDetails.h"

FConfigCatRolloutPercentageItem::FConfigCatRolloutPercentageItem(const configcat::RolloutPercentageItem& InValue)
{
}

FConfigCatRolloutRule::FConfigCatRolloutRule(const configcat::RolloutRule& InValue)
{
}

FConfigCatEvaluationDetails::FConfigCatEvaluationDetails(const configcat::EvaluationDetails& InValue)
{
	Key = UTF8_TO_TCHAR(InValue.key.c_str());
	Value = FConfigCatValue(InValue.value);
	VariationId = UTF8_TO_TCHAR(InValue.variationId.c_str());

	const auto MillisecondsSinceEpoch = std::chrono::duration_cast<std::chrono::milliseconds>(InValue.fetchTime.time_since_epoch()).count();
	FetchTime = FDateTime(MillisecondsSinceEpoch);

	User = FConfigCatUser(InValue.user);
	bIsDefaultValue = InValue.isDefaultValue;
	Error = UTF8_TO_TCHAR(InValue.error.c_str());
	MatchedEvaluationRule = InValue.matchedEvaluationRule ? FConfigCatRolloutRule(InValue.matchedEvaluationRule.value()) : FConfigCatRolloutRule();
	MatchedEvaluationPercentageRule = InValue.matchedEvaluationPercentageRule ? FConfigCatRolloutPercentageItem(InValue.matchedEvaluationPercentageRule.value()) : FConfigCatRolloutPercentageItem();
}