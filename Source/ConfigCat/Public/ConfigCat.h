// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <Modules/ModuleManager.h>

/**
 * ConfigCat module brings remote feature flag and configuration management in Unreal Engine
 */
class CONFIGCAT_API FConfigCatModule : public IModuleInterface
{
public:
	/**
	 * Returns the ConfigCat folder from within the project (not the plugin)
	 */
	static FString GetContentFolder();
};
