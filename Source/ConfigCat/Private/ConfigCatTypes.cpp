// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfigCatTypes.h"

#include "ConfigCatCppSDK/Include/config.h"
#include "ConfigCatValue.h"

FConfigCatRolloutRule::FConfigCatRolloutRule(const configcat::RolloutRule& InRule)
{
	Rule = std::make_shared<configcat::RolloutRule>(InRule);
}

FConfigCatRolloutPercentageItem::FConfigCatRolloutPercentageItem(const configcat::RolloutPercentageItem& InPercentageItem)
{
	PercentageItem = std::make_shared<configcat::RolloutPercentageItem>(InPercentageItem);
}

bool UConfigCatRuleAccessorsBPLibrary::IsValid(const FConfigCatRolloutRule& Struct)
{
	return Struct.Rule.get() != nullptr;
}

FConfigCatValue UConfigCatRuleAccessorsBPLibrary::GetRuleValue(const FConfigCatRolloutRule& Struct)
{
	if (IsValid(Struct))
	{
		return Struct.Rule->value;
	}

	return {};
}

FString UConfigCatRuleAccessorsBPLibrary::GetRuleComparisonAttribute(const FConfigCatRolloutRule& Struct)
{
	if (IsValid(Struct))
	{
		return UTF8_TO_TCHAR(Struct.Rule->comparisonAttribute.c_str());
	}

	return {};
}

FString UConfigCatRuleAccessorsBPLibrary::GetRuleComparator(const FConfigCatRolloutRule& Struct)
{
	if (IsValid(Struct))
	{
		return UTF8_TO_TCHAR(configcat::comparatorToString(Struct.Rule->comparator));
	}

	return {};
}

FString UConfigCatRuleAccessorsBPLibrary::GetRuleComparisonValue(const FConfigCatRolloutRule& Struct)
{
	if (IsValid(Struct))
	{
		return UTF8_TO_TCHAR(Struct.Rule->comparisonValue.c_str());
	}

	return {};
}

FString UConfigCatRuleAccessorsBPLibrary::GetRuleVariationId(const FConfigCatRolloutRule& Struct)
{
	if (IsValid(Struct))
	{
		return UTF8_TO_TCHAR(Struct.Rule->variationId.c_str());
	}

	return {};
}

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
