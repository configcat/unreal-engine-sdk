// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "ConfigCatSha.h"

#include<openssl/sha.h>

TArray<uint8> StringToBytes(const std::string& input)
{
	TArray<uint8> ByteArray;
	ByteArray.Append((uint8*)input.c_str(), input.length());
	return ByteArray;
}

std::string configcat::sha1(const std::string& input)
{
	TArray<uint8> BytesArrayToHash;
	BytesArrayToHash.Append(StringToBytes(input));

	FSHAHash const Hash = FSHA1::HashBuffer(BytesArrayToHash.GetData(), BytesArrayToHash.Num());
	FString FinalString;
	for (int i = 0; i < 20; i++)
	{
		FinalString += FString::Printf(TEXT("%02x"), Hash.Hash[i]);
	}

	return TCHAR_TO_UTF8(*FinalString);
}

std::string configcat::sha256(const std::string& input)
{
	TArray<uint8, TFixedAllocator<SHA256_DIGEST_LENGTH>> Digest;
	Digest.AddUninitialized(SHA256_DIGEST_LENGTH);
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, input.c_str(), input.size());
	SHA256_Final(Digest.GetData(), &sha256);

	FString FinalString;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		FinalString += FString::Printf(TEXT("%02x"), Digest[i]);
	}

	return TCHAR_TO_UTF8(*FinalString);
}