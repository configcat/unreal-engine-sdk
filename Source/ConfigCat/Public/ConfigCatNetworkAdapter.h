// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ConfigCatCppSDK/Include/httpsessionadapter.h>
#include <Interfaces/IHttpRequest.h>

namespace configcat
{
	class PollingMode;
}

/**
 * Implementation of the configcat::HttpSessionAdapter so we can handle HTTP requests directly inside Unreal
 */
class ConfigCatNetworkAdapter : public configcat::HttpSessionAdapter
{
public:
	explicit ConfigCatNetworkAdapter(const std::shared_ptr<configcat::PollingMode>& InPollingMode);
	virtual ~ConfigCatNetworkAdapter() override = default;

private:
	// Begin configcat::HttpSessionAdapter interface
	virtual bool init(uint32_t connectTimeoutMs, uint32_t readTimeoutMs) override;
	virtual configcat::Response
	get(const std::string& url,
	    const std::map<std::string, std::string>& header,
	    const std::map<std::string, std::string>& proxies,
	    const std::map<std::string, configcat::ProxyAuthentication>& proxyAuthentications) override;
	virtual void close() override;
	// End configcat::HttpSessionAdapter interface
	/*
	 * The number of milliseconds to wait for the server to make the initial connection
	 */
	int32 ConnectionTimeout = 0;
	/*
	 * The number of milliseconds to wait for the server to respond before giving up.
	 */
	int32 ReadTimeout = 0;
	/**
	 * HTTP request currently being executed
	 */
	FHttpRequestPtr GetRequest;
	/**
	 * Value used for the HTTP request header field X-ConfigCat-UserAgent
	 */
	FString UserAgentVersion;
};