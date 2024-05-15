// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "ConfigCatSettingValueContainerWrapper.h"

#include "ConfigCatValueWrapper.h"

UConfigCatSettingValueContainerWrapper* UConfigCatSettingValueContainerWrapper::CreateSettingValue(const configcat::SettingValueContainer& SettingValueContainer)
{
	UConfigCatSettingValueContainerWrapper* Result = NewObject<UConfigCatSettingValueContainerWrapper>();
	Result->SettingValueContainer = SettingValueContainer; 
	return Result;
}

FString UConfigCatSettingValueContainerWrapper::GetVariationId() const
{
	if (SettingValueContainer.variationId.has_value())
 	{
 		return UTF8_TO_TCHAR(SettingValueContainer.variationId.value().c_str());
 	}
 
 	return {};
}

UConfigCatValueWrapper* UConfigCatSettingValueContainerWrapper::GetValue() const
{
	return UConfigCatValueWrapper::CreateValue(SettingValueContainer.value);
}