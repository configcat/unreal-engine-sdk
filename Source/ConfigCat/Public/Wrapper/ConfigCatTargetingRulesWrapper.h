// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConfigCatCppSDK/Include/config.h"
#include "UObject/Object.h"
#include "ConfigCatTargetingRulesWrapper.generated.h"

/**
 * 
 */
UCLASS()
class CONFIGCAT_API UConfigCatTargetingRulesWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatTargetingRulesWrapper* CreateTargetingRules(const configcat::TargetingRules& InPercentageOptions);
};

