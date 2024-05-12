// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "Wrapper/ConfigCatTargetingRuleWrapper.h"

UConfigCatTargetingRuleWrapper* UConfigCatTargetingRuleWrapper::CreateTargetingRule(const configcat::TargetingRule& InTargetingRule)
{
	UConfigCatTargetingRuleWrapper* Result = NewObject<UConfigCatTargetingRuleWrapper>();
	Result->TargetingRule = InTargetingRule;
	return Result;
}
