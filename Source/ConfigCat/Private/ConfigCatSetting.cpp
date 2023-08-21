// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "ConfigCatSetting.h"

#include <ConfigCatCppSDK/Include/config.h>

FConfigCatSetting::FConfigCatSetting(const configcat::Setting& InSetting)
{
	Setting = std::make_shared<configcat::Setting>(InSetting);
}