// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "ConfigCatSha.h"

std::string configcat::sha1(const std::string& input)
{
	const FString InputString = UTF8_TO_TCHAR(input.c_str());

	FSHAHash const Hash = FSHA1::HashBuffer(*InputString, InputString.Len());
	FString FinalString;
	for (int i = 0; i < 20; i++)
	{
		FinalString += FString::Printf(TEXT("%02x"), Hash.Hash[i]);
	}

	return TCHAR_TO_UTF8(*FinalString);
}

std::string configcat::sha256(const std::string& input)
{
	const FString InputString = UTF8_TO_TCHAR(input.c_str());

	FSHA256Signature Hash;
	FPlatformMisc::GetSHA256Signature(*InputString, InputString.Len(), Hash);

	return TCHAR_TO_UTF8(*Hash.ToString());
}