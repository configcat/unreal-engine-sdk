// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "Wrapper/ConfigCatRolloutPercentageItem.h"

bool UConfigCatPercentageItemAccessorsBPLibrary::IsValid(const FConfigCatRolloutPercentageItem& Struct)
{
	return Struct.PercentageItem.get() != nullptr;
}

FConfigCatValue UConfigCatPercentageItemAccessorsBPLibrary::GetPercentageValue(const FConfigCatRolloutPercentageItem& Struct)
{
	if (IsValid(Struct))
	{
		return Struct.PercentageItem->value;
	}

	return {};
}

double UConfigCatPercentageItemAccessorsBPLibrary::GetPercentagePercentage(const FConfigCatRolloutPercentageItem& Struct)
{
	if (IsValid(Struct))
	{
		return Struct.PercentageItem->percentage;
	}

	return {};
}

FString UConfigCatPercentageItemAccessorsBPLibrary::GetPercentageVariationId(const FConfigCatRolloutPercentageItem& Struct)
{
	if (IsValid(Struct))
	{
		return UTF8_TO_TCHAR(Struct.PercentageItem->variationId.c_str());
	}

	return {};
}
