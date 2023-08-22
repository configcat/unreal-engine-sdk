// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "Wrapper/ConfigCatUser.h"

#include <ConfigCatCppSDK/Include/configcatuser.h>

using namespace configcat;

FConfigCatUser::FConfigCatUser(ConfigCatUser* InUser)
{
	if (InUser)
	{
		User = std::make_shared<ConfigCatUser>(*InUser);
	}
}

FConfigCatUser::FConfigCatUser(const FString& Id, const FString& Email, const FString& Country, const TMap<FString, FString>& Attributes)
{
	const std::string& UserId = TCHAR_TO_UTF8(*Id);
	const std::string& UserEmail = TCHAR_TO_UTF8(*Email);
	const std::string& UserCountry = TCHAR_TO_UTF8(*Country);

	std::unordered_map<std::string, std::string> UserAttributes;
	for (const TTuple<FString, FString>& Attribute : Attributes)
	{
		const std::string& AttributeKey = TCHAR_TO_UTF8(*Attribute.Key);
		const std::string& AttributeValue = TCHAR_TO_UTF8(*Attribute.Value);

		UserAttributes.emplace(AttributeKey, AttributeValue);
	}

	User = std::make_shared<ConfigCatUser>(UserId, UserEmail, UserCountry, UserAttributes);
}

FConfigCatUser UConfigCatUserAccessorsBPLibrary::CreateUser(const FString& Id, const FString& Email, const FString& Country, const TMap<FString, FString>& Attributes)
{
	return FConfigCatUser(Id, Email, Country, Attributes);
}

FString UConfigCatUserAccessorsBPLibrary::GetIdentifier(const FConfigCatUser& Struct)
{
	if (Struct.User)
	{
		return UTF8_TO_TCHAR(Struct.User->identifier.c_str());
	}

	return TEXT("");
}

FString UConfigCatUserAccessorsBPLibrary::GetAttribute(const FConfigCatUser& Struct, const FString& Key)
{
	const std::string* Result = nullptr;
	if (Struct.User)
	{
		const std::string AttributeKey = TCHAR_TO_UTF8(*Key);
		Result = Struct.User->getAttribute(AttributeKey);
	}

	return Result ? UTF8_TO_TCHAR(Result->c_str()) : TEXT("");
}