// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "ConfigCatSetting.h"

#include <ConfigCatCppSDK/Include/config.h>

#include "ConfigCatValue.h"

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

FString UConfigCatSettingAccessorsBPLibrary::GetSettingVariationId(const FConfigCatSetting& Struct)
{
	if (Struct.Setting)
	{
		return UTF8_TO_TCHAR(Struct.Setting->variationId.c_str());
	}

	return {};
}