// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ConfigCatCppSDK/Include/config.h>

#include <memory>

#include "ConfigCatConfigWrapper.generated.h"

UCLASS(DisplayName="Config Cat Config", Hidden)
class CONFIGCAT_API UConfigCatConfigWrapper : public UObject
{
	GENERATED_BODY()

public:
	static UConfigCatConfigWrapper* CreateConfig(std::shared_ptr<const configcat::Settings> InConfig);

	void SetConfig(std::shared_ptr<const configcat::Settings> InConfig);
	
private:
	std::shared_ptr<const configcat::Settings> Config;
};
