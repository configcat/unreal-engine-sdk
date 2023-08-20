// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "ConfigCatValue.h"

#include "ConfigCatLog.h"

FConfigCatValue::FConfigCatValue(const configcat::Value& InValue)
{
	if (std::holds_alternative<bool>(InValue))
	{
		Value.Set<bool>(std::get<bool>(InValue));
	}
	else if (std::holds_alternative<std::string>(InValue))
	{
		Value.Set<FString>(UTF8_TO_TCHAR(std::get<std::string>(InValue).c_str()));
	}
	else if (std::holds_alternative<int>(InValue))
	{
		Value.Set<int>(std::get<int>(InValue));
	}
	else if (std::holds_alternative<double>(InValue))
	{
		Value.Set<double>(std::get<double>(InValue));
	}
	else
	{
		const FString InValueString = UTF8_TO_TCHAR(configcat::valueToString(InValue).c_str());
		UE_LOG(LogConfigCat, Error, TEXT("Could not parse std::variant (%s) to TVariant inside FConfigCatValue"), *InValueString);
	}
}

bool UConfigCatValueAccessorsBPLibrary::HasAnyValue(const FConfigCatValue& Struct)
{
	return HasBooleanValue(Struct) || HasStringValue(Struct) || HasIntegerValue(Struct) || HasDecimalValue(Struct);
}
bool UConfigCatValueAccessorsBPLibrary::HasBooleanValue(const FConfigCatValue& Struct)
{
	return Struct.Value.IsType<bool>();
}
bool UConfigCatValueAccessorsBPLibrary::HasStringValue(const FConfigCatValue& Struct)
{
	return Struct.Value.IsType<FString>();
}
bool UConfigCatValueAccessorsBPLibrary::HasIntegerValue(const FConfigCatValue& Struct)
{
	return Struct.Value.IsType<int>();
}
bool UConfigCatValueAccessorsBPLibrary::HasDecimalValue(const FConfigCatValue& Struct)
{
	return Struct.Value.IsType<double>();
}
bool UConfigCatValueAccessorsBPLibrary::GetBooleanValue(const FConfigCatValue& Struct)
{
	const bool* Result = Struct.Value.TryGet<bool>();
	return Result ? *Result : false;
}
FString UConfigCatValueAccessorsBPLibrary::GetStringValue(const FConfigCatValue& Struct)
{
	const FString* Result = Struct.Value.TryGet<FString>();
	return Result ? *Result : TEXT("");
}
int UConfigCatValueAccessorsBPLibrary::GetIntegerValue(const FConfigCatValue& Struct)
{
	const int* Result = Struct.Value.TryGet<int>();
	return Result ? *Result : 0;
}
double UConfigCatValueAccessorsBPLibrary::GetDecimalValue(const FConfigCatValue& Struct)
{
	const double* Result = Struct.Value.TryGet<double>();
	return Result ? *Result : 0.0;
}
