// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "ConfigCatNetworkAdapter.h"

#include <ConfigCatCppSDK/Include/pollingmode.h>
#include <HttpManager.h>
#include <HttpModule.h>
#include <Interfaces/IHttpResponse.h>
#include <Interfaces/IPluginManager.h>
#include <Misc/ScopeExit.h>
#include <HAL/PlatformProcess.h>

#include "ConfigCatLog.h"

using namespace configcat;

namespace
{
	const FString UserAgentHeaderName = TEXT("X-ConfigCat-UserAgent");
}

ConfigCatNetworkAdapter::ConfigCatNetworkAdapter(const std::shared_ptr<PollingMode>& InPollingMode)
{
	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("ConfigCat"));
	const FString PluginVersion = Plugin ? Plugin->GetDescriptor().VersionName : TEXT("0.0.0");

	const char* PollingModeIdentifier = InPollingMode ? InPollingMode->getPollingIdentifier() : "x";
	const FString PollingMode = UTF8_TO_TCHAR(PollingModeIdentifier);

	UserAgentVersion = FString::Printf(TEXT("ConfigCat-Unreal/%s-%s"), *PollingMode, *PluginVersion);
}

bool ConfigCatNetworkAdapter::init(uint32_t connectTimeoutMs, uint32_t readTimeoutMs)
{
	UE_LOG(LogConfigCat, Verbose, TEXT("Network Adapter initialized."));

	ConnectionTimeout = connectTimeoutMs;
	ReadTimeout = readTimeoutMs;

	return true;
}

Response ConfigCatNetworkAdapter::get(
	const std::string& url,
	const std::map<std::string, std::string>& header,
	const std::map<std::string, std::string>& proxies,
	const std::map<std::string, ProxyAuthentication>& proxyAuthentications
)
{
	UE_LOG(LogConfigCat, Verbose, TEXT("Network Adapter performing GET request."));

	GetRequest = FHttpModule::Get().CreateRequest();
	ON_SCOPE_EXIT
	{
		GetRequest.Reset();
	};

	GetRequest->SetVerb(TEXT("GET"));

	// We cannot set different timeout durations for connection & read independently, so we combine their duration and set it as the whole request timeout
	const float Timeout = (ConnectionTimeout + ReadTimeout) / 1000.0f;
	GetRequest->SetTimeout(Timeout);

	for (const std::pair<const std::string, std::string>& It : header)
	{
		const FString HeaderKey = UTF8_TO_TCHAR(It.first.c_str());
		const FString HeaderValue = UTF8_TO_TCHAR(It.second.c_str());
		GetRequest->SetHeader(HeaderKey, HeaderValue);
	}

	// By default the cpp-sdk marks the UserAgent as ConfigCat-Cpp, we are going to override it with ConfigCat-Unreal
	GetRequest->SetHeader(UserAgentHeaderName, UserAgentVersion);

	const FString Url = UTF8_TO_TCHAR(url.c_str());
	GetRequest->SetURL(Url);

	if (proxies.empty() != 0)
	{
		UE_LOG(LogConfigCat, Warning, TEXT("Unreal Engine doesn't have a built-in proxy for HTTPS requests, ignoring proxies."));
	}

#ifndef CONFIGCAT_HTTPTHREAD_WORKAROUND
	GetRequest->SetDelegateThreadPolicy(EHttpRequestDelegateThreadPolicy::CompleteOnHttpThread);
#endif
	GetRequest->ProcessRequest();

	while (GetRequest->GetStatus() == EHttpRequestStatus::Processing)
	{
		constexpr float SleepInterval = 0.05f;
		UE_LOG(LogConfigCat, Verbose, TEXT("Waiting for Get response (IsGameThread: %s). Retrying in %s second."), *LexToString(IsInGameThread()), *LexToString(SleepInterval));

		// The cpp-sdk excepts a sync request, so this function will block execution until the HTTP request is finished, therefore:
		// - for requests running on the main thread (game thread), we need to manually tick the HTTP Module to process the request
		// - for requests running on any other thread, we just wait until for the HTTP module to process the request
		if (IsInGameThread())
		{
			FHttpModule::Get().GetHttpManager().Tick(SleepInterval);
		}

		FPlatformProcess::Sleep(SleepInterval);
	}

	const FHttpResponsePtr GetResponse = GetRequest->GetResponse();
	Response Response;
	if (!GetResponse)
	{
		Response.error = "Unreal Engine Network Adapter failed to launch request. Check logs";
		Response.errorCode = ResponseErrorCode::InternalError;
		return Response;
	}

	Response.text = TCHAR_TO_UTF8(*GetResponse->GetContentAsString());
	Response.statusCode = GetResponse->GetResponseCode();

	for (const FString& Header : GetResponse->GetAllHeaders())
	{
		FString HeaderKey;
		FString HeaderValue;
		if (Header.Split(TEXT(":"), &HeaderKey, &HeaderValue))
		{
			const std::string KeyString = TCHAR_TO_UTF8(*HeaderKey);
			const std::string KeyValue = TCHAR_TO_UTF8(*HeaderValue);
			Response.header[KeyString] = KeyValue;
		}
	}

	return Response;
}

void ConfigCatNetworkAdapter::close()
{
	UE_LOG(LogConfigCat, Verbose, TEXT("Network Adapter canceling on-going requests."));

	if (GetRequest && GetRequest->GetStatus() == EHttpRequestStatus::Processing)
	{
		GetRequest->CancelRequest();
	}
}