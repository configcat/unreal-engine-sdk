// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "Wrapper/ConfigCatEvaluationDetails.h"

// clang-format off
//TODO: This should go directly in evaluationdetails.h
#include <chrono>
// clang-format on

#include <ConfigCatCppSDK/Include/evaluationdetails.h>

#include "Wrapper/ConfigCatRolloutPercentageItem.h"
#include "Wrapper/ConfigCatRolloutRule.h"
#include "Wrapper/ConfigCatUser.h"
#include "Wrapper/ConfigCatValue.h"

using namespace configcat;

FConfigCatEvaluationDetails::FConfigCatEvaluationDetails(configcat::EvaluationDetails InDetails)
{
	EvaluationDetails = std::make_shared<configcat::EvaluationDetails>(InDetails);
}

FString FConfigCatEvaluationDetails::GetKey() const
{
	if (EvaluationDetails)
	{
		return UTF8_TO_TCHAR(EvaluationDetails->key.c_str());
	}

	return {};
}

FConfigCatValue FConfigCatEvaluationDetails::GetValue() const
{
	if (EvaluationDetails)
	{
		return FConfigCatValue(EvaluationDetails->value);
	}

	return {};
}

FString FConfigCatEvaluationDetails::GetVariationId() const
{
	if (EvaluationDetails)
	{
		return UTF8_TO_TCHAR(EvaluationDetails->variationId.c_str());
	}

	return {};
}

FDateTime FConfigCatEvaluationDetails::GetFetchTime() const
{
	if (EvaluationDetails)
	{
		// TODO: Find out what the fetch time is measured in so we ensure it properly transforms into FDateTime
		const auto TimeSinceEpoch = EvaluationDetails->fetchTime.time_since_epoch();
		const auto MillisecondsSinceEpoch = std::chrono::duration_cast<std::chrono::milliseconds>(TimeSinceEpoch).count();
		return FDateTime(MillisecondsSinceEpoch);
	}

	return {};
}

FConfigCatUser FConfigCatEvaluationDetails::GetUser() const
{
	if (EvaluationDetails)
	{
		// TODO: Discuss if we can make everything const? ideally the configcat client should not need the non-const version for SetUser
		return FConfigCatUser(const_cast<ConfigCatUser*>(EvaluationDetails->user));
	}

	return {};
}

bool FConfigCatEvaluationDetails::IsDefaultValue() const
{
	if (EvaluationDetails)
	{
		return EvaluationDetails->isDefaultValue;
	}

	return {};
}

FString FConfigCatEvaluationDetails::GetError() const
{
	if (EvaluationDetails)
	{
		return UTF8_TO_TCHAR(EvaluationDetails->error.c_str());
	}

	return {};
}

FConfigCatRolloutRule FConfigCatEvaluationDetails::GetRolloutRule() const
{
	if (EvaluationDetails && EvaluationDetails->matchedEvaluationRule.has_value())
	{
		return EvaluationDetails->matchedEvaluationRule.value();
	}

	return {};
}

FConfigCatRolloutPercentageItem FConfigCatEvaluationDetails::GetRolloutPercentageItem() const
{
	if (EvaluationDetails && EvaluationDetails->matchedEvaluationPercentageRule.has_value())
	{
		return EvaluationDetails->matchedEvaluationPercentageRule.value();
	}

	return {};
}

FString UConfigCatEvaluationDetailsAccessorsBPLibrary::GetKey(const FConfigCatEvaluationDetails& Struct)
{
	return Struct.GetKey();
}

FConfigCatValue UConfigCatEvaluationDetailsAccessorsBPLibrary::GetValue(const FConfigCatEvaluationDetails& Struct)
{
	return Struct.GetValue();
}

FString UConfigCatEvaluationDetailsAccessorsBPLibrary::GetVariationId(const FConfigCatEvaluationDetails& Struct)
{
	return Struct.GetVariationId();
}

FDateTime UConfigCatEvaluationDetailsAccessorsBPLibrary::GetFetchTime(const FConfigCatEvaluationDetails& Struct)
{
	return Struct.GetFetchTime();
}

FConfigCatUser UConfigCatEvaluationDetailsAccessorsBPLibrary::GetUser(const FConfigCatEvaluationDetails& Struct)
{
	return Struct.GetUser();
}

bool UConfigCatEvaluationDetailsAccessorsBPLibrary::IsDefaultValue(const FConfigCatEvaluationDetails& Struct)
{
	return Struct.IsDefaultValue();
}

FString UConfigCatEvaluationDetailsAccessorsBPLibrary::GetError(const FConfigCatEvaluationDetails& Struct)
{
	return Struct.GetError();
}

FConfigCatRolloutRule UConfigCatEvaluationDetailsAccessorsBPLibrary::GetRolloutRule(const FConfigCatEvaluationDetails& Struct)
{
	return Struct.GetRolloutRule();
}

FConfigCatRolloutPercentageItem UConfigCatEvaluationDetailsAccessorsBPLibrary::GetRolloutPercentageItem(const FConfigCatEvaluationDetails& Struct)
{
	return Struct.GetRolloutPercentageItem();
}
