// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "ConfigCatSubsystem.generated.h"


struct FConfigCatSetting;
struct FConfigCatEvaluationDetails;
namespace configcat
{
	class ConfigCatClient;
	class ConfigCatUser;
} // namespace configcat


// TODO: Create blueprint version of all events.
using FOnClientReady = FSimpleMulticastDelegate;
using FOnConfigChanged = TMulticastDelegate<void(TMap<FString, FConfigCatSetting>)>;
using FOnFlagEvaluated = TMulticastDelegate<void(const FConfigCatEvaluationDetails& Details)>;
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

	UFUNCTION(BlueprintPure, DisplayName = "Get Value (Boolean)", Category = "ConfigCat", meta = (AdvancedDisplay = "bDefaultValue, User", AutoCreateRefTerm = "User"))
	bool GetBoolValue(const FString& Key, bool bDefaultValue, const FConfigCatUser& User) const;

	UFUNCTION(BlueprintPure, DisplayName = "Get Value (Integer)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	int32 GetIntValue(const FString& Key, int32 DefaultValue, const FConfigCatUser& User) const;

	UFUNCTION(BlueprintPure, DisplayName = "Get Value (Double)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	double GetDoubleValue(const FString& Key, double DefaultValue, const FConfigCatUser& User) const;

	UFUNCTION(BlueprintPure, DisplayName = "Get Value (String)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	FString GetStringValue(const FString& Key, const FString& DefaultValue, const FConfigCatUser& User) const;

	UFUNCTION(BlueprintPure, DisplayName = "Get Config Value", Category = "ConfigCat", meta = (AdvancedDisplay = "User", AutoCreateRefTerm = "User"))
	FConfigCatValue GetConfigValue(const FString& Key, const FConfigCatUser& User) const;

	UFUNCTION(BlueprintPure, DisplayName = "Get Value Details(Boolean)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	FConfigCatEvaluationDetails GetBoolValueDetails(const FString& Key, bool DefaultValue, const FConfigCatUser& User) const;

	UFUNCTION(BlueprintPure, DisplayName = "Get Value Details(Integer)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	FConfigCatEvaluationDetails GetIntValueDetails(const FString& Key, int DefaultValue, const FConfigCatUser& User) const;

	UFUNCTION(BlueprintPure, DisplayName = "Get Value Details(Double)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	FConfigCatEvaluationDetails GetDoubleValueDetails(const FString& Key, double DefaultValue, const FConfigCatUser& User) const;

	UFUNCTION(BlueprintPure, DisplayName = "Get Value Details(String)", Category = "ConfigCat", meta = (AdvancedDisplay = "DefaultValue, User", AutoCreateRefTerm = "User"))
	FConfigCatEvaluationDetails GetStringValueDetails(const FString& Key, const FString& DefaultValue, const FConfigCatUser& User) const;

	UFUNCTION(BlueprintPure, Category = "ConfigCat")
	TArray<FString> GetAllKeys() const;

	UFUNCTION(BlueprintPure, Category = "ConfigCat")
	bool GetKeyAndValue(const FString& VariationId, FString& OutKey, FConfigCatValue& OutValue) const;

	UFUNCTION(BlueprintPure, Category = "ConfigCat", meta = (AdvancedDisplay = "User", AutoCreateRefTerm = "User"))
	TMap<FString, FConfigCatValue> GetAllValues(const FConfigCatUser& User) const;

	UFUNCTION(BlueprintPure, Category = "ConfigCat", meta = (AdvancedDisplay = "User", AutoCreateRefTerm = "User"))
	TArray<FConfigCatEvaluationDetails> GetAllValueDetails(const FConfigCatUser& User) const;

	UFUNCTION(BlueprintCallable, Category = "ConfigCat")
	void ForceRefresh();

	UFUNCTION(BlueprintCallable, Category = "ConfigCat")
	void SetDefaultUser(const FConfigCatUser& User);

	UFUNCTION(BlueprintCallable, Category = "ConfigCat")
	void ClearDefaultUser();

	UFUNCTION(BlueprintCallable, Category = "ConfigCat")
	void SetOnline();

	UFUNCTION(BlueprintCallable, Category = "ConfigCat")
	void SetOffline();

	UFUNCTION(BlueprintPure, Category = "ConfigCat")
	bool IsOffline() const;

	// TODO: Expose these to blueprints
	FOnClientReady OnClientReady;
	FOnConfigChanged OnConfigChanged;
	FOnFlagEvaluated OnFeatureLevelChanged;
	FOnError OnError;

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	configcat::ConfigCatClient* ConfigCatClient;
};
