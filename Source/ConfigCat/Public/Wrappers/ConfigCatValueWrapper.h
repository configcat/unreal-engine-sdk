// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ConfigCatCppSDK/Include/config.h>

#include <optional>

#include "ConfigCatValueWrapper.generated.h"

UCLASS(meta = (DisplayName = "ConfigCat Value"))
class CONFIGCAT_API UConfigCatValueWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatValueWrapper* CreateValue(const configcat::SettingValue& InValue);
	static UConfigCatValueWrapper* CreateValue(const configcat::Value& InValue);
	static UConfigCatValueWrapper* CreateValue(const std::optional<configcat::Value>& InValue);

	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	bool HasAnyValue() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	bool HasBooleanValue() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	bool HasStringValue() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	bool HasIntegerValue() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	bool HasDecimalValue() const;

	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	bool GetBooleanValue() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	FString GetStringValue() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	int GetIntegerValue() const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	double GetDecimalValue() const;

	std::optional<configcat::Value> Value;
};
