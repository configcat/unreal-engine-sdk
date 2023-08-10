// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "ConfigCatSubsystem.generated.h"

namespace configcat
{
	class ConfigCatClient;
	class ConfigCatUser;
} // namespace configcat


// TODO: Create blueprint version of all events.
using FOnClientReady = FSimpleMulticastDelegate;
using FOnConfigChanged = TMulticastDelegate<void()>; // TODO: Translate type from config cat
using FOnFlagEvaluated = TMulticastDelegate<void()>; // TODO: Translate type from config cat
using FOnError = TMulticastDelegate<void(const FString& Error)>;

/**
 *
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

	UFUNCTION(BlueprintCallable, DisplayName = "Get Value (Boolean)", Category = "ConfigCat", meta = (AdvancedDisplay = "bDefaultValue, User", AutoCreateRefTerm = "User"))
	bool GetBoolValue(const FString& Key, bool bDefaultValue, const FConfigCatUser& User);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Value (Integer)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	int32 GetIntValue(const FString& Key, int32 DefaultValue, const FConfigCatUser& User);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Value (Double)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	double GetDoubleValue(const FString& Key, double DefaultValue, const FConfigCatUser& User);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Value (String)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	FString GetStringValue(const FString& Key, FString DefaultValue, const FConfigCatUser& User);

	// std::shared_ptr<Value> getValue(const std::string& key, const ConfigCatUser* user = nullptr) const;
	// EvaluationDetails getValueDetails(const std::string& key, bool defaultValue, const ConfigCatUser* user = nullptr) const;
	// EvaluationDetails getValueDetails(const std::string& key, int defaultValue, const ConfigCatUser* user = nullptr) const;
	// EvaluationDetails getValueDetails(const std::string& key, double defaultValue, const ConfigCatUser* user = nullptr) const;
	// EvaluationDetails getValueDetails(const std::string& key, const std::string& defaultValue, const ConfigCatUser* user = nullptr) const;
	// EvaluationDetails getValueDetails(const std::string& key, const char* defaultValue, const ConfigCatUser* user = nullptr) const;

	TArray<FString> GetAllKeys() const;

	// std::shared_ptr<KeyValue> getKeyAndValue(const std::string& variationId) const;
	// std::unordered_map<std::string, Value> getAllValues(const ConfigCatUser* user = nullptr) const;
	// std::vector<EvaluationDetails> getAllValueDetails(const ConfigCatUser* user = nullptr) const;

	void ForceRefresh();

	void SetDefaultUser(const FConfigCatUser& User);
	void ClearDefaultUser();

	void SetOnline();
	void SetOffline();
	bool IsOffline() const;

	FOnClientReady OnClientReady;
	FOnError OnError;

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	configcat::ConfigCatClient* ConfigCatClient;
};
