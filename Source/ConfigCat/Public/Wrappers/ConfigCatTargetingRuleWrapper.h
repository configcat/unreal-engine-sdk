// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include "ConfigCatCppSDK/Include/config.h"

#include "ConfigCatTargetingRuleWrapper.generated.h"

class UConfigCatSettingValueContainerWrapper;
class UConfigCatPercentageOptionWrapper;
class UConfigCatValueWrapper;

UENUM(BlueprintType, meta = (DisplayName = "ConfigCat User Comparator"))
enum class EConfigCatUserComparator : uint8
{
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

	Invalid
};

UCLASS(meta = (DisplayName = "ConfigCat User Condition"))
class CONFIGCAT_API UConfigCatUserConditionWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatUserConditionWrapper* CreateUserCondition(const configcat::UserCondition& InUserCondition);
	
	UFUNCTION(BlueprintPure, Category = "ConfigCat|UserCondition")
	FString GetComparisonAttribute() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|UserCondition")
	EConfigCatUserComparator GetComparator() const;

	UFUNCTION(BlueprintPure, Category = "ConfigCat|UserCondition")
	bool HasAnyComparisonValue();
	UFUNCTION(BlueprintPure, Category = "ConfigCat|UserCondition")
   	bool HasStringComparisonValue() const;
   	UFUNCTION(BlueprintPure, Category = "ConfigCat|UserCondition")
   	bool HasNumberComparisonValue() const;
   	UFUNCTION(BlueprintPure, Category = "ConfigCat|UserCondition")
   	bool HasStringArrayComparisonValue() const;

	UFUNCTION(BlueprintPure, Category = "ConfigCat|UserCondition")
	FString GetStringComparisonValue() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|UserCondition")
	double GetNumberComparisonValue() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|UserCondition")
	TArray<FString> GetStringArrayComparisonValue() const;

	configcat::UserCondition UserCondition;
};

UENUM(BlueprintType, meta = (DisplayName = "ConfigCat Prerequisite Flag Comparator"))
enum class EConfigCatPrerequisiteFlagComparator : uint8
{
	Equals = 0,
	NotEquals = 1,
	Invalid
};

UCLASS(meta = (DisplayName = "ConfigCat Prerequisite Flag Condition"))
class CONFIGCAT_API UConfigCatPrerequisiteFlagConditionWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatPrerequisiteFlagConditionWrapper* CreatePrerequisiteFlagCondition(const configcat::PrerequisiteFlagCondition& InPrerequisiteFlagCondition);
	
	UFUNCTION(BlueprintPure, Category = "ConfigCat|PrerequisiteFlagCondition")
	FString GetPrerequisiteFlagKey() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|PrerequisiteFlagCondition")
	EConfigCatPrerequisiteFlagComparator GetComparator() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|PrerequisiteFlagCondition")
	UConfigCatValueWrapper* GetComparisonValue() const;

	configcat::PrerequisiteFlagCondition PrerequisiteFlagCondition;
};

UENUM(BlueprintType, meta = (DisplayName = "ConfigCat Segment Comparator"))
enum class EConfigCatSegmentComparator : uint8
{
	IsIn = 0,
	IsNotIn = 1,
	Invalid
};

UCLASS(meta = (DisplayName = "ConfigCat Segment Condition"))
class CONFIGCAT_API UConfigCatSegmentConditionWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatSegmentConditionWrapper* CreateSegmentCondition(const configcat::SegmentCondition& InSegmentCondition);
	
	UFUNCTION(BlueprintPure, Category = "ConfigCat|SegmentCondition")
	int32 GetSegmentIndex() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|SegmentCondition")
	EConfigCatSegmentComparator GetComparator() const;

	configcat::SegmentCondition SegmentCondition;
};

USTRUCT(BlueprintType, meta = (DisplayName = "ConfigCat Condition Container"))
struct CONFIGCAT_API FConfigCatConditionContainer
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "ConfigCat|ConditionContainer")
	UConfigCatUserConditionWrapper* UserCondition;
	UPROPERTY(BlueprintReadOnly, Category = "ConfigCat|ConditionContainer")
	UConfigCatPrerequisiteFlagConditionWrapper* PrerequisiteFlagCondition;
	UPROPERTY(BlueprintReadOnly, Category = "ConfigCat|ConditionContainer")
	UConfigCatSegmentConditionWrapper* SegmentCondition;
};

USTRUCT(BlueprintType, meta = (DisplayName = "ConfigCat Then Container"))
struct FConfigCatThenContainer
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "ConfigCat|ThenContainer")
	UConfigCatSettingValueContainerWrapper* SettingValueContainer = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "ConfigCat|ThenContainer")
	TArray<UConfigCatPercentageOptionWrapper*> PercentageOptions;
};

UCLASS(meta = (DisplayName = "ConfigCat Targeting Rule"))
class CONFIGCAT_API UConfigCatTargetingRuleWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatTargetingRuleWrapper* CreateTargetingRule(const configcat::TargetingRule& InTargetingRule);

	UFUNCTION(BlueprintPure, Category = "ConfigCat|TargetingRule")
	TArray<FConfigCatConditionContainer> GetConditions() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|TargetingRule")
	FConfigCatThenContainer GetThen() const;

	configcat::TargetingRule TargetingRule;
};