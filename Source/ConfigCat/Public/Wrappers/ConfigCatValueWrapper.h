// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ThirdParty/ConfigCatCppSDK/Include/config.h>

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

	UFUNCTION(BlueprintPure, Category = "Value", meta = (Keywords = "ConfigCat"))
	bool HasAnyValue() const;
	UFUNCTION(BlueprintPure, Category = "Value", meta = (Keywords = "ConfigCat"))
	bool HasBooleanValue() const;
	UFUNCTION(BlueprintPure, Category = "Value", meta = (Keywords = "ConfigCat"))
	bool HasStringValue() const;
	UFUNCTION(BlueprintPure, Category = "Value", meta = (Keywords = "ConfigCat"))
	bool HasIntegerValue() const;
	UFUNCTION(BlueprintPure, Category = "Value", meta = (Keywords = "ConfigCat"))
	bool HasDecimalValue() const;

	UFUNCTION(BlueprintPure, Category = "Value", meta = (Keywords = "ConfigCat"))
	bool GetBooleanValue() const;
	UFUNCTION(BlueprintPure, Category = "Value", meta = (Keywords = "ConfigCat"))
	FString GetStringValue() const;
	UFUNCTION(BlueprintPure, Category = "Value", meta = (Keywords = "ConfigCat"))
	int GetIntegerValue() const;
	UFUNCTION(BlueprintPure, Category = "Value", meta = (Keywords = "ConfigCat"))
	double GetDecimalValue() const;

	std::optional<configcat::Value> Value;
};
