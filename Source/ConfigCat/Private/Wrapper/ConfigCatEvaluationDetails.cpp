// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "Wrapper/ConfigCatEvaluationDetails.h"

#include <ConfigCatCppSDK/Include/evaluationdetails.h>

#include "Wrapper/ConfigCatValue.h"
#include "Wrapper/ConfigCatUserWrapper.h"

using namespace configcat;

FConfigCatEvaluationDetails::FConfigCatEvaluationDetails(const configcat::EvaluationDetailsBase& InDetails)
{
	//EvaluationDetails = std::make_shared<configcat::EvaluationDetails>(InDetails);
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
		return FConfigCatValue(EvaluationDetails->value());
	}

	return {};
}

FString FConfigCatEvaluationDetails::GetVariationId() const
{
	if (EvaluationDetails && EvaluationDetails->variationId.has_value())
	{
		return UTF8_TO_TCHAR(EvaluationDetails->variationId.value().c_str());
	}

	return {};
}

FDateTime FConfigCatEvaluationDetails::GetFetchTime() const
{
	if (EvaluationDetails)
	{
		const auto TimeSinceEpoch = EvaluationDetails->fetchTime.time_since_epoch().count();
		return FDateTime::FromUnixTimestamp(TimeSinceEpoch);
	}

	return {};
}

FConfigCatUserWrapper FConfigCatEvaluationDetails::GetUser() const
{
	if (EvaluationDetails)
	{
		return FConfigCatUserWrapper(EvaluationDetails->user);
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
	if (EvaluationDetails && EvaluationDetails->errorMessage.has_value())
	{
		return UTF8_TO_TCHAR(EvaluationDetails->errorMessage.value().c_str());
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

FConfigCatUserWrapper UConfigCatEvaluationDetailsAccessorsBPLibrary::GetUser(const FConfigCatEvaluationDetails& Struct)
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
