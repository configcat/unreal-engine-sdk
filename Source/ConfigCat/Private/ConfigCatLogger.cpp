// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "ConfigCatLogger.h"

#include "ConfigCatLog.h"

using namespace configcat;

FConfigCatLogger::FConfigCatLogger() : ILogger(LOG_LEVEL_DEBUG)
{
}

void FConfigCatLogger::log(configcat::LogLevel level, const std::string& message, const std::exception_ptr& exception)
{
	const FString& LogMessage = UTF8_TO_TCHAR(message.c_str());

	switch (level)
	{
	case LOG_LEVEL_ERROR:
		UE_LOG(LogConfigCat, Error, TEXT("[CPP-SDK] %s"), *LogMessage);
		break;
	case LOG_LEVEL_WARNING:
		UE_LOG(LogConfigCat, Warning, TEXT("[CPP-SDK] %s"), *LogMessage);
		break;
	case LOG_LEVEL_INFO:
		UE_LOG(LogConfigCat, Verbose, TEXT("[CPP-SDK] %s"), *LogMessage);
		break;
	case LOG_LEVEL_DEBUG:
		UE_LOG(LogConfigCat, VeryVerbose, TEXT("[CPP-SDK] %s"), *LogMessage);
		break;
	default:
		UE_LOG(LogConfigCat, Log, TEXT("[CPP-SDK] %s"), *LogMessage);
		break;
	}

	if(exception)
	{
		const FString ExceptionMessage = UTF8_TO_TCHAR(unwrap_exception_message(exception).c_str());
		UE_LOG(LogConfigCat, Error, TEXT("[CPP-SDK] Exception: %s"), *ExceptionMessage);
	}
}
