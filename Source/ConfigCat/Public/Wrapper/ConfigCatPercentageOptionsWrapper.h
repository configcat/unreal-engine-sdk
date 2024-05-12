// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConfigCatCppSDK/Include/config.h"
#include "UObject/Object.h"
#include "ConfigCatPercentageOptionsWrapper.generated.h"

/**
 * 
 */
UCLASS()
class CONFIGCAT_API UConfigCatPercentageOptionsWrapper : public UObject
{
	GENERATED_BODY()


public:
	static UConfigCatPercentageOptionsWrapper* CreatePercentageOptions(const configcat::PercentageOptions& InPercentageOptions);

};
