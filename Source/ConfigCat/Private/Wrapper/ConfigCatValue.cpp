// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "Wrapper/ConfigCatValue.h"

#include <ConfigCatCppSDK/Include/config.h>

FConfigCatValue::FConfigCatValue(const configcat::Value& InValue)
{
	Value = std::make_shared<configcat::Value>(InValue);
}

FConfigCatValue::FConfigCatValue(std::shared_ptr<configcat::Value> InValue)
{
	Value = InValue;
}

bool UConfigCatValueAccessorsBPLibrary::HasAnyValue(const FConfigCatValue& Struct)
{
	return HasBooleanValue(Struct) || HasStringValue(Struct) || HasIntegerValue(Struct) || HasDecimalValue(Struct);
}
bool UConfigCatValueAccessorsBPLibrary::HasBooleanValue(const FConfigCatValue& Struct)
{
	return Struct.Value && std::holds_alternative<bool>(*Struct.Value);
}
bool UConfigCatValueAccessorsBPLibrary::HasStringValue(const FConfigCatValue& Struct)
{
	return Struct.Value && std::holds_alternative<bool>(*Struct.Value);
}
bool UConfigCatValueAccessorsBPLibrary::HasIntegerValue(const FConfigCatValue& Struct)
{
	return Struct.Value && std::holds_alternative<int>(*Struct.Value);
}
bool UConfigCatValueAccessorsBPLibrary::HasDecimalValue(const FConfigCatValue& Struct)
{
	return Struct.Value && std::holds_alternative<bool>(*Struct.Value);
}
bool UConfigCatValueAccessorsBPLibrary::GetBooleanValue(const FConfigCatValue& Struct)
{
	if (HasBooleanValue(Struct))
	{
		return std::get<bool>(*Struct.Value);
	}

	return false;
}
FString UConfigCatValueAccessorsBPLibrary::GetStringValue(const FConfigCatValue& Struct)
{
	if (HasStringValue(Struct))
	{
		return UTF8_TO_TCHAR(std::get<std::string>(*Struct.Value).c_str());
	}

	return TEXT("");
}
int UConfigCatValueAccessorsBPLibrary::GetIntegerValue(const FConfigCatValue& Struct)
{
	if (HasIntegerValue(Struct))
	{
		return std::get<int>(*Struct.Value);
	}

	return 0;
}
double UConfigCatValueAccessorsBPLibrary::GetDecimalValue(const FConfigCatValue& Struct)
{
	if (HasDecimalValue(Struct))
	{
		return std::get<double>(*Struct.Value);
	}

	return 0.0;
}
