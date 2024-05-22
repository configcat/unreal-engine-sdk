// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "ConfigCatUserWrapper.h"

#include <ConfigCatCppSDK/Include/configcatuser.h>

using namespace configcat;

UConfigCatUserWrapper* UConfigCatUserWrapper::CreateUser(const FString& Id, const FString& Email, const FString& Country, const TMap<FString, FString>& Attributes)
{
	const std::string& UserId = TCHAR_TO_UTF8(*Id);
	const std::string& UserEmail = TCHAR_TO_UTF8(*Email);
	const std::string& UserCountry = TCHAR_TO_UTF8(*Country);

	std::unordered_map<std::string, ConfigCatUser::AttributeValue> UserAttributes;
	for (const TTuple<FString, FString>& Attribute : Attributes)
	{
		const std::string& AttributeKey = TCHAR_TO_UTF8(*Attribute.Key);
		const std::string& AttributeValue = TCHAR_TO_UTF8(*Attribute.Value);

		UserAttributes.emplace(AttributeKey, AttributeValue);
	}

	return CreateUser(ConfigCatUser::create(UserId, UserEmail, UserCountry, UserAttributes));
}

UConfigCatUserWrapper* UConfigCatUserWrapper::CreateUser(const std::shared_ptr<configcat::ConfigCatUser>& InUser)
{
	UConfigCatUserWrapper* Result = NewObject<UConfigCatUserWrapper>();
	Result->User = InUser;
	return Result;
}

FString UConfigCatUserWrapper::GetIdentifier() const
{
	if (User)
	{
		return UTF8_TO_TCHAR(User->getIdentifier().c_str());
	}

	return {};
}

FString UConfigCatUserWrapper::GetStringAttribute(const FString& Key) const
{
	if (HasStringAttribute(Key))
	{
		const ConfigCatUser::AttributeValue* Attribute = GetUserAttributeForKey(Key);
		return UTF8_TO_TCHAR(std::get<std::string>(*Attribute).c_str());
	}

	return {};
}

double UConfigCatUserWrapper::GetNumberAttribute(const FString& Key) const
{
	if (HasNumberAttribute(Key))
	{
		const ConfigCatUser::AttributeValue* Attribute = GetUserAttributeForKey(Key);
		return std::get<double>(*Attribute);
	}

	return {};
}

FDateTime UConfigCatUserWrapper::GetTimeAttribute(const FString& Key) const
{
	if (HasTimeAttribute(Key))
	{
		const ConfigCatUser::AttributeValue* Attribute = GetUserAttributeForKey(Key);
		const auto TimeSinceEpoch = std::get<date_time_t>(*Attribute).time_since_epoch().count();
		return FDateTime::FromUnixTimestamp(TimeSinceEpoch);
	}

	return {};
}

TArray<FString> UConfigCatUserWrapper::GetStringArrayAttribute(const FString& Key) const
{
	if (HasStringArrayAttribute(Key))
	{
		const ConfigCatUser::AttributeValue* Attribute = GetUserAttributeForKey(Key);
		TArray<FString> Result;
		auto ArrayAttribute = std::get<std::vector<std::string>>(*Attribute);
		for (const auto& ArrayIt : ArrayAttribute)
		{
			Result.Emplace(UTF8_TO_TCHAR(ArrayIt.c_str()));
		}
		return Result;
	}

	return {};
}

bool UConfigCatUserWrapper::HasAnyAttribute(const FString& Key) const
{
	return HasStringAttribute(Key) || HasNumberAttribute(Key) || HasTimeAttribute(Key) || HasStringArrayAttribute(Key);
}

bool UConfigCatUserWrapper::HasStringAttribute(const FString& Key) const
{
	const ConfigCatUser::AttributeValue* Attribute = GetUserAttributeForKey(Key);
	return Attribute && std::holds_alternative<std::string>(*Attribute);
}

bool UConfigCatUserWrapper::HasNumberAttribute(const FString& Key) const
{
	const ConfigCatUser::AttributeValue* Attribute = GetUserAttributeForKey(Key);
	return Attribute && std::holds_alternative<double>(*Attribute);
}

bool UConfigCatUserWrapper::HasTimeAttribute(const FString& Key) const
{
	const ConfigCatUser::AttributeValue* Attribute = GetUserAttributeForKey(Key);
	return Attribute && std::holds_alternative<date_time_t>(*Attribute);
}

bool UConfigCatUserWrapper::HasStringArrayAttribute(const FString& Key) const
{
	const ConfigCatUser::AttributeValue* Attribute = GetUserAttributeForKey(Key);
	return Attribute && std::holds_alternative<std::vector<std::string>>(*Attribute);
}

const ConfigCatUser::AttributeValue* UConfigCatUserWrapper::GetUserAttributeForKey(const FString& Key) const
{
	if (!User)
	{
		return {};
	}

	const std::string AttributeKey = TCHAR_TO_UTF8(*Key);
	return User->getAttribute(AttributeKey);
}