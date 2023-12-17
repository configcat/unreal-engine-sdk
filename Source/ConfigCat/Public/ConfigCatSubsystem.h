// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>

#include "Wrapper/ConfigCatSetting.h"
#include "Wrapper/ConfigCatUser.h"

#include "ConfigCatSubsystem.generated.h"

struct FConfigCatEvaluationDetails;
namespace configcat
{
	struct ConfigCatOptions;
	class ConfigCatClient;
	class ConfigCatUser;
} // namespace configcat

using FOnClientReady = FSimpleMulticastDelegate;
using FOnConfigChanged = TMulticastDelegate<void(const FConfigCatConfig& Config)>;
using FOnFlagEvaluated = TMulticastDelegate<void(const FConfigCatEvaluationDetails& Details)>;
using FOnError = TMulticastDelegate<void(const FString& Error)>;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClientReadyBP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfigChangedBp, const FConfigCatConfig&, Config);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFlagEvaluatedBp, const FConfigCatEvaluationDetails&, Details);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnErrorBp, const FString&, Error);

/**
 * Wrapper for accessing the configcat client. This subsystem is responsible for initializing and managing the client's lifecycle.
 */
UCLASS()
class CONFIGCAT_API UConfigCatSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/**
	 * Static wrapper for getting this GameInstance subsystem
	 */
	static UConfigCatSubsystem* Get(const UObject* WorldContext);

	/**
	 * Gets a feature flag of boolean value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Value (Boolean)", Category = "ConfigCat", meta = (AdvancedDisplay = "bDefaultValue, User", AutoCreateRefTerm = "User"))
	bool GetBoolValue(const FString& Key, bool bDefaultValue, const FConfigCatUser& User = FConfigCatUser()) const;
	/**
	 * Gets a feature flag of integer value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Value (Integer)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	int32 GetIntValue(const FString& Key, int32 DefaultValue, const FConfigCatUser& User = FConfigCatUser()) const;
	/**
	 * Gets a feature flag of decimal (double) value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Value (Double)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	double GetDoubleValue(const FString& Key, double DefaultValue, const FConfigCatUser& User = FConfigCatUser()) const;
	/**
	 * Gets a feature flag of string value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Value (String)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	FString GetStringValue(const FString& Key, const FString& DefaultValue, const FConfigCatUser& User = FConfigCatUser()) const;
	/**
	 * Gets a feature flag of variant value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Config Value", Category = "ConfigCat", meta = (AdvancedDisplay = "User", AutoCreateRefTerm = "User"))
	FConfigCatValue GetConfigValue(const FString& Key, const FConfigCatUser& User = FConfigCatUser()) const;
	/**
	 * Gets the evaluation details of a feature flag of bool value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Value Details(Boolean)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	FConfigCatEvaluationDetails GetBoolValueDetails(const FString& Key, bool DefaultValue, const FConfigCatUser& User = FConfigCatUser()) const;
	/**
	 * Gets the evaluation details of a feature flag of integer value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Value Details(Integer)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	FConfigCatEvaluationDetails GetIntValueDetails(const FString& Key, int DefaultValue, const FConfigCatUser& User = FConfigCatUser()) const;
	/**
	 * Gets the evaluation details of a feature flag of decimal (double) value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Value Details(Double)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	FConfigCatEvaluationDetails GetDoubleValueDetails(const FString& Key, double DefaultValue, const FConfigCatUser& User = FConfigCatUser()) const;
	/**
	 * Gets the evaluation details of a feature flag of string value for a specific key. Optionally takes in a target user.
	 */
	UFUNCTION(BlueprintPure, DisplayName = "Get Value Details(String)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	FConfigCatEvaluationDetails GetStringValueDetails(const FString& Key, const FString& DefaultValue, const FConfigCatUser& User = FConfigCatUser()) const;
	/**
	 * Gets all the setting keys.
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat")
	TArray<FString> GetAllKeys() const;
	/**
	 * Gets the key of a setting and it's value identified by the given Variation ID (analytics)
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat")
	bool GetKeyAndValue(const FString& VariationId, FString& OutKey, FConfigCatValue& OutValue) const;
	/**
	 * Gets the values of all feature flags or settings.
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat", meta = (AdvancedDisplay = "User", AutoCreateRefTerm = "User"))
	TMap<FString, FConfigCatValue> GetAllValues(const FConfigCatUser& User = FConfigCatUser()) const;
	/**
	 * Gets the values along with evaluation details of all feature flags and settings.
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat", meta = (AdvancedDisplay = "User", AutoCreateRefTerm = "User"))
	TArray<FConfigCatEvaluationDetails> GetAllValueDetails(const FConfigCatUser& User = FConfigCatUser()) const;
	/**
	 * Initiates a force refresh synchronously on the cached configuration.
	 */
	UFUNCTION(BlueprintCallable, Category = "ConfigCat")
	void ForceRefresh();
	/**
	 * Sets the default user.
	 */
	UFUNCTION(BlueprintCallable, Category = "ConfigCat")
	void SetDefaultUser(const FConfigCatUser& User = FConfigCatUser());
	/**
	 * Sets the default user to nullptr.
	 */
	UFUNCTION(BlueprintCallable, Category = "ConfigCat")
	void ClearDefaultUser();
	/**
	 * Configures the SDK to allow HTTP requests.
	 */
	UFUNCTION(BlueprintCallable, Category = "ConfigCat")
	void SetOnline();
	/**
	 * Configures the SDK to not initiate HTTP requests and work only from its cache.
	 */
	UFUNCTION(BlueprintCallable, Category = "ConfigCat")
	void SetOffline();
	/**
	 * true when the SDK is configured not to initiate HTTP requests, otherwise false.
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat")
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
	 * Internal pointer to the configcat client singleton.
	 */
	configcat::ConfigCatClient* ConfigCatClient;
};
