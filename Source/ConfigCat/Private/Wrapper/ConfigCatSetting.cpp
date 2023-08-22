// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "Wrapper/ConfigCatSetting.h"

#include <ConfigCatCppSDK/Include/config.h>

FConfigCatSetting::FConfigCatSetting(const configcat::Setting& InSetting)
{
	Setting = std::make_shared<configcat::Setting>(InSetting);
}

FConfigCatValue UConfigCatSettingAccessorsBPLibrary::GetSettingValue(const FConfigCatSetting& Struct)
{
	if (Struct.Setting)
	{
		return Struct.Setting->value;
	}

	return {};
}

TArray<FConfigCatRolloutRule> UConfigCatSettingAccessorsBPLibrary::GetSettingRolloutRules(const FConfigCatSetting& Struct)
{
	TArray<FConfigCatRolloutRule> Result;

	if (Struct.Setting)
	{
		for (const auto& Rule : Struct.Setting->rolloutRules)
		{
			Result.Emplace(Rule);
		}
	}

	return Result;
}

TArray<FConfigCatRolloutPercentageItem> UConfigCatSettingAccessorsBPLibrary::GetSettingRolloutPercentageItem(const FConfigCatSetting& Struct)
{
	TArray<FConfigCatRolloutPercentageItem> Result;

	if (Struct.Setting)
	{
		for (const auto& PercentageItem : Struct.Setting->percentageItems)
		{
			Result.Emplace(PercentageItem);
		}
	}

	return Result;
}

FString UConfigCatSettingAccessorsBPLibrary::GetSettingVariationId(const FConfigCatSetting& Struct)
{
	if (Struct.Setting)
	{
		return UTF8_TO_TCHAR(Struct.Setting->variationId.c_str());
	}

	return {};
}