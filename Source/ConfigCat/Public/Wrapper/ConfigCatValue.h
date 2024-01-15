// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>

#include <memory>

#include "ConfigCatValue.generated.h"

namespace configcat
{
	struct Value;
}

/**
 * Wrapper class for configcat::Value
 */
USTRUCT(BlueprintType)
struct CONFIGCAT_API FConfigCatValue
{
	GENERATED_BODY()

	FConfigCatValue() = default;
	FConfigCatValue(const configcat::Value& InValue);
	FConfigCatValue(std::shared_ptr<configcat::Value> InValue);

	bool HasAnyValue() const;
	bool HasBooleanValue() const;
	bool HasStringValue() const;
	bool HasIntegerValue() const;
	bool HasDecimalValue() const;

	bool GetBooleanValue() const;
	FString GetStringValue() const;
	int GetIntegerValue() const;
	double GetDecimalValue() const;

	/**
	 * Internal feature flag value we want to expose in blueprints
	 */
	std::shared_ptr<configcat::Value> Value;
};

/**
 * Getters for all the properties of the configcat::Value stored inside a FConfigCatValue wrapper
 */
UCLASS()
class CONFIGCAT_API UConfigCatValueAccessorsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/**
	 * Checks if the struct holds any type value
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static bool HasAnyValue(const FConfigCatValue& Struct);
	/**
	 * Checks if the struct holds a boolean value
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static bool HasBooleanValue(const FConfigCatValue& Struct);
	/**
	 * Checks if the struct holds a string value
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static bool HasStringValue(const FConfigCatValue& Struct);
	/**
	 * Checks if the struct holds an integer value
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static bool HasIntegerValue(const FConfigCatValue& Struct);
	/**
	 * Checks if the struct holds a decimal (double) value
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static bool HasDecimalValue(const FConfigCatValue& Struct);

	/**
	 * Returns the boolean value stored in the struct, if it holds one
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static bool GetBooleanValue(const FConfigCatValue& Struct);
	/**
	 * Returns the string value stored in the struct, if it holds one
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static FString GetStringValue(const FConfigCatValue& Struct);
	/**
	 * Returns the integer value stored in the struct, if it holds one
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static int GetIntegerValue(const FConfigCatValue& Struct);
	/**
	 * Returns the decimal (double) value stored in the struct, if it holds one
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static double GetDecimalValue(const FConfigCatValue& Struct);

	/**
	 * Create a ConfigValue holding a boolean value
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static FConfigCatValue CreteBooleanValue(bool Value);
	/**
	 * Create a ConfigValue holding a string value
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static FConfigCatValue CreateStringValue(const FString& Value);
	/**
	 * Create a ConfigValue holding a integer value
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static FConfigCatValue CreateIntegerValue(int Value);
	/**
	 * Create a ConfigValue holding a decimal (double) value
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static FConfigCatValue CreateDecimalValue(double Value);
};
