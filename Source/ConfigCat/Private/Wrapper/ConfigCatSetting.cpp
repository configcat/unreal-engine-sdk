// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "Wrapper/ConfigCatSetting.h"

#include <ConfigCatCppSDK/Include/config.h>

#include "Wrapper/ConfigCatValue.h"

FConfigCatSetting::FConfigCatSetting(const configcat::Setting& InSetting)
{
	Setting = std::make_shared<configcat::Setting>(InSetting);
}

FString FConfigCatSetting::GetSettingVariationId() const
{
	if(!Setting)
	{
		return {};
	}

	const auto VariationId = Setting->variationId;
	if(!VariationId)
	{
		return {};
	}
	
	return UTF8_TO_TCHAR(VariationId.value().c_str());
}

FString UConfigCatSettingAccessorsBPLibrary::GetSettingVariationId(const FConfigCatSetting& Struct)
{
	return Struct.GetSettingVariationId();
}