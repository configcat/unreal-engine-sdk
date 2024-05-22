// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "ConfigCatTargetingRuleWrapper.h"

#include "ConfigCatSettingValueContainerWrapper.h"
#include "ConfigCatPercentageOptionWrapper.h"
#include "ConfigCatValueWrapper.h"

UConfigCatUserConditionWrapper* UConfigCatUserConditionWrapper::CreateUserCondition(const configcat::UserCondition& InUserCondition)
{
	UConfigCatUserConditionWrapper* Result = NewObject<UConfigCatUserConditionWrapper>();
	Result->UserCondition = InUserCondition;
	return Result;
}

FString UConfigCatUserConditionWrapper::GetComparisonAttribute() const
{
	return UTF8_TO_TCHAR(UserCondition.comparisonAttribute.c_str());
}

EConfigCatUserComparator UConfigCatUserConditionWrapper::GetComparator() const
{
	if (static_cast<int32>(UserCondition.comparator) < 0)
	{
		return EConfigCatUserComparator::Invalid;
	}

	return static_cast<EConfigCatUserComparator>(UserCondition.comparator);
}

bool UConfigCatUserConditionWrapper::HasAnyComparisonValue()
{
	return HasStringComparisonValue() || HasNumberComparisonValue() || HasStringArrayComparisonValue();
}

bool UConfigCatUserConditionWrapper::HasStringComparisonValue() const
{
	return std::holds_alternative<std::string>(UserCondition.comparisonValue);
}

bool UConfigCatUserConditionWrapper::HasNumberComparisonValue() const
{
	return std::holds_alternative<double>(UserCondition.comparisonValue);
}

bool UConfigCatUserConditionWrapper::HasStringArrayComparisonValue() const
{
	return std::holds_alternative<std::vector<std::string>>(UserCondition.comparisonValue);
}

FString UConfigCatUserConditionWrapper::GetStringComparisonValue() const
{
	if (HasStringComparisonValue())
	{
		return UTF8_TO_TCHAR(std::get<std::string>(UserCondition.comparisonValue).c_str());
	}

	return {};
}

double UConfigCatUserConditionWrapper::GetNumberComparisonValue() const
{
	if (HasNumberComparisonValue())
	{
		return std::get<double>(UserCondition.comparisonValue);
	}

	return {};
}

TArray<FString> UConfigCatUserConditionWrapper::GetStringArrayComparisonValue() const
{
	if (HasStringArrayComparisonValue())
	{
		TArray<FString> Result;
		const std::vector<std::string> ArrayAttribute = std::get<std::vector<std::string>>(UserCondition.comparisonValue);
		for (const std::string& ArrayIt : ArrayAttribute)
		{
			Result.Emplace(UTF8_TO_TCHAR(ArrayIt.c_str()));
		}
		return Result;
	}

	return {};
}

UConfigCatPrerequisiteFlagConditionWrapper* UConfigCatPrerequisiteFlagConditionWrapper::CreatePrerequisiteFlagCondition(const configcat::PrerequisiteFlagCondition& InPrerequisiteFlagCondition)
{
	UConfigCatPrerequisiteFlagConditionWrapper* Result = NewObject<UConfigCatPrerequisiteFlagConditionWrapper>();
	Result->PrerequisiteFlagCondition = InPrerequisiteFlagCondition;
	return Result;
}

FString UConfigCatPrerequisiteFlagConditionWrapper::GetPrerequisiteFlagKey() const
{
	return UTF8_TO_TCHAR(PrerequisiteFlagCondition.prerequisiteFlagKey.c_str());
}

EConfigCatPrerequisiteFlagComparator UConfigCatPrerequisiteFlagConditionWrapper::GetComparator() const
{
	if (static_cast<int32>(PrerequisiteFlagCondition.comparator) < 0)
	{
		return EConfigCatPrerequisiteFlagComparator::Invalid;
	}

	return static_cast<EConfigCatPrerequisiteFlagComparator>(PrerequisiteFlagCondition.comparator);
}

UConfigCatValueWrapper* UConfigCatPrerequisiteFlagConditionWrapper::GetComparisonValue() const
{
	return UConfigCatValueWrapper::CreateValue(PrerequisiteFlagCondition.comparisonValue);
}

UConfigCatSegmentConditionWrapper* UConfigCatSegmentConditionWrapper::CreateSegmentCondition(const configcat::SegmentCondition& InSegmentCondition)
{
	UConfigCatSegmentConditionWrapper* Result = NewObject<UConfigCatSegmentConditionWrapper>();
	Result->SegmentCondition = InSegmentCondition;
	return Result;
}

int32 UConfigCatSegmentConditionWrapper::GetSegmentIndex() const
{
	return SegmentCondition.segmentIndex;
}

EConfigCatSegmentComparator UConfigCatSegmentConditionWrapper::GetComparator() const
{
	if (static_cast<int32>(SegmentCondition.comparator) < 0)
	{
		return EConfigCatSegmentComparator::Invalid;
	}

	return static_cast<EConfigCatSegmentComparator>(SegmentCondition.comparator);
}

UConfigCatTargetingRuleWrapper* UConfigCatTargetingRuleWrapper::CreateTargetingRule(const configcat::TargetingRule& InTargetingRule)
{
	UConfigCatTargetingRuleWrapper* Result = NewObject<UConfigCatTargetingRuleWrapper>();
	Result->TargetingRule = InTargetingRule;
	return Result;
}

TArray<FConfigCatConditionContainer> UConfigCatTargetingRuleWrapper::GetConditions() const
{
	TArray<FConfigCatConditionContainer> Result;

	for (const configcat::ConditionContainer& ConditionContainer : TargetingRule.conditions)
	{
		FConfigCatConditionContainer NewCondition;
		const auto& Condition = ConditionContainer.condition;
		if (std::holds_alternative<configcat::UserCondition>(Condition))
		{
			const configcat::UserCondition& UserCondition = std::get<configcat::UserCondition>(Condition);
			NewCondition.UserCondition = nullptr;
			Result.Add(NewCondition);
		}
		else if (std::holds_alternative<configcat::PrerequisiteFlagCondition>(Condition))
		{
			const configcat::PrerequisiteFlagCondition& PrerequisiteFlagCondition = std::get<configcat::PrerequisiteFlagCondition>(Condition);
			NewCondition.PrerequisiteFlagCondition = nullptr;
			Result.Add(NewCondition);
		}
		else if (std::holds_alternative<configcat::SegmentCondition>(Condition))
		{
			const configcat::SegmentCondition& SegmentCondition = std::get<configcat::SegmentCondition>(Condition);
			NewCondition.SegmentCondition = nullptr;
			Result.Add(NewCondition);
		}
	}

	return Result;
}

FConfigCatThenContainer UConfigCatTargetingRuleWrapper::GetThen() const
{
	FConfigCatThenContainer Result;
	if (std::holds_alternative<configcat::SettingValueContainer>(TargetingRule.then))
	{
		const configcat::SettingValueContainer& SettingValueContainer = std::get<configcat::SettingValueContainer>(TargetingRule.then);
		Result.SettingValueContainer = UConfigCatSettingValueContainerWrapper::CreateSettingValue(SettingValueContainer);
	}
	else if (std::holds_alternative<configcat::PercentageOptions>(TargetingRule.then))
	{
		const auto& PercentageOptions = std::get<configcat::PercentageOptions>(TargetingRule.then);
		for (const auto& PercentageOption : PercentageOptions)
		{
			Result.PercentageOptions.Add(UConfigCatPercentageOptionWrapper::CreatePercentageOption(PercentageOption));
		}
	}

	return Result;
}