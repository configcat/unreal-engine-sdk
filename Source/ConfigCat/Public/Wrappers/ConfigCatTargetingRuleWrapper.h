// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include "ThirdParty/ConfigCatCppSDK/Include/config.h"

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
	
	UFUNCTION(BlueprintPure, Category = "UserCondition", meta = (Keywords = "ConfigCat"))
	FString GetComparisonAttribute() const;
	UFUNCTION(BlueprintPure, Category = "UserCondition", meta = (Keywords = "ConfigCat"))
	EConfigCatUserComparator GetComparator() const;

	UFUNCTION(BlueprintPure, Category = "UserCondition", meta = (Keywords = "ConfigCat"))
	bool HasAnyComparisonValue();
	UFUNCTION(BlueprintPure, Category = "UserCondition", meta = (Keywords = "ConfigCat"))
   	bool HasStringComparisonValue() const;
   	UFUNCTION(BlueprintPure, Category = "UserCondition", meta = (Keywords = "ConfigCat"))
   	bool HasNumberComparisonValue() const;
   	UFUNCTION(BlueprintPure, Category = "UserCondition", meta = (Keywords = "ConfigCat"))
   	bool HasStringArrayComparisonValue() const;

	UFUNCTION(BlueprintPure, Category = "UserCondition", meta = (Keywords = "ConfigCat"))
	FString GetStringComparisonValue() const;
	UFUNCTION(BlueprintPure, Category = "UserCondition", meta = (Keywords = "ConfigCat"))
	double GetNumberComparisonValue() const;
	UFUNCTION(BlueprintPure, Category = "UserCondition", meta = (Keywords = "ConfigCat"))
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
	
	UFUNCTION(BlueprintPure, Category = "PrerequisiteFlagCondition", meta = (Keywords = "ConfigCat"))
	FString GetPrerequisiteFlagKey() const;
	UFUNCTION(BlueprintPure, Category = "PrerequisiteFlagCondition", meta = (Keywords = "ConfigCat"))
	EConfigCatPrerequisiteFlagComparator GetComparator() const;
	UFUNCTION(BlueprintPure, Category = "PrerequisiteFlagCondition", meta = (Keywords = "ConfigCat"))
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
	
	UFUNCTION(BlueprintPure, Category = "SegmentCondition", meta = (Keywords = "ConfigCat"))
	int32 GetSegmentIndex() const;
	UFUNCTION(BlueprintPure, Category = "SegmentCondition", meta = (Keywords = "ConfigCat"))
	EConfigCatSegmentComparator GetComparator() const;

	configcat::SegmentCondition SegmentCondition;
};

USTRUCT(BlueprintType, meta = (DisplayName = "ConfigCat Condition Container"))
struct CONFIGCAT_API FConfigCatConditionContainer
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "ConditionContainer", meta = (Keywords = "ConfigCat"))
	UConfigCatUserConditionWrapper* UserCondition = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "ConditionContainer", meta = (Keywords = "ConfigCat"))
	UConfigCatPrerequisiteFlagConditionWrapper* PrerequisiteFlagCondition = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "ConditionContainer", meta = (Keywords = "ConfigCat"))
	UConfigCatSegmentConditionWrapper* SegmentCondition = nullptr;
};

USTRUCT(BlueprintType, meta = (DisplayName = "ConfigCat Then Container"))
struct FConfigCatThenContainer
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "ThenContainer", meta = (Keywords = "ConfigCat"))
	UConfigCatSettingValueContainerWrapper* SettingValueContainer = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThenContainer", meta = (Keywords = "ConfigCat"))
	TArray<UConfigCatPercentageOptionWrapper*> PercentageOptions;
};

UCLASS(meta = (DisplayName = "ConfigCat Targeting Rule"))
class CONFIGCAT_API UConfigCatTargetingRuleWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatTargetingRuleWrapper* CreateTargetingRule(const configcat::TargetingRule& InTargetingRule);

	UFUNCTION(BlueprintPure, Category = "TargetingRule", meta = (Keywords = "ConfigCat"))
	TArray<FConfigCatConditionContainer> GetConditions() const;
	UFUNCTION(BlueprintPure, Category = "TargetingRule", meta = (Keywords = "ConfigCat"))
	FConfigCatThenContainer GetThen() const;

	configcat::TargetingRule TargetingRule;
};