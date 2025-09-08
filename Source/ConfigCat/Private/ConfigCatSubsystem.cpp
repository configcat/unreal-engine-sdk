// Copyright (c) ConfigCat 2024. All Rights Reserved.

#include "ConfigCatSubsystem.h"

#include <ThirdParty/ConfigCatCppSDK/Include/configcat.h>
#include <ThirdParty/ConfigCatCppSDK/Include/configcatclient.h>
#include <ThirdParty/ConfigCatCppSDK/Include/fileoverridedatasource.h>
#include <ThirdParty/ConfigCatCppSDK/Include/mapoverridedatasource.h>
#include <Async/Async.h>
#include <HAL/FileManager.h>
#include <HAL/PlatformFileManager.h>
#include <Kismet/GameplayStatics.h>
#include <Logging/LogVerbosity.h>
#include <Misc/ConfigCacheIni.h>
#include <Engine/GameInstance.h>
#include <Engine/Engine.h>

#include "ConfigCat.h"
#include "ConfigCatLog.h"
#include "ConfigCatLogger.h"
#include "ConfigCatNetworkAdapter.h"
#include "ConfigCatSettings.h"

#include "Wrappers/ConfigCatSettingsWrapper.h"
#include "Wrappers/ConfigCatEvaluationWrapper.h"
#include "Wrappers/ConfigCatValueWrapper.h"

using namespace configcat;

namespace
{
	void PrintError(const FString& ErrorMessage)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("[ConfigCat] %s"), *ErrorMessage));
		}
		UE_LOG(LogConfigCat, Error, TEXT("%s"), *ErrorMessage);
	}

	bool EnsureConfigCatClient(const std::shared_ptr<configcat::ConfigCatClient>& Client)
	{
		if (Client)
		{
			return true;
		}

		PrintError(TEXT("Trying to access the client before initialization or after shutdown."));
		return false;
	}

	template <typename T>
	T GetValue(const std::shared_ptr<ConfigCatClient>& Client, FString Key, T DefaultValue, const UConfigCatUserWrapper* User)
	{
		if (!EnsureConfigCatClient(Client))
		{
			return DefaultValue;
		}

		const std::string& FlagKey = TCHAR_TO_UTF8(*Key);

		return Client->getValue(FlagKey, DefaultValue, User ? User->User : nullptr);
	}

	template <typename T>
	UConfigCatEvaluationWrapper* GetEvaluationDetails(const std::shared_ptr<ConfigCatClient>& Client, FString Key, T DefaultValue, const UConfigCatUserWrapper* User)
	{
		if (!EnsureConfigCatClient(Client))
		{
			return {};
		}

		const std::string& FlagKey = TCHAR_TO_UTF8(*Key);

		return UConfigCatEvaluationWrapper::CreateEvaluation(Client->getValueDetails(FlagKey, DefaultValue, User ? User->User : nullptr));
	}


} // namespace

UConfigCatSubsystem* UConfigCatSubsystem::Get(const UObject* WorldContext)
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContext);
	return GameInstance->GetSubsystem<UConfigCatSubsystem>();
}

bool UConfigCatSubsystem::GetBoolValue(const FString& Key, bool bDefaultValue, const UConfigCatUserWrapper* User) const
{
	return GetValue(ConfigCatClient, Key, bDefaultValue, User);
}

int32 UConfigCatSubsystem::GetIntValue(const FString& Key, int32 DefaultValue, const UConfigCatUserWrapper* User) const
{
	return GetValue(ConfigCatClient, Key, DefaultValue, User);
}

double UConfigCatSubsystem::GetDoubleValue(const FString& Key, double DefaultValue, const UConfigCatUserWrapper* User) const
{
	return GetValue(ConfigCatClient, Key, DefaultValue, User);
}

FString UConfigCatSubsystem::GetStringValue(const FString& Key, const FString& DefaultValue, const UConfigCatUserWrapper* User) const
{
	UE_LOG(LogConfigCat, Display, TEXT("Request %s feature flag from configcat cpp-sdk"), *Key);
	const std::string& StringDefaultValue = TCHAR_TO_UTF8(*DefaultValue);
	const std::string& StringResult = GetValue(ConfigCatClient, Key, StringDefaultValue, User);
	return UTF8_TO_TCHAR(StringResult.c_str());
}

UConfigCatValueWrapper* UConfigCatSubsystem::GetConfigValue(const FString& Key, const UConfigCatUserWrapper* User) const
{
	if (!EnsureConfigCatClient(ConfigCatClient))
	{
		return {};
	}

	const std::string& FlagKey = TCHAR_TO_UTF8(*Key);
	const std::optional<Value> FeatureFlagValue = ConfigCatClient->getValue(FlagKey, User ? User->User : nullptr);

	return UConfigCatValueWrapper::CreateValue(FeatureFlagValue);
}

UConfigCatEvaluationWrapper* UConfigCatSubsystem::GetBoolValueDetails(const FString& Key, bool DefaultValue, const UConfigCatUserWrapper* User) const
{
	return GetEvaluationDetails(ConfigCatClient, Key, DefaultValue, User);
}

UConfigCatEvaluationWrapper* UConfigCatSubsystem::GetIntValueDetails(const FString& Key, int DefaultValue, const UConfigCatUserWrapper* User) const
{
	return GetEvaluationDetails(ConfigCatClient, Key, DefaultValue, User);
}

UConfigCatEvaluationWrapper* UConfigCatSubsystem::GetDoubleValueDetails(const FString& Key, double DefaultValue, const UConfigCatUserWrapper* User) const
{
	return GetEvaluationDetails(ConfigCatClient, Key, DefaultValue, User);
}

UConfigCatEvaluationWrapper* UConfigCatSubsystem::GetStringValueDetails(const FString& Key, const FString& DefaultValue, const UConfigCatUserWrapper* User) const
{
	const std::string& StringDefaultValue = TCHAR_TO_UTF8(*DefaultValue);
	return GetEvaluationDetails(ConfigCatClient, Key, StringDefaultValue, User);
}

TArray<FString> UConfigCatSubsystem::GetAllKeys() const
{
	if (!EnsureConfigCatClient(ConfigCatClient))
	{
		return {};
	}

	const std::vector<std::string> Keys = ConfigCatClient->getAllKeys();

	TArray<FString> Result;
	for (const std::string& Key : Keys)
	{
		Result.Emplace(UTF8_TO_TCHAR(Key.c_str()));
	}

	return Result;
}

bool UConfigCatSubsystem::GetKeyAndValue(const FString& VariationId, FString& OutKey, UConfigCatValueWrapper*& OutValue) const
{
	if (!EnsureConfigCatClient(ConfigCatClient))
	{
		return false;
	}

	const std::string& VariationIdString = TCHAR_TO_UTF8(*VariationId);

	std::optional<KeyValue> KeyValue = ConfigCatClient->getKeyAndValue(VariationIdString);

	if (!KeyValue)
	{
		return false;
	}

	OutKey = UTF8_TO_TCHAR(KeyValue->key.c_str());
	OutValue = UConfigCatValueWrapper::CreateValue(KeyValue->value);
	return true;
}

TMap<FString, UConfigCatValueWrapper*> UConfigCatSubsystem::GetAllValues(const UConfigCatUserWrapper* User) const
{
	if (!EnsureConfigCatClient(ConfigCatClient))
	{
		return {};
	}

	const std::unordered_map<std::string, Value> Values = ConfigCatClient->getAllValues(User ? User->User : nullptr);

	TMap<FString, UConfigCatValueWrapper*> Result;
	for (const std::pair<const std::string, Value>& Value : Values)
	{
		Result.Emplace(UTF8_TO_TCHAR(Value.first.c_str()), UConfigCatValueWrapper::CreateValue(Value.second));
	}

	return Result;
}

TArray<UConfigCatEvaluationWrapper*> UConfigCatSubsystem::GetAllValueDetails(const UConfigCatUserWrapper* User) const
{
	if (!EnsureConfigCatClient(ConfigCatClient))
	{
		return {};
	}

	const std::vector<EvaluationDetails<Value>> ValueDetails = ConfigCatClient->getAllValueDetails(User ? User->User : nullptr);

	TArray<UConfigCatEvaluationWrapper*> Result;
	for (const EvaluationDetails<Value>& ValueDetail : ValueDetails)
	{
		Result.Emplace(UConfigCatEvaluationWrapper::CreateEvaluation(ValueDetail));
	}

	return Result;
}

void UConfigCatSubsystem::ForceRefresh()
{
	if (!EnsureConfigCatClient(ConfigCatClient))
	{
		return;
	}

	ConfigCatClient->forceRefresh();
}

void UConfigCatSubsystem::SetDefaultUser(const UConfigCatUserWrapper* User)
{
	if (!EnsureConfigCatClient(ConfigCatClient))
	{
		return;
	}
	if (!User || !User->User)
	{
		UE_LOG(LogConfigCat, Warning, TEXT("Trying to set Default User with invalid pointer."));
		return;
	}

	ConfigCatClient->setDefaultUser(User->User);
}

void UConfigCatSubsystem::ClearDefaultUser()
{
	if (!EnsureConfigCatClient(ConfigCatClient))
	{
		return;
	}

	ConfigCatClient->clearDefaultUser();
}

void UConfigCatSubsystem::SetOnline()
{
	if (!EnsureConfigCatClient(ConfigCatClient))
	{
		return;
	}

	ConfigCatClient->setOnline();
}

void UConfigCatSubsystem::SetOffline()
{
	if (!EnsureConfigCatClient(ConfigCatClient))
	{
		return;
	}

	ConfigCatClient->setOffline();
}

bool UConfigCatSubsystem::IsOffline() const
{
	if (!EnsureConfigCatClient(ConfigCatClient))
	{
		return true;
	}

	return ConfigCatClient->isOffline();
}

void UConfigCatSubsystem::PerformInitialize()
{
#if PLATFORM_IOS && !FORCE_ANSI_ALLOCATOR
	UE_LOG(LogConfigCat, Fatal, TEXT("ConfigCat for iOS currently requires 'FORCE_ANSI_ALLOCATOR=1' inside your PROJECTNAME.Target.cs"));
#endif

	const UConfigCatSettings* ConfigCatSettings = GetDefault<UConfigCatSettings>();
	if (!ConfigCatSettings || ConfigCatSettings->SdkKey.IsEmpty())
	{
		PrintError(TEXT("SdkKey missing. Please set your SdkKey in the Project Settings."));
		return;
	}

	const std::string& SdkKey = TCHAR_TO_UTF8(*ConfigCatSettings->SdkKey);

	const FString CppSdkVersion = UTF8_TO_TCHAR(configcat::version);
	UE_LOG(LogConfigCat, Display, TEXT("ConfigCat Subsystem initializing cpp-sdk - %s"), *CppSdkVersion);

	ConfigCatOptions Options;
	Options.baseUrl = TCHAR_TO_UTF8(*ConfigCatSettings->BaseUrl);
	Options.dataGovernance = ConfigCatSettings->DataGovernance == EDataGovernance::Global ? Global : EuOnly;
	Options.connectTimeoutMs = ConfigCatSettings->ConnectionTimeoutMs;
	Options.readTimeoutMs = ConfigCatSettings->ReadTimeoutMs;

	switch (ConfigCatSettings->PollingMode)
	{
	case EPollingMode::Auto:
		Options.pollingMode = PollingMode::autoPoll(ConfigCatSettings->AutoPollIntervalSeconds, ConfigCatSettings->MaxInitWaitTimeSeconds);
		break;
	case EPollingMode::LazyLoad:
		Options.pollingMode = PollingMode::lazyLoad(ConfigCatSettings->CacheRefreshIntervalSeconds);
		break;
	case EPollingMode::ManualPoll:
		Options.pollingMode = PollingMode::manualPoll();
		break;
	}

	for (const TTuple<FString, FString>& Proxy : ConfigCatSettings->Proxies)
	{
		const std::string& ProxyKey = TCHAR_TO_UTF8(*Proxy.Key);
		const std::string& ProxyValue = TCHAR_TO_UTF8(*Proxy.Value);

		Options.proxies.emplace(ProxyKey, ProxyValue);
	}

	for (const TTuple<FString, FProxyAuthentication>& ProxyAuth : ConfigCatSettings->ProxyAuthentications)
	{
		const std::string& ProxyKey = TCHAR_TO_UTF8(*ProxyAuth.Key);

		ProxyAuthentication ProxyValue;
		ProxyValue.user = TCHAR_TO_UTF8(*ProxyAuth.Value.User);
		ProxyValue.password = TCHAR_TO_UTF8(*ProxyAuth.Value.Password);

		Options.proxyAuthentications.emplace(ProxyKey, ProxyValue);
	}

	Options.httpSessionAdapter = std::make_shared<ConfigCatNetworkAdapter>(Options.pollingMode);
	Options.logger = std::make_shared<FConfigCatLogger>();
	Options.offline = ConfigCatSettings->bStartOffline;

	SetupClientHooks(Options);
	SetupClientOverrides(Options);

	OnConfigureOptions.Broadcast(Options);

	try
	{
		ConfigCatClient = ConfigCatClient::get(SdkKey, &Options);
	}
	catch (const std::exception& e)
	{
		const FString& ExceptionString = UTF8_TO_TCHAR(e.what());
		const FString& ErrorMessage = FString::Printf(TEXT("ConfigCatSDK initialization failed with error: %s"), *ExceptionString);
		PrintError(ErrorMessage);
		return;
	}

#ifdef CONFIGCAT_HTTPTHREAD_WORKAROUND
	if (ConfigCatSettings->PollingMode == EPollingMode::Auto)
	{
		ForceRefresh();
	}
#endif
}

void UConfigCatSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	const UConfigCatSettings* ConfigCatSettings = GetDefault<UConfigCatSettings>();
	if (ConfigCatSettings && ConfigCatSettings->bAutoInitialize)
	{
		PerformInitialize();
	}
}

void UConfigCatSubsystem::Deinitialize()
{
	UE_LOG(LogConfigCat, Log, TEXT("ConfigCat Subsystem shutdown"));

	if (ConfigCatClient)
	{
		const std::shared_ptr<Hooks> Hooks = ConfigCatClient->getHooks();
		Hooks->clear();

		ConfigCatClient::close(ConfigCatClient);
	}

	ConfigCatClient = nullptr;
}

void UConfigCatSubsystem::SetupClientHooks(ConfigCatOptions& Options)
{
	Options.hooks = std::make_shared<Hooks>();
	TWeakObjectPtr<UConfigCatSubsystem> WeakThis(this);

	Options.hooks->addOnError(
		[WeakThis](const std::string& Error, const std::exception_ptr& Exception)
		{
			if (WeakThis.IsValid())
			{
				WeakThis->OnErrorHook(Error, Exception);
			}
		}
	);
	Options.hooks->addOnClientReady(
		[WeakThis]()
		{
			if (WeakThis.IsValid())
			{
				WeakThis->OnClientReadyHook();
			}
		}
	);
	Options.hooks->addOnConfigChanged(
		[WeakThis](const std::shared_ptr<const Settings>& InConfig)
		{
			if (WeakThis.IsValid())
			{
				WeakThis->OnConfigChangedHook(InConfig);
			}
		}
	);
	Options.hooks->addOnFlagEvaluated(
		[WeakThis](const EvaluationDetailsBase& InEvaluationDetails)
		{
			if (WeakThis.IsValid())
			{
				UConfigCatEvaluationWrapper* EvaluationDetails = UConfigCatEvaluationWrapper::CreateEvaluation(InEvaluationDetails);

				WeakThis->OnFlagEvaluated.Broadcast(EvaluationDetails);
				WeakThis->OnFlagEvaluatedBp.Broadcast(EvaluationDetails);
			}
		}
	);
}

void UConfigCatSubsystem::SetupClientOverrides(ConfigCatOptions& Options)
{
	const UConfigCatSettings* ConfigCatSettings = GetDefault<UConfigCatSettings>();
	const OverrideBehaviour Behaviour = [=]()
	{
		switch (ConfigCatSettings->OverrideBehaviour)
		{
		case EOverrideBehaviour::LocalOnly:
			return LocalOnly;
		case EOverrideBehaviour::LocalOverRemote:
			return LocalOverRemote;
		case EOverrideBehaviour::RemoteOverLocal:
			return RemoteOverLocal;
		}

		checkNoEntry();
		return RemoteOverLocal;
	}();

	if (ConfigCatSettings->OverrideMode == EOverrideMode::File)
	{
		const FString FlagsFile = FConfigCatModule::GetContentFolder() + TEXT("/flags.json");
		std::string FlagsFilePath = TCHAR_TO_UTF8(*FlagsFile);
		Options.flagOverrides = std::make_shared<FileFlagOverrides>(FlagsFilePath, Behaviour);
	}
	else if (ConfigCatSettings->OverrideMode == EOverrideMode::Map)
	{
		// TODO: This would require delayed initialization or static delegates just to bind this + create a config in blueprints is quiet horrible.
		UE_LOG(LogConfigCat, Error, TEXT("Programatically overriding with a map flag is currently not supported."));
		// std::unordered_map<std::string, Value> OverrideFlags;
		// Options.flagOverrides = std::make_shared<MapFlagOverrides>(OverrideFlags, Behaviour);
	}
}

void UConfigCatSubsystem::OnErrorHook(const std::string& Error, const std::exception_ptr& Exception)
{
	const FString& StringError = UTF8_TO_TCHAR(Error.c_str());
	const FString& StringException = UTF8_TO_TCHAR(unwrap_exception_message(Exception).c_str());

	AsyncTask(ENamedThreads::GameThread, [WeakThis = TWeakObjectPtr<UConfigCatSubsystem>(this), StringError, StringException]()
	{
		if (WeakThis.IsValid())
		{
			WeakThis->OnError.Broadcast(StringError, StringException);
			WeakThis->OnErrorBp.Broadcast(StringError, StringException);
		}
	});
}

void UConfigCatSubsystem::OnClientReadyHook()
{
	AsyncTask(ENamedThreads::GameThread, [WeakThis = TWeakObjectPtr<UConfigCatSubsystem>(this)]()
	{
		if (WeakThis.IsValid())
		{
			WeakThis->OnClientReady.Broadcast();
			WeakThis->OnClientReadyBP.Broadcast();
		}
	});
}

void UConfigCatSubsystem::OnConfigChangedHook(const std::shared_ptr<const configcat::Settings>& InConfig)
{
	AsyncTask(ENamedThreads::GameThread, [WeakThis = TWeakObjectPtr<UConfigCatSubsystem>(this), InConfig]()
	{
		if (WeakThis.IsValid())
		{
			UConfigCatSettingsWrapper* Config = UConfigCatSettingsWrapper::CreateSettings(InConfig);

			WeakThis->OnConfigChanged.Broadcast(Config);
			WeakThis->OnConfigChangedBp.Broadcast(Config);
		}
	});
}