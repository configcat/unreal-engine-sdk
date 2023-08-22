// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include <ConfigCatCppSDK/Include/log.h>

/**
 * Implementation of the configcat::ILogger so we can display the messages directly inside Unreal
 */
class FConfigCatLogger : public configcat::ILogger
{
public:
	explicit FConfigCatLogger();
	virtual ~FConfigCatLogger() = default;

	virtual void log(configcat::LogLevel level, const std::string& message) override;
};
