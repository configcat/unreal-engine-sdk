// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConfigCatCppSDK/Include/config.h"
#include "UObject/Object.h"
#include "ConfigCatPercentageOptionWrapper.generated.h"

/**
 * 
 */
UCLASS()
class CONFIGCAT_API UConfigCatPercentageOptionWrapper : public UObject
{
	GENERATED_BODY()


public:
	static UConfigCatPercentageOptionWrapper* CreatePercentageOptions(const configcat::PercentageOption& InPercentageOptions);

};
