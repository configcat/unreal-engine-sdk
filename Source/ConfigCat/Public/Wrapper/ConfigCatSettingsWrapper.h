// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ConfigCatCppSDK/Include/config.h>

#include <memory>

#include "ConfigCatSettingsWrapper.generated.h"

UCLASS(DisplayName="Config Cat Settings", Hidden)
class UConfigCatSettingWrapper : public UObject 
{
	GENERATED_BODY()

public:
	static UConfigCatSettingWrapper* CreateSetting(const configcat::Setting& InSetting);

	// TODO: Create getters using 'UFUNCTION(BlueprintPure, Category = "ConfigCat|Setting")' for:
	// SettingType type = static_cast<SettingType>(-1);
	// std::optional<std::string> percentageOptionsAttribute;
	// TargetingRules targetingRules;
	// PercentageOptions percentageOptions;
	// SettingValue value;
	// std::optional<std::string> variationId;
	// inline bool hasInvalidType() const { return type < SettingType::Boolean || SettingType::Double < type; }
	// SettingType getTypeChecked() const;

	void SetSetting(const configcat::Setting& InSetting);

private:
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
