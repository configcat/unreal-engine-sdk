// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "Wrapper/ConfigCatUserWrapper.h"

#include <ConfigCatCppSDK/Include/configcatuser.h>

using namespace configcat;

FConfigCatUserWrapper::FConfigCatUserWrapper(std::shared_ptr<configcat::ConfigCatUser> InUser)
{
	User = InUser;
}

FConfigCatUserWrapper::FConfigCatUserWrapper(ConfigCatUser* InUser)
{
	if (InUser)
	{
		User = std::make_shared<ConfigCatUser>(*InUser);
	}
}

FConfigCatUserWrapper::FConfigCatUserWrapper(const FString& Id, const FString& Email, const FString& Country, const TMap<FString, FString>& Attributes)
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

	User = std::make_shared<ConfigCatUser>(UserId, UserEmail, UserCountry, UserAttributes);
}

std::shared_ptr<ConfigCatUser> FConfigCatUserWrapper::GetUser() const
{
	return User;
}

FString FConfigCatUserWrapper::GetIdentifier() const
{
	if (User)
	{
		return UTF8_TO_TCHAR(User->getIdentifier().c_str());
	}

	return {};
}

FString FConfigCatUserWrapper::GetStringAttribute(const FString& Key) const
{
	if (HasStringAttribute(Key))
	{
		const ConfigCatUser::AttributeValue* Attribute = GetUserAttributeForKey(Key);
		return UTF8_TO_TCHAR(std::get<std::string>(*Attribute).c_str());
	}

	return {};
}

double FConfigCatUserWrapper::GetNumberAttribute(const FString& Key) const
{
	if (HasStringAttribute(Key))
	{
		const ConfigCatUser::AttributeValue* Attribute = GetUserAttributeForKey(Key);
		return std::get<double>(*Attribute);
	}

	return {};
}

FDateTime FConfigCatUserWrapper::GetTimeAttribute(const FString& Key) const
{
	if (HasStringAttribute(Key))
	{
		const ConfigCatUser::AttributeValue* Attribute = GetUserAttributeForKey(Key);
		const auto TimeSinceEpoch = std::get<date_time_t>(*Attribute).time_since_epoch().count();
		return FDateTime::FromUnixTimestamp(TimeSinceEpoch);
	}

	return {};
}

TArray<FString> FConfigCatUserWrapper::GetStringArrayAttribute(const FString& Key) const
{
	if (HasStringAttribute(Key))
	{
		const ConfigCatUser::AttributeValue* Attribute = GetUserAttributeForKey(Key);
		TArray<FString> Result;
		auto ArrayAttribute = std::get<std::vector<std::string>>(*Attribute);
		for(const auto& ArrayIt : ArrayAttribute)
		{
			Result.Emplace(UTF8_TO_TCHAR(ArrayIt.c_str()));
		}
		return Result;
	}

	return {};
}

bool FConfigCatUserWrapper::HasAnyAttribute(const FString& Key) const
{
	return HasStringAttribute(Key) || HasNumberAttribute(Key) || HasTimeAttribute(Key) || HasStringArrayAttribute(Key);
}

bool FConfigCatUserWrapper::HasStringAttribute(const FString& Key) const
{
	const ConfigCatUser::AttributeValue* Attribute = GetUserAttributeForKey(Key);
	return Attribute && std::holds_alternative<std::string>(*Attribute);
}

bool FConfigCatUserWrapper::HasNumberAttribute(const FString& Key) const
{
	const ConfigCatUser::AttributeValue* Attribute = GetUserAttributeForKey(Key);
	return Attribute && std::holds_alternative<double>(*Attribute);
}

bool FConfigCatUserWrapper::HasTimeAttribute(const FString& Key) const
{
	const ConfigCatUser::AttributeValue* Attribute = GetUserAttributeForKey(Key);
	return Attribute && std::holds_alternative<date_time_t>(*Attribute);
}

bool FConfigCatUserWrapper::HasStringArrayAttribute(const FString& Key) const
{
	const ConfigCatUser::AttributeValue* Attribute = GetUserAttributeForKey(Key);
	return Attribute && std::holds_alternative<std::vector<std::string>>(*Attribute);
}

const configcat::ConfigCatUser::AttributeValue* FConfigCatUserWrapper::GetUserAttributeForKey(const FString& Key) const
{
	if (!User)
	{
		return {};
	}

	const std::string AttributeKey = TCHAR_TO_UTF8(*Key);
	return User->getAttribute(AttributeKey);
}

FConfigCatUserWrapper UConfigCatUserAccessorsBPLibrary::CreateUser(const FString& Id, const FString& Email, const FString& Country, const TMap<FString, FString>& Attributes)
{
	return FConfigCatUserWrapper(Id, Email, Country, Attributes);
}

FString UConfigCatUserAccessorsBPLibrary::GetIdentifier(const FConfigCatUserWrapper& Struct)
{
	return Struct.GetIdentifier();
}

FString UConfigCatUserAccessorsBPLibrary::GetStringAttribute(const FConfigCatUserWrapper& Struct, const FString& Key)
{
	return Struct.GetStringAttribute(Key);
}

double UConfigCatUserAccessorsBPLibrary::GetNumberAttribute(const FConfigCatUserWrapper& Struct, const FString& Key)
{
	return Struct.GetNumberAttribute(Key);
}

FDateTime UConfigCatUserAccessorsBPLibrary::GetTimeAttribute(const FConfigCatUserWrapper& Struct, const FString& Key)
{
	return Struct.GetTimeAttribute(Key);
}

TArray<FString> UConfigCatUserAccessorsBPLibrary::GetStringArrayAttribute(const FConfigCatUserWrapper& Struct, const FString& Key)
{
	return Struct.GetStringArrayAttribute(Key);
}

bool UConfigCatUserAccessorsBPLibrary::HasAnyAttribute(const FConfigCatUserWrapper& Struct, const FString& Key)
{
	return Struct.HasAnyAttribute(Key);
}

bool UConfigCatUserAccessorsBPLibrary::HasStringAttribute(const FConfigCatUserWrapper& Struct, const FString& Key)
{
	return Struct.HasStringAttribute(Key);
}

bool UConfigCatUserAccessorsBPLibrary::HasNumberAttribute(const FConfigCatUserWrapper& Struct, const FString& Key)
{
	return Struct.HasNumberAttribute(Key);
}

bool UConfigCatUserAccessorsBPLibrary::HasTimeAttribute(const FConfigCatUserWrapper& Struct, const FString& Key)
{
	return Struct.HasTimeAttribute(Key);
}

bool UConfigCatUserAccessorsBPLibrary::HasStringArrayAttribute(const FConfigCatUserWrapper& Struct, const FString& Key)
{
	return Struct.HasStringArrayAttribute(Key);
}