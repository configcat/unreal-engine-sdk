// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ConfigCatCppSDK/Include/config.h>

#include <memory>

#include "ConfigCatSettingsWrapper.generated.h"

UENUM()
enum EConfigCatSettingTypeWrapper
{
	Boolean = 0,
	String = 1,
	Int = 2,
	Double = 3,
};

UCLASS(DisplayName="Config Cat Settings", Hidden)
class UConfigCatSettingWrapper : public UObject 
{
	GENERATED_BODY()

public:
	static UConfigCatSettingWrapper* CreateSetting(const configcat::Setting& InSetting);

	UFUNCTION(BlueprintPure, Category = "ConfigCat|Setting")
	bool HasInvalidType() const;
	
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Setting")
	EConfigCatSettingTypeWrapper GetType() const;
	
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Setting")
	FString GetPercentageOptionsAttribute() const;
	
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Setting")
	FString GetVariationId() const;

	//TODO: add these:
	// TargetingRules targetingRules;
	// PercentageOptions percentageOptions;
	// SettingValue value;

	configcat::Setting Setting;
};

UCLASS(DisplayName="Config Cat Settings", Hidden)
class CONFIGCAT_API UConfigCatSettingsWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatSettingsWrapper* CreateSettings(const std::shared_ptr<const configcat::Settings>& InSettings);

	UFUNCTION(BlueprintPure, Category = "ConfigCat|Settings")
	TMap<FString, UConfigCatSettingWrapper*> GetSettings() const;

	void SetSettings(const std::shared_ptr<const configcat::Settings>& InSettings);
	
private:
	std::shared_ptr<const configcat::Settings> Settings;
};
