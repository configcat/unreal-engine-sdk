// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "Wrapper/ConfigCatTargetingRuleWrapper.h"

#include "Wrappers/ConfigCatValueWrapper.h"


FString UConfigCatUserConditionWrapper::GetComparisonAttribute() const
{
	return UTF8_TO_TCHAR(UserCondition.comparisonAttribute.c_str());
}

EConfigCatUserComparator UConfigCatUserConditionWrapper::GetComparator() const
{
	return static_cast<EConfigCatUserComparator>(UserCondition.comparator);
}

FString UConfigCatUserConditionWrapper::GetStringComparisonValue() const
{
	// UserCondition.comparisonValue;
	return {};
}

double UConfigCatUserConditionWrapper::GetNumberComparisonValue() const
{
	// UserCondition.comparisonValue;
	return {};
}

TArray<FString> UConfigCatUserConditionWrapper::GetStringArrayComparisonValue() const
{
	// UserCondition.comparisonValue;
	return {};
}

FString UConfigCatPrerequisiteFlagConditionWrapper::GetPrerequisiteFlagKey() const
{
	return UTF8_TO_TCHAR(PrerequisiteFlagCondition.prerequisiteFlagKey.c_str());
}

EConfigCatPrerequisiteFlagComparator UConfigCatPrerequisiteFlagConditionWrapper::GetComparator() const
{
	return static_cast<EConfigCatPrerequisiteFlagComparator>(PrerequisiteFlagCondition.comparator);
}

UConfigCatValueWrapper* UConfigCatPrerequisiteFlagConditionWrapper::GetComparisonValue() const
{
	return UConfigCatValueWrapper::CreateValue(PrerequisiteFlagCondition.comparisonValue);
}

int32 UConfigCatSegmentConditionWrapper::GetSegmentIndex() const
{
	return SegmentCondition.segmentIndex;
}

EConfigCatSegmentComparator UConfigCatSegmentConditionWrapper::GetComparator() const
{
	return static_cast<EConfigCatSegmentComparator>(SegmentCondition.comparator);
}

UConfigCatTargetingRuleWrapper* UConfigCatTargetingRuleWrapper::CreateTargetingRule(const configcat::TargetingRule& InTargetingRule)
{
	UConfigCatTargetingRuleWrapper* Result = NewObject<UConfigCatTargetingRuleWrapper>();
	Result->TargetingRule = InTargetingRule;
	return Result;
}
