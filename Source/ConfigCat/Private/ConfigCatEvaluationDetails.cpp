// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "ConfigCatEvaluationDetails.h"

// clang-format off
//TODO: This should go directly in evaluationdetails.h
#include <chrono>
// clang-format on

#include "ConfigCatCppSDK/Include/evaluationdetails.h"
#include "ConfigCatUser.h"
#include "ConfigCatValue.h"

using namespace configcat;

FConfigCatEvaluationDetails::FConfigCatEvaluationDetails(configcat::EvaluationDetails InValue)
{
	EvaluationDetails = std::make_shared<configcat::EvaluationDetails>(InValue);
}

FString UConfigCatEvaluationDetailsAccessorsBPLibrary::GetKey(const FConfigCatEvaluationDetails& Struct)
{
	if (Struct.EvaluationDetails)
	{
		return UTF8_TO_TCHAR(Struct.EvaluationDetails->key.c_str());
	}

	return TEXT("");
}

FConfigCatValue UConfigCatEvaluationDetailsAccessorsBPLibrary::GetValue(const FConfigCatEvaluationDetails& Struct)
{
	if (Struct.EvaluationDetails)
	{
		return FConfigCatValue(Struct.EvaluationDetails->value);
	}

	return {};
}

FString UConfigCatEvaluationDetailsAccessorsBPLibrary::GetVariationId(const FConfigCatEvaluationDetails& Struct)
{
	if (Struct.EvaluationDetails)
	{
		return UTF8_TO_TCHAR(Struct.EvaluationDetails->variationId.c_str());
	}

	return TEXT("");
}

FDateTime UConfigCatEvaluationDetailsAccessorsBPLibrary::GetFetchTime(const FConfigCatEvaluationDetails& Struct)
{
	if (Struct.EvaluationDetails)
	{
		const auto TimeSinceEpoch = Struct.EvaluationDetails->fetchTime.time_since_epoch();
		const auto MillisecondsSinceEpoch = std::chrono::duration_cast<std::chrono::milliseconds>(TimeSinceEpoch).count();
		return FDateTime(MillisecondsSinceEpoch);
	}

	return {};
}

FConfigCatUser UConfigCatEvaluationDetailsAccessorsBPLibrary::GetUser(const FConfigCatEvaluationDetails& Struct)
{
	if (Struct.EvaluationDetails)
	{
		// TODO: Discuss if we can make everything const? ideally the configcat client should not need the non-const version for SetUser
		return FConfigCatUser(const_cast<ConfigCatUser*>(Struct.EvaluationDetails->user));
	}

	return {};
}

bool UConfigCatEvaluationDetailsAccessorsBPLibrary::IsDefaultValue(const FConfigCatEvaluationDetails& Struct)
{
	if (Struct.EvaluationDetails)
	{
		return Struct.EvaluationDetails->isDefaultValue;
	}

	return false;
}

FString UConfigCatEvaluationDetailsAccessorsBPLibrary::GetError(const FConfigCatEvaluationDetails& Struct)
{
	if (Struct.EvaluationDetails)
	{
		return UTF8_TO_TCHAR(Struct.EvaluationDetails->error.c_str());
	}

	return TEXT("");
}
