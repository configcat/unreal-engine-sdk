// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "Wrapper/ConfigCatRolloutPercentageItem.h"

#include <ConfigCatCppSDK/Include/config.h>

#include "Wrapper/ConfigCatValue.h"

FConfigCatRolloutPercentageItem::FConfigCatRolloutPercentageItem(const configcat::RolloutPercentageItem& InPercentageItem)
{
	PercentageItem = std::make_shared<configcat::RolloutPercentageItem>(InPercentageItem);
}

bool FConfigCatRolloutPercentageItem::IsValid() const
{
	return PercentageItem.get() != nullptr;
}

FConfigCatValue FConfigCatRolloutPercentageItem::GetPercentageValue() const
{
	if (IsValid())
	{
		return PercentageItem->value;
	}

	return {};
}

double FConfigCatRolloutPercentageItem::GetPercentagePercentage() const
{
	if (IsValid())
	{
		return PercentageItem->percentage;
	}

	return {};
}

FString FConfigCatRolloutPercentageItem::GetPercentageVariationId() const
{
	if (IsValid())
	{
		return UTF8_TO_TCHAR(PercentageItem->variationId.c_str());
	}

	return {};
}

bool UConfigCatPercentageItemAccessorsBPLibrary::IsValid(const FConfigCatRolloutPercentageItem& Struct)
{
	return Struct.IsValid();
}

FConfigCatValue UConfigCatPercentageItemAccessorsBPLibrary::GetPercentageValue(const FConfigCatRolloutPercentageItem& Struct)
{
	return Struct.GetPercentageValue();
}

double UConfigCatPercentageItemAccessorsBPLibrary::GetPercentagePercentage(const FConfigCatRolloutPercentageItem& Struct)
{
	return Struct.GetPercentagePercentage();
}

FString UConfigCatPercentageItemAccessorsBPLibrary::GetPercentageVariationId(const FConfigCatRolloutPercentageItem& Struct)
{
	return Struct.GetPercentageVariationId();
}
