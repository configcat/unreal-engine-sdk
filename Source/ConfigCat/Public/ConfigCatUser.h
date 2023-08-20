// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include "ConfigCatUser.generated.h"

namespace configcat
{
	class ConfigCatUser;
} // namespace configcat

/**
 *
 */
USTRUCT(BlueprintType)
struct CONFIGCAT_API FConfigCatUser
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "ConfigCat")
	FString Id;

	UPROPERTY(BlueprintReadWrite, Category = "ConfigCat")
	FString Email;

	UPROPERTY(BlueprintReadWrite, Category = "ConfigCat")
	FString Country;

	UPROPERTY(BlueprintReadWrite, Category = "ConfigCat")
	TMap<FString, FString> Attributes;

	configcat::ConfigCatUser ToNative() const;

	bool IsValid() const;
};
