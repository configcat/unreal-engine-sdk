// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "Wrapper/ConfigCatPercentageOptionWrapper.h"

UConfigCatPercentageOptionWrapper* UConfigCatPercentageOptionWrapper::CreatePercentageOption(const configcat::PercentageOption& InPercentageOption)
{
	UConfigCatPercentageOptionWrapper* Result = NewObject<UConfigCatPercentageOptionWrapper>();
	Result->PercentageOption = InPercentageOption;
	return Result;
}