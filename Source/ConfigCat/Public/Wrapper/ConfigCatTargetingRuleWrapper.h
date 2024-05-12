// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include "ConfigCatCppSDK/Include/config.h"

#include "ConfigCatTargetingRuleWrapper.generated.h"

UCLASS(DisplayName="Config Cat Targeting Rule", Hidden)
class UConfigCatTargetingRuleWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatTargetingRuleWrapper* CreateTargetingRule(const configcat::TargetingRule& InTargetingRule);

	configcat::TargetingRule TargetingRule;
};

