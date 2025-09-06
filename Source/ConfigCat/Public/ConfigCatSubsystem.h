// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>

#include <memory>
#include <string>

#include "Wrappers/ConfigCatSettingValueContainerWrapper.h"
#include "Wrappers/ConfigCatUserWrapper.h"

#include "ConfigCatSubsystem.generated.h"

class UConfigCatSettingsWrapper;
class UConfigCatEvaluationWrapper;
class UConfigCatValueWrapper;

namespace configcat
{
	struct ConfigCatOptions;
	class ConfigCatClient;
} // namespace configcat

using FOnClientReady = FSimpleMulticastDelegate;
using FOnConfigChanged = TMulticastDelegate<void(UConfigCatSettingsWrapper* Config)>;
using FOnFlagEvaluated = TMulticastDelegate<void(UConfigCatEvaluationWrapper* Details)>;
using FOnError = TMulticastDelegate<void(const FString& Error, const FString& Exception)>;
using FOnConfigureOptions = TMulticastDelegate<void(configcat::ConfigCatOptions& Options)>;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClientReadyBP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfigChangedBp, UConfigCatSettingsWrapper*, Config);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFlagEvaluatedBp, UConfigCatEvaluationWrapper*, Details);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnErrorBp, const FString&, Error, const FString&, Exception);

/**
 * Wrapper for accessing the configcat client. This subsystem is responsible for initializing and managing the client's lifecycle.
 */
UCLASS(meta = (DisplayName = "ConfigCat Subsystem"))
class CONFIGCAT_API UConfigCatSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/**
	 * Static wrapper for getting this GameInstance subsystem
	 */
	static UConfigCatSubsystem* Get(const UObject* WorldContext);

	/**
	 * Performs the initialization of the SDK. See bAutoInitialize flag in the settings.
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Manual Initialization", Category = "FeatureFlags", meta = (Keywords = "ConfigCat"))
	void PerformInitialize();
	/**
	 * Gets a feature flag of boolean value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Value (Boolean)", Category = "FeatureFlags", meta = (Keywords = "ConfigCat", AdvancedDisplay = "bDefaultValue, User", AutoCreateRefTerm = "User"))
	bool GetBoolValue(const FString& Key, bool bDefaultValue, const UConfigCatUserWrapper* User = nullptr) const;
	/**
	 * Gets a feature flag of integer value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Value (Integer)", Category = "FeatureFlags", meta = (Keywords = "ConfigCat", AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	int32 GetIntValue(const FString& Key, int32 DefaultValue, const UConfigCatUserWrapper* User = nullptr) const;
	/**
	 * Gets a feature flag of decimal (double) value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Value (Double)", Category = "FeatureFlags", meta = (Keywords = "ConfigCat", AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	double GetDoubleValue(const FString& Key, double DefaultValue, const UConfigCatUserWrapper* User = nullptr) const;
	/**
	 * Gets a feature flag of string value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Value (String)", Category = "FeatureFlags", meta = (Keywords = "ConfigCat", AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	FString GetStringValue(const FString& Key, const FString& DefaultValue, const UConfigCatUserWrapper* User = nullptr) const;
	/**
	 * Gets a feature flag of variant value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Config Value", Category = "FeatureFlags", meta = (Keywords = "ConfigCat", AdvancedDisplay = "User", AutoCreateRefTerm = "User"))
	UConfigCatValueWrapper* GetConfigValue(const FString& Key, const UConfigCatUserWrapper* User = nullptr) const;
	/**
	 * Gets the evaluation details of a feature flag of bool value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Value Details(Boolean)", Category = "FeatureFlags", meta = (Keywords = "ConfigCat", AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	UConfigCatEvaluationWrapper* GetBoolValueDetails(const FString& Key, bool DefaultValue, const UConfigCatUserWrapper* User = nullptr) const;
	/**
	 * Gets the evaluation details of a feature flag of integer value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Value Details(Integer)", Category = "FeatureFlags", meta = (Keywords = "ConfigCat", AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	UConfigCatEvaluationWrapper* GetIntValueDetails(const FString& Key, int DefaultValue, const UConfigCatUserWrapper* User = nullptr) const;
	/**
	 * Gets the evaluation details of a feature flag of decimal (double) value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Value Details(Double)", Category = "FeatureFlags", meta = (Keywords = "ConfigCat", AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	UConfigCatEvaluationWrapper* GetDoubleValueDetails(const FString& Key, double DefaultValue, const UConfigCatUserWrapper* User = nullptr) const;
	/**
	 * Gets the evaluation details of a feature flag of string value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Value Details(String)", Category = "FeatureFlags", meta = (Keywords = "ConfigCat", AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	UConfigCatEvaluationWrapper* GetStringValueDetails(const FString& Key, const FString& DefaultValue, const UConfigCatUserWrapper* User = nullptr) const;
	/**
	 * Gets all the setting keys.
	 */
	UFUNCTION(BlueprintPure, Category = "FeatureFlags", meta = (Keywords = "ConfigCat"))
	TArray<FString> GetAllKeys() const;
	/**
	 * Gets the key of a setting and it's value identified by the given Variation ID (analytics)
	 */
	UFUNCTION(BlueprintPure, Category = "FeatureFlags", meta = (Keywords = "ConfigCat"))
	bool GetKeyAndValue(const FString& VariationId, FString& OutKey, UConfigCatValueWrapper*& OutValue) const;
	/**
	 * Gets the values of all feature flags or settings.
	 */
	UFUNCTION(BlueprintPure, Category = "FeatureFlags", meta = (Keywords = "ConfigCat", AdvancedDisplay = "User", AutoCreateRefTerm = "User"))
	TMap<FString, UConfigCatValueWrapper*> GetAllValues(const UConfigCatUserWrapper* User = nullptr) const;
	/**
	 * Gets the values along with evaluation details of all feature flags and settings.
	 */
	UFUNCTION(BlueprintPure, Category = "FeatureFlags", meta = (Keywords = "ConfigCat", AdvancedDisplay = "User", AutoCreateRefTerm = "User"))
	TArray<UConfigCatEvaluationWrapper*> GetAllValueDetails(const UConfigCatUserWrapper* User = nullptr) const;
	/**
	 * Initiates a force refresh synchronously on the cached configuration.
	 */
	UFUNCTION(BlueprintCallable, Category = "FeatureFlags", meta = (Keywords = "ConfigCat"))
	void ForceRefresh();
	/**
	 * Sets the default user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Targeting", meta = (Keywords = "ConfigCat"))
	void SetDefaultUser(const UConfigCatUserWrapper* User = nullptr);
	/**
	 * Sets the default user to nullptr.
	 */
	UFUNCTION(BlueprintCallable, Category = "Targeting", meta = (Keywords = "ConfigCat"))
	void ClearDefaultUser();
	/**
	 * Configures the SDK to allow HTTP requests.
	 */
	UFUNCTION(BlueprintCallable, Category = "Connection", meta = (Keywords = "ConfigCat"))
	void SetOnline();
	/**
	 * Configures the SDK to not initiate HTTP requests and work only from its cache.
	 */
	UFUNCTION(BlueprintCallable, Category = "Connection", meta = (Keywords = "ConfigCat"))
	void SetOffline();
	/**
	 * true when the SDK is configured not to initiate HTTP requests, otherwise false.
	 */
	UFUNCTION(BlueprintPure, Category = "Connection", meta = (Keywords = "ConfigCat"))
	bool IsOffline() const;
	/**
	 * Executed when the configcat client is fully initialized.
	 */
	FOnClientReady OnClientReady;
	/**
	 * Executed when the configcat client is fully initialized.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnClientReadyBP OnClientReadyBP;
	/**
	 * Executed when the configcat client received an updated config.
	 */
	FOnConfigChanged OnConfigChanged;
	/**
	 * Executed when the configcat client received an updated config.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnConfigChangedBp OnConfigChangedBp;
	/**
	 * Executed when the configcat client evaluated a feature flag.
	 */
	FOnFlagEvaluated OnFlagEvaluated;
	/**
	 * Executed when the configcat client evaluated a feature flag.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnFlagEvaluatedBp OnFlagEvaluatedBp;
	/**
	 * Executed when the configcat client encounters an error.
	 */
	FOnError OnError;
	/**
	 * Executed when the configcat client encounters an error.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnErrorBp OnErrorBp;
	/**
	 * Allows customization of the initializations options before the client is created.
	 */
	FOnConfigureOptions OnConfigureOptions;	

private:
	// Begin UGameInstanceSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End UGameInstanceSubsystem interface
	/**
	 * Sets up the ConfigCatOptions to bind the subsystem's delegates.
	 */
	void SetupClientHooks(configcat::ConfigCatOptions& Options);
	/**
	 *Sets up the ConfigCatOptions to use the appropriate overrides based on plugin settings.
	 */
	void SetupClientOverrides(configcat::ConfigCatOptions& Options);
	/**
	 * Callback executed when the native configcat client encounters an error.
	 */
	void OnErrorHook(const std::string& Error, const std::exception_ptr& Exception);
	/**
	 * Callback executed when the native configcat client is ready.
	 */
	void OnClientReadyHook();
	/**
	 * Callback executed when the native configcat client receives a new configuration.
	 */
	void OnConfigChangedHook(const std::shared_ptr<const configcat::Settings>& InConfig);
	/**
	 * Internal pointer to the configcat client singleton.
	 */
	std::shared_ptr<configcat::ConfigCatClient> ConfigCatClient;
};
