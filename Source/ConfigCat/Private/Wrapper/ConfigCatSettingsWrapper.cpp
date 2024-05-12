// Fill out your copyright notice in the Description page of Project Settings.

#include "Wrapper/ConfigCatSettingsWrapper.h"

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
	if(Setting.percentageOptionsAttribute)
	{
		return UTF8_TO_TCHAR(Setting.percentageOptionsAttribute.value().c_str());
	}

	return {};
}

FString UConfigCatSettingWrapper::GetVariationId() const
{
	if(Setting.variationId)
	{
		return UTF8_TO_TCHAR(Setting.variationId.value().c_str());
	}

	return {};
}

UConfigCatSettingsWrapper* UConfigCatSettingsWrapper::CreateSettings(const std::shared_ptr<const configcat::Settings>& InSettings)
{
	UConfigCatSettingsWrapper* Result = NewObject<UConfigCatSettingsWrapper>();
	Result->SetSettings(InSettings);
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

void UConfigCatSettingsWrapper::SetSettings(const std::shared_ptr<const configcat::Settings>& InSettings)
{
	Settings = InSettings;
}