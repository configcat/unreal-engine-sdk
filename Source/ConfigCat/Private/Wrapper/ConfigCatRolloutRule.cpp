// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "Wrapper/ConfigCatRolloutRule.h"

#include <ConfigCatCppSDK/Include/config.h>

#include "Wrapper/ConfigCatRolloutPercentageItem.h"

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
