// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>

#include <memory>

#include "ConfigCatUser.generated.h"

namespace configcat
{
	class ConfigCatUser;
}

/**
 * Wrapper class for configcat::ConfigCatUser
 */
USTRUCT(BlueprintType)
struct CONFIGCAT_API FConfigCatUser
{
	GENERATED_BODY()

	FConfigCatUser() = default;
	FConfigCatUser(configcat::ConfigCatUser* InUser);
	FConfigCatUser(const FString& Id, const FString& Email, const FString& Country, const TMap<FString, FString>& Attributes);

	/**
	 * Internal user we want to expose in blueprints
	 */
	std::shared_ptr<configcat::ConfigCatUser> User;
};

/**
 * Getters for all the properties of the configcat::ConfigCatUser stored inside a FConfigCatUser wrapper
 */
UCLASS()
class CONFIGCAT_API UConfigCatUserAccessorsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/**
	 * Creates an instance of a ConfigCatUser struct based on the input
	 * @param Id Unique identifier of the user
	 * @param Email Email of the user (note: will be converted into Attribute internally)
	 * @param Country Country of the user (note: will be converted into Attribute internally)
	 * @param Attributes Additional Key-Value pairs associated with the user
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User", meta = (AutoCreateRefTerm = "Attributes"))
	static FConfigCatUser CreateUser(const FString& Id, const FString& Email, const FString& Country, const TMap<FString, FString>& Attributes);
	/**
	 * Gets the Id of a ConfigCatUser
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	static FString GetIdentifier(const FConfigCatUser& Struct);
	/**
	 * Gets an Attribute of a ConfigCatUser based on a Key
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	static FString GetAttribute(const FConfigCatUser& Struct, const FString& Key);
};