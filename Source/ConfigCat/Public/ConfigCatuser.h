// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include "ConfigCatuser.generated.h"

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

	UPROPERTY(BlueprintReadWrite)
	FString Id;

	UPROPERTY(BlueprintReadWrite)
	FString Email;

	UPROPERTY(BlueprintReadWrite)
	FString Country;

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FString> Attributes;

	configcat::ConfigCatUser ToNative() const;

	bool IsValid() const;
};
