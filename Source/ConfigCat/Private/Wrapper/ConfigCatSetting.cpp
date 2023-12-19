// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "Wrapper/ConfigCatSetting.h"

#include <ConfigCatCppSDK/Include/config.h>

#include "Wrapper/ConfigCatRolloutPercentageItem.h"
#include "Wrapper/ConfigCatRolloutRule.h"
#include "Wrapper/ConfigCatValue.h"

FConfigCatSetting::FConfigCatSetting(const configcat::Setting& InSetting)
{
	Setting = std::make_shared<configcat::Setting>(InSetting);
}

FConfigCatValue FConfigCatSetting::GetSettingValue() const
{
	if (Setting)
	{
		return Setting->value;
	}

	return {};
}

TArray<FConfigCatRolloutRule> FConfigCatSetting::GetSettingRolloutRules() const
{
	TArray<FConfigCatRolloutRule> Result;

	if (Setting)
	{
		for (const auto& Rule : Setting->rolloutRules)
		{
			Result.Emplace(Rule);
		}
	}

	return Result;
}

TArray<FConfigCatRolloutPercentageItem> FConfigCatSetting::GetSettingRolloutPercentageItem() const
{
	TArray<FConfigCatRolloutPercentageItem> Result;

	if (Setting)
	{
		for (const auto& PercentageItem : Setting->percentageItems)
		{
			Result.Emplace(PercentageItem);
		}
	}

	return Result;
}

FString FConfigCatSetting::GetSettingVariationId() const
{
	if (Setting)
	{
		return UTF8_TO_TCHAR(Setting->variationId.c_str());
	}

	return {};
}

FConfigCatValue UConfigCatSettingAccessorsBPLibrary::GetSettingValue(const FConfigCatSetting& Struct)
{
	return Struct.GetSettingValue();
}

TArray<FConfigCatRolloutRule> UConfigCatSettingAccessorsBPLibrary::GetSettingRolloutRules(const FConfigCatSetting& Struct)
{
	return Struct.GetSettingRolloutRules();
}

TArray<FConfigCatRolloutPercentageItem> UConfigCatSettingAccessorsBPLibrary::GetSettingRolloutPercentageItem(const FConfigCatSetting& Struct)
{
	return Struct.GetSettingRolloutPercentageItem();
}

FString UConfigCatSettingAccessorsBPLibrary::GetSettingVariationId(const FConfigCatSetting& Struct)
{
	return Struct.GetSettingVariationId();
}