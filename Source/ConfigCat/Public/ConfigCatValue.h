// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include <memory>

#include "ConfigCatValue.generated.h"

namespace configcat
{
	struct Value;
}

USTRUCT(BlueprintType)
struct FConfigCatValue
{
	GENERATED_BODY()

	FConfigCatValue() = default;
	FConfigCatValue(const configcat::Value& InValue);
	FConfigCatValue(std::shared_ptr<configcat::Value> InValue);

	std::shared_ptr<configcat::Value> Value;
};

UCLASS()
class UConfigCatValueAccessorsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static bool HasAnyValue(const FConfigCatValue& Struct);

	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static bool HasBooleanValue(const FConfigCatValue& Struct);
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static bool HasStringValue(const FConfigCatValue& Struct);
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static bool HasIntegerValue(const FConfigCatValue& Struct);
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static bool HasDecimalValue(const FConfigCatValue& Struct);

	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static bool GetBooleanValue(const FConfigCatValue& Struct);
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static FString GetStringValue(const FConfigCatValue& Struct);
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static int GetIntegerValue(const FConfigCatValue& Struct);
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Value")
	static double GetDecimalValue(const FConfigCatValue& Struct);
};
