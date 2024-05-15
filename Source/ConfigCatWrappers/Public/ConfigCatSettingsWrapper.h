// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ConfigCatCppSDK/Include/config.h>

#include <memory>

#include "ConfigCatSettingsWrapper.generated.h"

class UConfigCatPercentageOptionWrapper;
class UConfigCatTargetingRuleWrapper;
class UConfigCatValueWrapper;

UENUM(BlueprintType)
enum EConfigCatSettingTypeWrapper : uint8
{
	Boolean = 0,
	String = 1,
	Int = 2,
	Double = 3,
};

UCLASS(DisplayName="Config Cat Setting")
class CONFIGCATWRAPPERS_API UConfigCatSettingWrapper : public UObject 
{
	GENERATED_BODY()

public:
	static UConfigCatSettingWrapper* CreateSetting(const configcat::Setting& InSetting);

	UFUNCTION(BlueprintPure, Category = "ConfigCat|Setting")
	FString GetVariationId() const;

	UFUNCTION(BlueprintPure, Category = "ConfigCat|Setting")
	FString GetPercentageOptionsAttribute() const;
	
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Setting")
	bool HasInvalidType() const;
	
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Setting")
	EConfigCatSettingTypeWrapper GetType() const;
	
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Setting")
	UConfigCatValueWrapper* GetValue() const;
	
	UFUNCTION(BlueprintPure, Category = "ConfigCat|Setting")
	TArray<UConfigCatTargetingRuleWrapper*> GetTargetingRules() const;

	UFUNCTION(BlueprintPure, Category = "ConfigCat|Setting")
	TArray<UConfigCatPercentageOptionWrapper*> GetPercentageOptions() const;

	configcat::Setting Setting;
};

UCLASS(DisplayName="Config Cat Settings")
class CONFIGCATWRAPPERS_API UConfigCatSettingsWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatSettingsWrapper* CreateSettings(const std::shared_ptr<const configcat::Settings>& InSettings);

	UFUNCTION(BlueprintPure, Category = "ConfigCat|Settings")
	TMap<FString, UConfigCatSettingWrapper*> GetSettings() const;

	std::shared_ptr<const configcat::Settings> Settings;
};
