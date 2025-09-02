﻿// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ThirdParty/ConfigCatCppSDK/Include/config.h>

#include <memory>

#include "ConfigCatSettingsWrapper.generated.h"

class UConfigCatPercentageOptionWrapper;
class UConfigCatTargetingRuleWrapper;
class UConfigCatValueWrapper;

UENUM(BlueprintType, meta = (DisplayName = "ConfigCat Setting Type"))
enum class EConfigCatSettingType : uint8
{
	Bool = 0,
	String = 1,
	Int = 2,
	Double = 3,
};

UCLASS(meta = (DisplayName = "ConfigCat Setting"))
class CONFIGCAT_API UConfigCatSettingWrapper : public UObject 
{
	GENERATED_BODY()

public:
	static UConfigCatSettingWrapper* CreateSetting(const configcat::Setting& InSetting);

	UFUNCTION(BlueprintPure, Category = "Setting", meta = (Keywords = "ConfigCat"))
	FString GetVariationId() const;

	UFUNCTION(BlueprintPure, Category = "Setting", meta = (Keywords = "ConfigCat"))
	FString GetPercentageOptionsAttribute() const;
	
	UFUNCTION(BlueprintPure, Category = "Setting", meta = (Keywords = "ConfigCat"))
	bool HasInvalidType() const;
	
	UFUNCTION(BlueprintPure, Category = "Setting", meta = (Keywords = "ConfigCat"))
	EConfigCatSettingType GetType() const;
	
	UFUNCTION(BlueprintPure, Category = "Setting", meta = (Keywords = "ConfigCat"))
	UConfigCatValueWrapper* GetValue() const;
	
	UFUNCTION(BlueprintPure, Category = "Setting", meta = (Keywords = "ConfigCat"))
	TArray<UConfigCatTargetingRuleWrapper*> GetTargetingRules() const;

	UFUNCTION(BlueprintPure, Category = "Setting", meta = (Keywords = "ConfigCat"))
	TArray<UConfigCatPercentageOptionWrapper*> GetPercentageOptions() const;

	configcat::Setting Setting;
};

UCLASS(meta = (DisplayName = "ConfigCat Settings"))
class CONFIGCAT_API UConfigCatSettingsWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatSettingsWrapper* CreateSettings(const std::shared_ptr<const configcat::Settings>& InSettings);

	UFUNCTION(BlueprintPure, Category = "Settings", meta = (Keywords = "ConfigCat"))
	TMap<FString, UConfigCatSettingWrapper*> GetSettings() const;

	std::shared_ptr<const configcat::Settings> Settings;
};
