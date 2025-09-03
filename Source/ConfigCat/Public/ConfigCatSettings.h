﻿// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
#include <Engine/DeveloperSettings.h>

#include "ConfigCatSettings.generated.h"

USTRUCT()
struct FProxyAuthentication
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Proxy)
	FString User;

	UPROPERTY(EditAnywhere, Category = Proxy)
	FString Password;
};

UENUM()
enum class EDataGovernance : uint8
{
	EuOnly,
	Global,
};

UENUM()
enum class EPollingMode : uint8
{
	Auto,
	LazyLoad,
	ManualPoll,
};

UENUM()
enum class EOverrideMode : uint8
{
	None,
	File,
	Map
};

UENUM()
enum class EOverrideBehaviour : uint8
{
	LocalOnly,
	LocalOverRemote,
	RemoteOverLocal
};

/**
 * Holds configuration for integrating the ConfigCat feature flags SDK
 */
UCLASS(DefaultConfig, Config = ConfigCat, meta = (DisplayName = "ConfigCat Settings"))
class CONFIGCAT_API UConfigCatSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/**
	 * SDK Key to access your feature flags and configurations. Get it from ConfigCat Dashboard.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Integration")
	FString SdkKey = TEXT("");
	/**
	 * The base ConfigCat CDN url.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client")
	FString BaseUrl = TEXT("");
	/**
	 * Set this parameter to be in sync with the Data Governance preference on the [Dashboard](https://app.configcat.com/organization/data-governance).
	 * Only Organization Admins have access
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client")
	EDataGovernance DataGovernance = EDataGovernance::Global;
	/**
	 * The number of milliseconds to wait for the server to make the initial connection
	 * 0 means it never times out during transfer
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client", meta = (DisplayName = "Connection Timeout (in milliseconds)", ClampMin = "0", UIMin = "0", ForceUnits = "ms"))
	uint32 ConnectionTimeoutMs = 8000;
	/**
	 * The number of milliseconds to wait for the server to respond before giving up
	 * 0 means it never times out during transfer
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client", meta = (DisplayName = "Read Timeout (in milliseconds)", ClampMin = "0", UIMin = "0", ForceUnits = "ms"))
	uint32 ReadTimeoutMs = 5000;
	/**
	 * The polling mode.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client")
	EPollingMode PollingMode;
	/**
	 * Sets at least how often this policy should fetch the latest configuration and refresh the cache.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client", meta = (DisplayName = "Auto Poll Interval (in seconds)", EditCondition = "PollingMode == EPollingMode::Auto", EditConditionHides, ClampMin = "0", UIMin = "0", ForceUnits = "s"))
	uint32 AutoPollIntervalSeconds = 60;
	/**
	 * Sets the maximum waiting time between initialization and the first config acquisition in seconds.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client", meta = (DisplayName = "Maximum Inititial Wait Time (in seconds)", EditCondition = "PollingMode == EPollingMode::Auto", EditConditionHides, ClampMin = "0", UIMin = "0", ForceUnits = "s"))
	uint32 MaxInitWaitTimeSeconds = 5;
	/**
	 * Sets how long the cache will store its value before fetching the latest from the network again.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client", meta = (DisplayName = "Cache Refresh Interval (in seconds)", EditCondition = "PollingMode == EPollingMode::LazyLoad", EditConditionHides, ClampMin = "0", UIMin = "0", ForceUnits = "s"))
	uint32 CacheRefreshIntervalSeconds = 60;
	/**
	 * Proxy addresses. e.g. { "https": "your_proxy_ip:your_proxy_port" }
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Proxy")
	TMap<FString, FString> Proxies;
	/**
	 * Proxy authentication.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Proxy")
	TMap<FString, FProxyAuthentication> ProxyAuthentications;
	/**
	 * Indicates whether the SDK should be initialized in offline mode or not.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client")
	bool bStartOffline;
	/**
	 * Specifies the data source for overrides if any
	 */
	UPROPERTY(Config, EditAnywhere, Category= "ConfigCat|Override")
	EOverrideMode OverrideMode;
	/**
	 * Specifies how the overrides should apply over the downloaded values
	 */
	UPROPERTY(Config, EditAnywhere, Category= "ConfigCat|Override", meta = (EditCondition = "OverrideMode != EOverrideMode::None", EditConditionHides))
	EOverrideBehaviour OverrideBehaviour;
	/**
	 * Automatically initialization the SDK client. You can disable it if you want to manually initialize at a later stage.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Subsystem")
	bool bAutoInitialize = true;

private:
	// Begin UDeveloperSettings interface
	virtual FName GetContainerName() const override;
	virtual FName GetCategoryName() const override;
	virtual FName GetSectionName() const override;
#if WITH_EDITOR
	virtual FText GetSectionText() const override;
#endif
	// End UDeveloperSettings interface
};
