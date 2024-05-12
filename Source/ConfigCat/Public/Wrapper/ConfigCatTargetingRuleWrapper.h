// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConfigCatCppSDK/Include/config.h"
#include "UObject/Object.h"
#include "ConfigCatTargetingRuleWrapper.generated.h"

/**
 * 
 */
UCLASS()
class CONFIGCAT_API UConfigCatTargetingRuleWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatTargetingRuleWrapper* CreateTargetingRules(const configcat::TargetingRule& InPercentageOptions);
};

