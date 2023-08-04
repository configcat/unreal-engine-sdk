// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "ConfigCatuser.h"

#include <ConfigCatCppSDK/Include/configcatuser.h>

using namespace configcat;

ConfigCatUser FConfigCatUser::ToNative() const
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

	return ConfigCatUser(UserId, UserEmail, UserCountry, UserAttributes);
}

bool FConfigCatUser::IsValid() const
{
	if (Id.IsEmpty() && Email.IsEmpty() && Country.IsEmpty() && Attributes.IsEmpty())
	{
		return false;
	}

	return true;
}
