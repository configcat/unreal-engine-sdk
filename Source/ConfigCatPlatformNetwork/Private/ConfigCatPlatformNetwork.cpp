// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "ConfigCatPlatformNetwork.h"

#include <Curl/CurlHttp.h>

#include <Microsoft/AllowMicrosoftPlatformTypes.h>
#include <curl/curl.h>
#include <Microsoft/HideMicrosoftPlatformTypes.h>

void FConfigCatPlatformNetworkModule::ApplyProxySettings(FHttpRequestPtr Request, const FString& ProxyUrl, const FString& ProxyUsername, const FString& ProxyPassword)
{
#if WITH_CURL
	TSharedPtr<FCurlHttpRequest> GetRequestCurl = StaticCastSharedPtr<FCurlHttpRequest>(Request);
	if (CURL* CurlHandle = GetRequestCurl->GetEasyHandle())
	{
		if (!ProxyUrl.IsEmpty())
		{
			curl_easy_setopt(CurlHandle, CURLOPT_PROXY, TCHAR_TO_ANSI(*ProxyUrl));
		}

		if (!ProxyUsername.IsEmpty())
		{
			curl_easy_setopt(CurlHandle, CURLOPT_PROXYUSERNAME, TCHAR_TO_ANSI(*ProxyUsername));
		}

		if (!ProxyPassword.IsEmpty())
		{
			curl_easy_setopt(CurlHandle, CURLOPT_PROXYPASSWORD, TCHAR_TO_ANSI(*ProxyPassword));
		}
	}
#endif
}

void FConfigCatPlatformNetworkModule::CleanupProxySettings(FHttpRequestPtr Request)
{
#if WITH_CURL
	TSharedPtr<FCurlHttpRequest> GetRequestCurl = StaticCastSharedPtr<FCurlHttpRequest>(Request);
	if (CURL* CurlHandle = GetRequestCurl->GetEasyHandle())
	{
		curl_easy_setopt(CurlHandle, CURLOPT_PROXY, nullptr);
		curl_easy_setopt(CurlHandle, CURLOPT_PROXYUSERNAME, nullptr);
		curl_easy_setopt(CurlHandle, CURLOPT_PROXYPASSWORD, nullptr);
	}
#endif
}

IMPLEMENT_MODULE(FConfigCatPlatformNetworkModule, ConfigCatPlatformNetwork)