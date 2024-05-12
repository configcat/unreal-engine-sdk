// Fill out your copyright notice in the Description page of Project Settings.

#include "Wrapper/ConfigCatEvaluationWrapper.h"

#include "Wrappers/ConfigCatValueWrapper.h"

using namespace configcat;

UConfigCatEvaluationWrapper* UConfigCatEvaluationWrapper::CreateEvaluation(const EvaluationDetailsBase& InEvaluationDetails)
{
	UConfigCatEvaluationWrapper* Result = NewObject<UConfigCatEvaluationWrapper>();
	Result->SetEvaluationDetails(InEvaluationDetails);
	return Result;
}

FString UConfigCatEvaluationWrapper::GetKey() const
{
	if (Details)
	{
		return UTF8_TO_TCHAR(Details->key.c_str());
	}

	return {};
}

UConfigCatValueWrapper* UConfigCatEvaluationWrapper::GetValue() const
{
	if (Details)
	{
		return UConfigCatValueWrapper::CreateValue(Details->value);
	}

	return {};
}

FString UConfigCatEvaluationWrapper::GetVariationId() const
{
	if (Details && Details->variationId.has_value())
	{
		return UTF8_TO_TCHAR(Details->variationId.value().c_str());
	}

	return {};
}

FDateTime UConfigCatEvaluationWrapper::GetFetchTime() const
{
	if (Details)
	{
		const auto TimeSinceEpoch = Details->fetchTime.time_since_epoch().count();
		return FDateTime::FromUnixTimestamp(TimeSinceEpoch);
	}

	return {};
}

UConfigCatUserWrapper* UConfigCatEvaluationWrapper::GetUser() const
{
	if (Details)
	{
		// return FConfigCatUserWrapper(Details->user);
	}

	return {};
}

bool UConfigCatEvaluationWrapper::IsDefaultValue() const
{
	if (Details)
	{
		return Details->isDefaultValue;
	}

	return {};
}

FString UConfigCatEvaluationWrapper::GetError() const
{
	if (Details && Details->errorMessage.has_value())
	{
		return UTF8_TO_TCHAR(Details->errorMessage.value().c_str());
	}

	return {};
}

FString UConfigCatEvaluationWrapper::GetException() const
{
	return {};
}

void UConfigCatEvaluationWrapper::SetEvaluationDetails(const EvaluationDetailsBase& InEvaluationDetails)
{
	Details = std::make_shared<EvaluationDetails<>>(to_concrete(InEvaluationDetails));
}