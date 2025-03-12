// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <Modules/ModuleManager.h>

#include <Interfaces/IHttpRequest.h>

class CONFIGCATPLATFORMNETWORK_API FConfigCatPlatformNetworkModule : public IModuleInterface
{
public:
	static void ApplyProxySettings(FHttpRequestPtr Request, const FString& ProxyUrl, const FString& ProxyUsername, const FString& ProxyPassword);
	static void CleanupProxySettings(FHttpRequestPtr Request);
};
