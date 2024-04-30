// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ConfigCatCppSDK/Include/config.h>

#include <optional>

#include "ConfigCatValueWrapper.generated.h"

UCLASS(DisplayName="Config Cat Value", Hidden)
class CONFIGCAT_API UConfigCatValueWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatValueWrapper* CreateValue(configcat::Value InValue);
	static UConfigCatValueWrapper* CreateValue(std::optional<configcat::Value> InValue);

	/**
	 * Checks if the struct holds any type value
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	bool HasAnyValue() const;
	/**
	 * Checks if the struct holds a boolean value
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	bool HasBooleanValue() const;
	/**
	 * Checks if the struct holds a string value
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	bool HasStringValue() const;
	/**
	 * Checks if the struct holds an integer value
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	bool HasIntegerValue() const;
	/**
	 * Checks if the struct holds a decimal (double) value
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	bool HasDecimalValue() const;

	/**
	 * Returns the boolean value stored in the struct, if it holds one
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	bool GetBooleanValue() const;
	/**
	 * Returns the string value stored in the struct, if it holds one
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	FString GetStringValue() const;
	/**
	 * Returns the integer value stored in the struct, if it holds one
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	int GetIntegerValue() const;
	/**
	 * Returns the decimal (double) value stored in the struct, if it holds one
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	double GetDecimalValue() const;

	void SetValue(std::optional<configcat::Value> InValue);

private:
	std::optional<configcat::Value> Value;
};
