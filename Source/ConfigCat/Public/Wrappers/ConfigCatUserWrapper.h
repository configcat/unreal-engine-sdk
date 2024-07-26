// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <Misc/DateTime.h>

#include <memory>

#include "ConfigCatUserWrapper.generated.h"

namespace configcat
{
	class ConfigCatUser;
}

UCLASS(DisplayName="Config Cat User")
class CONFIGCAT_API UConfigCatUserWrapper : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User", meta = (AdvancedDisplay = "Email, Country, Attributes"))
	static UConfigCatUserWrapper* CreateUser(const FString& Id, const FString& Email, const FString& Country, const TMap<FString, FString>& Attributes);
	static UConfigCatUserWrapper* CreateUser(const FString& Id, const FString& Email = TEXT(""), const FString& Country = TEXT(""));
	static UConfigCatUserWrapper* CreateUser(const std::shared_ptr<configcat::ConfigCatUser>& InUser);

	/**
	 * Gets the Id of a ConfigCatUser
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	FString GetIdentifier() const;

	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	FString GetStringAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	double GetNumberAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	FDateTime GetTimeAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	TArray<FString> GetStringArrayAttribute(const FString& Key) const;

	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	bool HasAnyAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	bool HasStringAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	bool HasNumberAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	bool HasTimeAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	bool HasStringArrayAttribute(const FString& Key) const;

	std::shared_ptr<configcat::ConfigCatUser> User;
};