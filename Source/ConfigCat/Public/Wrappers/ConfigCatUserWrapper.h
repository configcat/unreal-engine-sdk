// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <Misc/DateTime.h>

#include <memory>

#include "ConfigCatUserWrapper.generated.h"

namespace configcat
{
	class ConfigCatUser;
}

UCLASS(meta = (DisplayName = "ConfigCat User"))
class CONFIGCAT_API UConfigCatUserWrapper : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "User", meta = (Keywords = "ConfigCat", AdvancedDisplay = "Email, Country, Attributes", AutoCreateRefTerm = "Attributes"))
	static UConfigCatUserWrapper* CreateUser(const FString& Id, const FString& Email, const FString& Country, const TMap<FString, FString>& Attributes);
	static UConfigCatUserWrapper* CreateUser(const FString& Id, const FString& Email = TEXT(""), const FString& Country = TEXT(""));
	static UConfigCatUserWrapper* CreateUser(const std::shared_ptr<configcat::ConfigCatUser>& InUser);

	/**
	 * Gets the Id of a ConfigCatUser
	 */
	UFUNCTION(BlueprintPure, Category = "User", meta = (Keywords = "ConfigCat"))
	FString GetIdentifier() const;

	UFUNCTION(BlueprintPure, Category = "User", meta = (Keywords = "ConfigCat"))
	FString GetStringAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "User", meta = (Keywords = "ConfigCat"))
	double GetNumberAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "User", meta = (Keywords = "ConfigCat"))
	FDateTime GetTimeAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "User", meta = (Keywords = "ConfigCat"))
	TArray<FString> GetStringArrayAttribute(const FString& Key) const;

	UFUNCTION(BlueprintPure, Category = "User", meta = (Keywords = "ConfigCat"))
	bool HasAnyAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "User", meta = (Keywords = "ConfigCat"))
	bool HasStringAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "User", meta = (Keywords = "ConfigCat"))
	bool HasNumberAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "User", meta = (Keywords = "ConfigCat"))
	bool HasTimeAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "User", meta = (Keywords = "ConfigCat"))
	bool HasStringArrayAttribute(const FString& Key) const;

	std::shared_ptr<configcat::ConfigCatUser> User;
};