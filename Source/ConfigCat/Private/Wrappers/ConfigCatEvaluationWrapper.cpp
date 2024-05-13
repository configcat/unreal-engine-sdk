// Fill out your copyright notice in the Description page of Project Settings.

#include "Wrappers/ConfigCatEvaluationWrapper.h"

#include "ConfigCatCppSDK/Include/log.h"
#include "Wrappers/ConfigCatPercentageOptionWrapper.h"
#include "Wrapper/ConfigCatTargetingRuleWrapper.h"
#include "Wrappers/ConfigCatUserWrapper.h"
#include "Wrappers/ConfigCatValueWrapper.h"

UConfigCatEvaluationWrapper* UConfigCatEvaluationWrapper::CreateEvaluation(const configcat::EvaluationDetailsBase& InEvaluationDetails)
{
	UConfigCatEvaluationWrapper* Result = NewObject<UConfigCatEvaluationWrapper>();
	Result->EvaluationDetails = std::make_shared<configcat::EvaluationDetails<>>(to_concrete(InEvaluationDetails));
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
		return UConfigCatValueWrapper::CreateValue(EvaluationDetails->value);
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
	if (EvaluationDetails && EvaluationDetails->user)
	{
		return UConfigCatUserWrapper::CreateUser(EvaluationDetails->user);
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

FString UConfigCatEvaluationWrapper::GetException() const
{
	if(EvaluationDetails && EvaluationDetails->errorException)
	{
		return UTF8_TO_TCHAR(unwrap_exception_message(EvaluationDetails->errorException).c_str());
	}
	return {};
}

UConfigCatTargetingRuleWrapper* UConfigCatEvaluationWrapper::GetMatchedTargetingRule() const
{
	if(EvaluationDetails && EvaluationDetails->matchedTargetingRule)
	{
		return UConfigCatTargetingRuleWrapper::CreateTargetingRule(EvaluationDetails->matchedTargetingRule.value());
	}

	return {};
}

UConfigCatPercentageOptionWrapper* UConfigCatEvaluationWrapper::GetMatchedPercentageOption() const
{
	if(EvaluationDetails && EvaluationDetails->matchedPercentageOption)
	{
		return UConfigCatPercentageOptionWrapper::CreatePercentageOption(EvaluationDetails->matchedPercentageOption.value());
	}

	return {};
}
