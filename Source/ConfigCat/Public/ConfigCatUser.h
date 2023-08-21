// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include <memory>

#include "ConfigCatUser.generated.h"

namespace configcat
{
	class ConfigCatUser;
}

/**
 *
 */
USTRUCT(BlueprintType)
struct CONFIGCAT_API FConfigCatUser
{
	GENERATED_BODY()

	FConfigCatUser() = default;
	FConfigCatUser(configcat::ConfigCatUser* InUser);
	FConfigCatUser(const FString& Id, const FString& Email, const FString& Country, const TMap<FString, FString>& Attributes);

	std::shared_ptr<configcat::ConfigCatUser> User;
};

UCLASS()
class UConfigCatUserAccessorsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	static FConfigCatUser CreateUser(const FString& Id, const FString& Email, const FString& Country, TMap<FString, FString> Attributes);

	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	static FString GetIdentifier(const FConfigCatUser& Struct);

	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	static FString GetAttribute(const FConfigCatUser& Struct, const FString& Key);
};