// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <Modules/ModuleManager.h>

/**
 * @brief ConfigCatEditor module automates the setup required within the editor (e.g.: copying the JSON configs certificate to the final package).
 */
class FConfigCatEditorModule : public IModuleInterface
{
	// Begin IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	// End IModuleInterface interface
};
