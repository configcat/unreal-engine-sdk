// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include "ConfigCatCppSDK/Include/config.h"

#include "ConfigCatTargetingRuleWrapper.generated.h"

class UConfigCatPercentageOptionWrapper;
class UConfigCatValueWrapper;

enum class EConfigCatUserComparator
{
	Invalid = -1,
	TextIsOneOf = 0,
	TextIsNotOneOf = 1,
	TextContainsAnyOf = 2,
	TextNotContainsAnyOf = 3,
	SemVerIsOneOf = 4,
	SemVerIsNotOneOf = 5,
	SemVerLess = 6,
	SemVerLessOrEquals = 7,
	SemVerGreater = 8,
	SemVerGreaterOrEquals = 9,
	NumberEquals = 10,
	NumberNotEquals = 11,
	NumberLess = 12,
	NumberLessOrEquals = 13,
	NumberGreater = 14,
	NumberGreaterOrEquals = 15,
	SensitiveTextIsOneOf = 16,
	SensitiveTextIsNotOneOf = 17,
	DateTimeBefore = 18,
	DateTimeAfter = 19,
	SensitiveTextEquals = 20,
	SensitiveTextNotEquals = 21,
	SensitiveTextStartsWithAnyOf = 22,
	SensitiveTextNotStartsWithAnyOf = 23,
	SensitiveTextEndsWithAnyOf = 24,
	SensitiveTextNotEndsWithAnyOf = 25,
	SensitiveArrayContainsAnyOf = 26,
	SensitiveArrayNotContainsAnyOf = 27,
	TextEquals = 28,
	TextNotEquals = 29,
	TextStartsWithAnyOf = 30,
	TextNotStartsWithAnyOf = 31,
	TextEndsWithAnyOf = 32,
	TextNotEndsWithAnyOf = 33,
	ArrayContainsAnyOf = 34,
	ArrayNotContainsAnyOf = 35,
};

class UConfigCatUserConditionWrapper : public UObject
{
	FString GetComparisonAttribute() const;
	EConfigCatUserComparator GetComparator() const;

	FString GetStringComparisonValue() const;
	double GetNumberComparisonValue() const;
	TArray<FString> GetStringArrayComparisonValue() const;

	configcat::UserCondition UserCondition;
};

enum class EConfigCatPrerequisiteFlagComparator
{
	Invalid = -1,
	Equals = 0,
	NotEquals = 1
};

class UConfigCatPrerequisiteFlagConditionWrapper : public UObject
{
	FString GetPrerequisiteFlagKey() const;
	EConfigCatPrerequisiteFlagComparator GetComparator() const;
	UConfigCatValueWrapper* GetComparisonValue() const;

	configcat::PrerequisiteFlagCondition PrerequisiteFlagCondition;
};

enum class EConfigCatSegmentComparator
{
	Invalid = -1,
	IsIn = 0,
	IsNotIn = 2,
};

class UConfigCatSegmentConditionWrapper : public UObject
{
	int32 GetSegmentIndex() const;
	EConfigCatSegmentComparator GetComparator() const;

	configcat::SegmentCondition SegmentCondition;
};

UCLASS(DisplayName="Config Cat Targeting Rule", Hidden)
class UConfigCatTargetingRuleWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatTargetingRuleWrapper* CreateTargetingRule(const configcat::TargetingRule& InTargetingRule);

	// TArray<UConfigCatConditionWrapper*> GetConditions() const;
	UConfigCatValueWrapper* GetThenSettingValue() const;
	TArray<UConfigCatPercentageOptionWrapper*> GetThenPercentageOptions() const;

	configcat::TargetingRule TargetingRule;
};