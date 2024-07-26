// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "Wrappers/ConfigCatSettingsWrapper.h"

#include "Wrappers/ConfigCatPercentageOptionWrapper.h"
#include "Wrappers/ConfigCatTargetingRuleWrapper.h"
#include "Wrappers/ConfigCatValueWrapper.h"

using namespace configcat;

UConfigCatSettingWrapper* UConfigCatSettingWrapper::CreateSetting(const configcat::Setting& InSetting)
{
	UConfigCatSettingWrapper* Result = NewObject<UConfigCatSettingWrapper>();
	Result->Setting = InSetting;
	return Result;
}

bool UConfigCatSettingWrapper::HasInvalidType() const
{
	return Setting.hasInvalidType();
}

EConfigCatSettingTypeWrapper UConfigCatSettingWrapper::GetType() const
{
	return static_cast<EConfigCatSettingTypeWrapper>(Setting.type);
}

FString UConfigCatSettingWrapper::GetPercentageOptionsAttribute() const
{
	if (Setting.percentageOptionsAttribute)
	{
		return UTF8_TO_TCHAR(Setting.percentageOptionsAttribute.value().c_str());
	}

	return {};
}

FString UConfigCatSettingWrapper::GetVariationId() const
{
	if (Setting.variationId)
	{
		return UTF8_TO_TCHAR(Setting.variationId.value().c_str());
	}

	return {};
}

UConfigCatValueWrapper* UConfigCatSettingWrapper::GetValue() const
{
	return UConfigCatValueWrapper::CreateValue(Setting.value);
}

TArray<UConfigCatTargetingRuleWrapper*> UConfigCatSettingWrapper::GetTargetingRules() const
{
	TArray<UConfigCatTargetingRuleWrapper*> Result;
	for (const auto& Rule : Setting.targetingRules)
	{
		Result.Add(UConfigCatTargetingRuleWrapper::CreateTargetingRule(Rule));
	}
	
	return Result;
}

TArray<UConfigCatPercentageOptionWrapper*> UConfigCatSettingWrapper::GetPercentageOptions() const
{
	TArray<UConfigCatPercentageOptionWrapper*> Result;
	for (const auto& Option : Setting.percentageOptions)
	{
		Result.Add(UConfigCatPercentageOptionWrapper::CreatePercentageOption(Option));
	}
	
	return Result;
}

UConfigCatSettingsWrapper* UConfigCatSettingsWrapper::CreateSettings(const std::shared_ptr<const configcat::Settings>& InSettings)
{
	UConfigCatSettingsWrapper* Result = NewObject<UConfigCatSettingsWrapper>();
	Result->Settings = InSettings;
	return Result;
}

TMap<FString, UConfigCatSettingWrapper*> UConfigCatSettingsWrapper::GetSettings() const
{
	TMap<FString, UConfigCatSettingWrapper*> Result;

	if (Settings)
	{
		for (const std::pair<const std::string, Setting>& Setting : *Settings)
		{
			const FString Key = UTF8_TO_TCHAR(Setting.first.c_str());
			UConfigCatSettingWrapper* Value = UConfigCatSettingWrapper::CreateSetting(Setting.second);
			Result.Emplace(Key, Value);
		}
	}

	return Result;
}