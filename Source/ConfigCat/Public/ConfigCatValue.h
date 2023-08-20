// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include <ConfigCatCppSDK/Include/config.h>

#include "ConfigCatValue.generated.h"

USTRUCT(BlueprintType)
struct FConfigCatValue
{
	GENERATED_BODY()

	FConfigCatValue() = default;
	FConfigCatValue(const configcat::Value& InValue);

	TVariant<bool, FString, int, double> Value;
};

UCLASS()
class UConfigCatValueAccessorsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|Value")
	static bool HasAnyValue(const FConfigCatValue& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|Value")
	static bool HasBooleanValue(const FConfigCatValue& Struct);
	UFUNCTION(BlueprintCallable, Category = "ConfigCat|Value")
	static bool HasStringValue(const FConfigCatValue& Struct);
	UFUNCTION(BlueprintCallable, Category = "ConfigCat|Value")
	static bool HasIntegerValue(const FConfigCatValue& Struct);
	UFUNCTION(BlueprintCallable, Category = "ConfigCat|Value")
	static bool HasDecimalValue(const FConfigCatValue& Struct);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat|Value")
	static bool GetBooleanValue(const FConfigCatValue& Struct);
	UFUNCTION(BlueprintCallable, Category = "ConfigCat|Value")
	static FString GetStringValue(const FConfigCatValue& Struct);
	UFUNCTION(BlueprintCallable, Category = "ConfigCat|Value")
	static int GetIntegerValue(const FConfigCatValue& Struct);
	UFUNCTION(BlueprintCallable, Category = "ConfigCat|Value")
	static double GetDecimalValue(const FConfigCatValue& Struct);
};
