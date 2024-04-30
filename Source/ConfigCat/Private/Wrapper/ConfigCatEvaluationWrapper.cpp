// Fill out your copyright notice in the Description page of Project Settings.


#include "Wrapper/ConfigCatEvaluationWrapper.h"

#include "Wrapper/ConfigCatValueWrapper.h"

UConfigCatEvaluationWrapper* UConfigCatEvaluationWrapper::CreateEvaluation(const configcat::EvaluationDetailsBase& EvaluationDetails)
{
	UConfigCatEvaluationWrapper* Result = NewObject<UConfigCatEvaluationWrapper>();
	// Result->SetValue(InValue);
	return Result;
}

FString UConfigCatEvaluationWrapper::GetKey() const
{
	if (EvaluationDetails)
	{
		return UTF8_TO_TCHAR(EvaluationDetails->key.c_str());
	}

	return {};
}

UConfigCatValueWrapper* UConfigCatEvaluationWrapper::GetValue() const
{
	if (EvaluationDetails)
	{
		return UConfigCatValueWrapper::CreateValue(EvaluationDetails->value());
	}

	return {};
}

FString UConfigCatEvaluationWrapper::GetVariationId() const
{
	if (EvaluationDetails && EvaluationDetails->variationId.has_value())
	{
		return UTF8_TO_TCHAR(EvaluationDetails->variationId.value().c_str());
	}

	return {};
}

FDateTime UConfigCatEvaluationWrapper::GetFetchTime() const
{
	if (EvaluationDetails)
	{
		const auto TimeSinceEpoch = EvaluationDetails->fetchTime.time_since_epoch().count();
		return FDateTime::FromUnixTimestamp(TimeSinceEpoch);
	}

	return {};
}

UConfigCatUserWrapper* UConfigCatEvaluationWrapper::GetUser() const
{
	if (EvaluationDetails)
	{
		// return FConfigCatUserWrapper(EvaluationDetails->user);
	}

	return {};
}

bool UConfigCatEvaluationWrapper::IsDefaultValue() const
{
	if (EvaluationDetails)
	{
		return EvaluationDetails->isDefaultValue;
	}

	return {};
}

FString UConfigCatEvaluationWrapper::GetError() const
{
	if (EvaluationDetails && EvaluationDetails->errorMessage.has_value())
	{
		return UTF8_TO_TCHAR(EvaluationDetails->errorMessage.value().c_str());
	}

	return {};
}