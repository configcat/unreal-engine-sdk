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

bool FConfigCatValue::HasAnyValue() const
{
	return HasBooleanValue() || HasStringValue() || HasIntegerValue() || HasDecimalValue();
}

bool FConfigCatValue::HasBooleanValue() const
{
	return Value && std::holds_alternative<bool>(*Value);
}

bool FConfigCatValue::HasStringValue() const
{
	return Value && std::holds_alternative<bool>(*Value);
}

bool FConfigCatValue::HasIntegerValue() const
{
	return Value && std::holds_alternative<int>(*Value);
}

bool FConfigCatValue::HasDecimalValue() const
{
	return Value && std::holds_alternative<bool>(*Value);
}

bool FConfigCatValue::GetBooleanValue() const
{
	if (HasBooleanValue())
	{
		return std::get<bool>(*Value);
	}

	return {};
}

FString FConfigCatValue::GetStringValue() const
{
	if (HasStringValue())
	{
		return UTF8_TO_TCHAR(std::get<std::string>(*Value).c_str());
	}

	return {};
}

int FConfigCatValue::GetIntegerValue() const
{
	if (HasIntegerValue())
	{
		return std::get<int>(*Value);
	}

	return {};
}

double FConfigCatValue::GetDecimalValue() const
{
	if (HasDecimalValue())
	{
		return std::get<double>(*Value);
	}

	return {};
}

bool UConfigCatValueAccessorsBPLibrary::HasAnyValue(const FConfigCatValue& Struct)
{
	return Struct.HasAnyValue();
}

bool UConfigCatValueAccessorsBPLibrary::HasBooleanValue(const FConfigCatValue& Struct)
{
	return Struct.HasBooleanValue();
}

bool UConfigCatValueAccessorsBPLibrary::HasStringValue(const FConfigCatValue& Struct)
{
	return Struct.HasStringValue();
}

bool UConfigCatValueAccessorsBPLibrary::HasIntegerValue(const FConfigCatValue& Struct)
{
	return Struct.HasIntegerValue();
}

bool UConfigCatValueAccessorsBPLibrary::HasDecimalValue(const FConfigCatValue& Struct)
{
	return Struct.HasDecimalValue();
}

bool UConfigCatValueAccessorsBPLibrary::GetBooleanValue(const FConfigCatValue& Struct)
{
	return Struct.GetBooleanValue();
}

FString UConfigCatValueAccessorsBPLibrary::GetStringValue(const FConfigCatValue& Struct)
{
	return Struct.GetStringValue();
}

int UConfigCatValueAccessorsBPLibrary::GetIntegerValue(const FConfigCatValue& Struct)
{
	return Struct.GetIntegerValue();
}

double UConfigCatValueAccessorsBPLibrary::GetDecimalValue(const FConfigCatValue& Struct)
{
	return Struct.GetDecimalValue();
}

FConfigCatValue UConfigCatValueAccessorsBPLibrary::CreteBooleanValue(bool Value)
{
	return FConfigCatValue(configcat::Value(Value));
}

FConfigCatValue UConfigCatValueAccessorsBPLibrary::CreateStringValue(const FString& Value)
{
	const std::string StringValue = TCHAR_TO_UTF8(*Value);
	return FConfigCatValue(configcat::Value(StringValue));
}

FConfigCatValue UConfigCatValueAccessorsBPLibrary::CreateIntegerValue(int Value)
{
	return FConfigCatValue(configcat::Value(Value));
}

FConfigCatValue UConfigCatValueAccessorsBPLibrary::CreateDecimalValue(double Value)
{
	return FConfigCatValue(configcat::Value(Value));
}
