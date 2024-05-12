// Copyright (c) ConfigCat 2024. All Rights Reserved.


#include "Wrapper/ConfigCatValueWrapper.h"

UConfigCatValueWrapper* UConfigCatValueWrapper::CreateValue(configcat::Value InValue)
{
	return CreateValue(std::make_optional(InValue));
}

UConfigCatValueWrapper* UConfigCatValueWrapper::CreateValue(const std::optional<configcat::Value>& InValue)
{
	UConfigCatValueWrapper* Result = NewObject<UConfigCatValueWrapper>();
	Result->Value = InValue;
	return Result;
}

bool UConfigCatValueWrapper::HasAnyValue() const
{
	return HasBooleanValue() || HasStringValue() || HasIntegerValue() || HasDecimalValue();
}

bool UConfigCatValueWrapper::HasBooleanValue() const
{
	return Value && std::holds_alternative<bool>(*Value);
}

bool UConfigCatValueWrapper::HasStringValue() const
{
	return Value && std::holds_alternative<std::string>(*Value);
}

bool UConfigCatValueWrapper::HasIntegerValue() const
{
	return Value && std::holds_alternative<int>(*Value);
}

bool UConfigCatValueWrapper::HasDecimalValue() const
{
	return Value && std::holds_alternative<bool>(*Value);
}

bool UConfigCatValueWrapper::GetBooleanValue() const
{
	if (HasBooleanValue())
	{
		return std::get<bool>(*Value);
	}

	return {};
}

FString UConfigCatValueWrapper::GetStringValue() const
{
	if (HasStringValue())
	{
		return UTF8_TO_TCHAR(std::get<std::string>(*Value).c_str());
	}

	return {};
}

int UConfigCatValueWrapper::GetIntegerValue() const
{
	if (HasIntegerValue())
	{
		return std::get<int>(*Value);
	}

	return {};
}

double UConfigCatValueWrapper::GetDecimalValue() const
{
	if (HasDecimalValue())
	{
		return std::get<double>(*Value);
	}

	return {};
}