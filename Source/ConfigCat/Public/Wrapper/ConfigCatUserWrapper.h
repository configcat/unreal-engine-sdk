// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ConfigCatCppSDK/Include/configcatuser.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include <memory>

#include "ConfigCatUserWrapper.generated.h"

/**
 * Wrapper class for configcat::ConfigCatUser
 */
USTRUCT(BlueprintType)
struct CONFIGCAT_API FConfigCatUserWrapper
{
	GENERATED_BODY()

	FConfigCatUserWrapper() = default;
	FConfigCatUserWrapper(std::shared_ptr<configcat::ConfigCatUser> InUser);
	FConfigCatUserWrapper(configcat::ConfigCatUser* InUser);
	FConfigCatUserWrapper(const FString& Id, const FString& Email = TEXT(""), const FString& Country = TEXT(""), const TMap<FString, FString>& Attributes = {});

	std::shared_ptr<configcat::ConfigCatUser> GetUser() const;
	FString GetIdentifier() const;
	
	FString GetStringAttribute(const FString& Key) const;
	double GetNumberAttribute(const FString& Key) const;
	FDateTime GetTimeAttribute(const FString& Key) const;
	TArray<FString> GetStringArrayAttribute(const FString& Key) const;

	bool HasAnyAttribute(const FString& Key) const;
	bool HasStringAttribute(const FString& Key) const;
	bool HasNumberAttribute(const FString& Key) const;
	bool HasTimeAttribute(const FString& Key) const;
	bool HasStringArrayAttribute(const FString& Key) const;

private:
	const configcat::ConfigCatUser::AttributeValue* GetUserAttributeForKey(const FString& Key) const;

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
	static FConfigCatUserWrapper CreateUser(const FString& Id, const FString& Email, const FString& Country, const TMap<FString, FString>& Attributes);
	/**
	 * Gets the Id of a ConfigCatUser
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	static FString GetIdentifier(const FConfigCatUserWrapper& Struct);

	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	static FString GetStringAttribute(const FConfigCatUserWrapper& Struct, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	static double GetNumberAttribute(const FConfigCatUserWrapper& Struct, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	static FDateTime GetTimeAttribute(const FConfigCatUserWrapper& Struct, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	static TArray<FString> GetStringArrayAttribute(const FConfigCatUserWrapper& Struct, const FString& Key);

	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	static bool HasAnyAttribute(const FConfigCatUserWrapper& Struct, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	static bool HasStringAttribute(const FConfigCatUserWrapper& Struct, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	static bool HasNumberAttribute(const FConfigCatUserWrapper& Struct, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	static bool HasTimeAttribute(const FConfigCatUserWrapper& Struct, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	static bool HasStringArrayAttribute(const FConfigCatUserWrapper& Struct, const FString& Key);
};