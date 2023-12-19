// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include <EditorSubsystem.h>

#include "ConfigCatEditorSubsystem.generated.h"

/**
 * @brief Automates setup steps required by the ConfigCat plugin (copying SSL certificates, adding files to the final package) 
 */
UCLASS()
class UConfigCatEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

	/**
	 * @brief Ensures the ConfigCat folder from the project content directory is staged in the final build.
	 */
	void EnsureContentIsPackaged();
	// Begin UEditorSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	// End UEditorSubsystem interface
};
