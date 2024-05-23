// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "ConfigCatPercentageOptionWrapper.h"

#include "ConfigCatValueWrapper.h"

UConfigCatPercentageOptionWrapper* UConfigCatPercentageOptionWrapper::CreatePercentageOption(const configcat::PercentageOption& InPercentageOption)
{
	UConfigCatPercentageOptionWrapper* Result = NewObject<UConfigCatPercentageOptionWrapper>();
	Result->PercentageOption = InPercentageOption;
	return Result;
}

uint8 UConfigCatPercentageOptionWrapper::GetPercentage() const
{
	return PercentageOption.percentage;
}

FString UConfigCatPercentageOptionWrapper::GetVariationId() const
{
	if (PercentageOption.variationId)
	{
		return UTF8_TO_TCHAR(PercentageOption.variationId.value().c_str());
	}

	return {};
}

UConfigCatValueWrapper* UConfigCatPercentageOptionWrapper::GetValue() const
{
	return UConfigCatValueWrapper::CreateValue(PercentageOption.value);

}