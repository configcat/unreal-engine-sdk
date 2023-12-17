// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "Wrapper/ConfigCatRolloutRule.h"

#include <ConfigCatCppSDK/Include/config.h>

#include "Wrapper/ConfigCatValue.h"

FConfigCatRolloutRule::FConfigCatRolloutRule(const configcat::RolloutRule& InRule)
{
	Rule = std::make_shared<configcat::RolloutRule>(InRule);
}

bool FConfigCatRolloutRule::IsValid() const
{
	return Rule.get() != nullptr;
}

FConfigCatValue FConfigCatRolloutRule::GetRuleValue() const
{
	if (IsValid())
	{
		return Rule->value;
	}

	return {};
}

FString FConfigCatRolloutRule::GetRuleComparisonAttribute() const
{
	if (IsValid())
	{
		return UTF8_TO_TCHAR(Rule->comparisonAttribute.c_str());
	}

	return {};
}

FString FConfigCatRolloutRule::GetRuleComparator() const
{
	if (IsValid())
	{
		return UTF8_TO_TCHAR(configcat::comparatorToString(Rule->comparator));
	}

	return {};
}

FString FConfigCatRolloutRule::GetRuleComparisonValue() const
{
	if (IsValid())
	{
		return UTF8_TO_TCHAR(Rule->comparisonValue.c_str());
	}

	return {};
}

FString FConfigCatRolloutRule::GetRuleVariationId() const
{
	if (IsValid())
	{
		return UTF8_TO_TCHAR(Rule->variationId.c_str());
	}

	return {};
}

bool UConfigCatRuleAccessorsBPLibrary::IsValid(const FConfigCatRolloutRule& Struct)
{
	return Struct.IsValid();
}

FConfigCatValue UConfigCatRuleAccessorsBPLibrary::GetRuleValue(const FConfigCatRolloutRule& Struct)
{
	return Struct.GetRuleValue();
}

FString UConfigCatRuleAccessorsBPLibrary::GetRuleComparisonAttribute(const FConfigCatRolloutRule& Struct)
{
	return Struct.GetRuleComparisonAttribute();
}

FString UConfigCatRuleAccessorsBPLibrary::GetRuleComparator(const FConfigCatRolloutRule& Struct)
{
	return Struct.GetRuleComparator();
}

FString UConfigCatRuleAccessorsBPLibrary::GetRuleComparisonValue(const FConfigCatRolloutRule& Struct)
{
	return Struct.GetRuleComparisonValue();
}

FString UConfigCatRuleAccessorsBPLibrary::GetRuleVariationId(const FConfigCatRolloutRule& Struct)
{
	return Struct.GetRuleVariationId();
}
