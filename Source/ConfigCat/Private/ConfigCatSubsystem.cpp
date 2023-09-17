// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "ConfigCatSubsystem.h"

#include <ConfigCatCppSDK/Include/configcatclient.h>
#include <ConfigCatCppSDK/Include/configcatuser.h>
#include <ConfigCatCppSDK/Include/fileoverridedatasource.h>
#include <ConfigCatCppSDK/Include/mapoverridedatasource.h>
#include <Kismet/GameplayStatics.h>
#include <Logging/LogVerbosity.h>
#include <Misc/ConfigCacheIni.h>

#include "ConfigCatLog.h"
#include "ConfigCatLogger.h"
#include "ConfigCatSettings.h"
#include "Wrapper/ConfigCatEvaluationDetails.h"
#include "Wrapper/ConfigCatUser.h"
#include "Wrapper/ConfigCatValue.h"

using namespace configcat;

namespace
{
	template <typename T>
	T GetValue(ConfigCatClient* Client, FString Key, T DefaultValue, const FConfigCatUser& User)
	{
		if (!ensure(Client))
		{
			UE_LOG(LogConfigCat, Warning, TEXT("Trying to access the ConfigCatClient before initialization or after shutdown."));
			return DefaultValue;
		}

		const ConfigCatUser* TargetUser = User.User.get();
		const std::string& FlagKey = TCHAR_TO_UTF8(*Key);

		return Client->getValue(FlagKey, DefaultValue, TargetUser);
	}

	template <typename T>
	EvaluationDetails GetEvaluationDetails(ConfigCatClient* Client, FString Key, T DefaultValue, const FConfigCatUser& User)
	{
		if (!ensure(Client))
		{
			UE_LOG(LogConfigCat, Warning, TEXT("Trying to access the ConfigCatClient before initialization or after shutdown."));
			return {};
		}

		const ConfigCatUser* TargetUser = User.User.get();
		const std::string& FlagKey = TCHAR_TO_UTF8(*Key);

		return Client->getValueDetails(FlagKey, DefaultValue, TargetUser);
	}
} // namespace


UConfigCatSubsystem* UConfigCatSubsystem::Get(const UObject* WorldContext)
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContext);
	return GameInstance->GetSubsystem<UConfigCatSubsystem>();
}

bool UConfigCatSubsystem::GetBoolValue(const FString& Key, bool bDefaultValue, const FConfigCatUser& User) const
{
	return GetValue(ConfigCatClient, Key, bDefaultValue, User);
}

int32 UConfigCatSubsystem::GetIntValue(const FString& Key, int32 DefaultValue, const FConfigCatUser& User) const
{
	return GetValue(ConfigCatClient, Key, DefaultValue, User);
}

double UConfigCatSubsystem::GetDoubleValue(const FString& Key, double DefaultValue, const FConfigCatUser& User) const
{
	return GetValue(ConfigCatClient, Key, DefaultValue, User);
}

FString UConfigCatSubsystem::GetStringValue(const FString& Key, const FString& DefaultValue, const FConfigCatUser& User) const
{
	const std::string& StringDefaultValue = TCHAR_TO_UTF8(*DefaultValue);
	const std::string& StringResult = GetValue(ConfigCatClient, Key, StringDefaultValue, User);
	return UTF8_TO_TCHAR(StringResult.c_str());
}

FConfigCatValue UConfigCatSubsystem::GetConfigValue(const FString& Key, const FConfigCatUser& User) const
{
	if (!ensure(ConfigCatClient))
	{
		UE_LOG(LogConfigCat, Warning, TEXT("Trying to access the ConfigCatClient before initialization or after shutdown."));
		return {};
	}

	const ConfigCatUser* TargetUser = User.User.get();
	const std::string& FlagKey = TCHAR_TO_UTF8(*Key);

	const std::shared_ptr<Value> FeatureFlagValue = ConfigCatClient->getValue(FlagKey, TargetUser);
	return FConfigCatValue(FeatureFlagValue);
}

FConfigCatEvaluationDetails UConfigCatSubsystem::GetBoolValueDetails(const FString& Key, bool DefaultValue, const FConfigCatUser& User) const
{
	return GetEvaluationDetails(ConfigCatClient, Key, DefaultValue, User);
}

FConfigCatEvaluationDetails UConfigCatSubsystem::GetIntValueDetails(const FString& Key, int DefaultValue, const FConfigCatUser& User) const
{
	return GetEvaluationDetails(ConfigCatClient, Key, DefaultValue, User);
}

FConfigCatEvaluationDetails UConfigCatSubsystem::GetDoubleValueDetails(const FString& Key, double DefaultValue, const FConfigCatUser& User) const
{
	return GetEvaluationDetails(ConfigCatClient, Key, DefaultValue, User);
}

FConfigCatEvaluationDetails UConfigCatSubsystem::GetStringValueDetails(const FString& Key, const FString& DefaultValue, const FConfigCatUser& User) const
{
	const std::string& StringDefaultValue = TCHAR_TO_UTF8(*DefaultValue);
	return GetEvaluationDetails(ConfigCatClient, Key, StringDefaultValue, User);
}

TArray<FString> UConfigCatSubsystem::GetAllKeys() const
{
	if (!ensure(ConfigCatClient))
	{
		UE_LOG(LogConfigCat, Warning, TEXT("Trying to access the ConfigCatClient before initialization or after shutdown."));
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

bool UConfigCatSubsystem::GetKeyAndValue(const FString& VariationId, FString& OutKey, FConfigCatValue& OutValue) const
{
	if (!ensure(ConfigCatClient))
	{
		UE_LOG(LogConfigCat, Warning, TEXT("Trying to access the ConfigCatClient before initialization or after shutdown."));
		return false;
	}

	const std::string& VariationIdString = TCHAR_TO_UTF8(*VariationId);

	std::shared_ptr<KeyValue> KeyValue = ConfigCatClient->getKeyAndValue(VariationIdString);

	if (!KeyValue)
	{
		return false;
	}

	OutKey = UTF8_TO_TCHAR(KeyValue->key.c_str());
	OutValue = KeyValue->value;
	return true;
}

TMap<FString, FConfigCatValue> UConfigCatSubsystem::GetAllValues(const FConfigCatUser& User) const
{
	if (!ensure(ConfigCatClient))
	{
		UE_LOG(LogConfigCat, Warning, TEXT("Trying to access the ConfigCatClient before initialization or after shutdown."));
		return {};
	}

	const ConfigCatUser* TargetUser = User.User.get();

	const std::unordered_map<std::string, Value> Values = ConfigCatClient->getAllValues(TargetUser);

	TMap<FString, FConfigCatValue> Result;
	for (const std::pair<const std::string, Value>& Value : Values)
	{
		Result.Emplace(UTF8_TO_TCHAR(Value.first.c_str()), Value.second);
	}

	return Result;
}

TArray<FConfigCatEvaluationDetails> UConfigCatSubsystem::GetAllValueDetails(const FConfigCatUser& User) const
{
	if (!ensure(ConfigCatClient))
	{
		UE_LOG(LogConfigCat, Warning, TEXT("Trying to access the ConfigCatClient before initialization or after shutdown."));
		return {};
	}

	const ConfigCatUser* TargetUser = User.User.get();

	const std::vector<EvaluationDetails> ValueDetails = ConfigCatClient->getAllValueDetails(TargetUser);

	TArray<FConfigCatEvaluationDetails> Result;
	for (const EvaluationDetails& ValueDetail : ValueDetails)
	{
		Result.Emplace(ValueDetail);
	}

	return Result;
}

void UConfigCatSubsystem::ForceRefresh()
{
	if (!ensure(ConfigCatClient))
	{
		UE_LOG(LogConfigCat, Warning, TEXT("Trying to access the ConfigCatClient before initialization or after shutdown."));
		return;
	}

	ConfigCatClient->forceRefresh();
}

void UConfigCatSubsystem::SetDefaultUser(const FConfigCatUser& User)
{
	if (!ensure(ConfigCatClient))
	{
		UE_LOG(LogConfigCat, Warning, TEXT("Trying to access the ConfigCatClient before initialization or after shutdown."));
		return;
	}
	if (!User.User)
	{
		UE_LOG(LogConfigCat, Warning, TEXT("Trying to set Default User with invalid pointer."));
		return;
	}

	ConfigCatClient->setDefaultUser(User.User);
}

void UConfigCatSubsystem::ClearDefaultUser()
{
	if (!ensure(ConfigCatClient))
	{
		UE_LOG(LogConfigCat, Warning, TEXT("Trying to access the ConfigCatClient before initialization or after shutdown."));
		return;
	}

	ConfigCatClient->clearDefaultUser();
}

void UConfigCatSubsystem::SetOnline()
{
	if (!ensure(ConfigCatClient))
	{
		UE_LOG(LogConfigCat, Warning, TEXT("Trying to access the ConfigCatClient before initialization or after shutdown."));
		return;
	}

	ConfigCatClient->setOnline();
}

void UConfigCatSubsystem::SetOffline()
{
	if (!ensure(ConfigCatClient))
	{
		UE_LOG(LogConfigCat, Warning, TEXT("Trying to access the ConfigCatClient before initialization or after shutdown."));
		return;
	}

	ConfigCatClient->setOffline();
}

bool UConfigCatSubsystem::IsOffline() const
{
	if (!ensure(ConfigCatClient))
	{
		UE_LOG(LogConfigCat, Warning, TEXT("Trying to access the ConfigCatClient before initialization or after shutdown."));
		return true;
	}

	// TODO: Investigate why this is not const in the CPP SDK.
	return ConfigCatClient->isOffline();
}

void UConfigCatSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogConfigCat, Log, TEXT("ConfigCat Subsystem initialized"));

	const UConfigCatSettings* ConfigCatSettings = GetDefault<UConfigCatSettings>();
	const std::string& SdkKey = TCHAR_TO_UTF8(*ConfigCatSettings->SdkKey);

	ConfigCatOptions Options;
	Options.baseUrl = TCHAR_TO_UTF8(*ConfigCatSettings->BaseUrl);
	Options.dataGovernance = ConfigCatSettings->DataGovernance == EDataGovernance::Global ? Global : EuOnly;
	Options.connectTimeoutMs = ConfigCatSettings->ConnectionTimeout;
	Options.readTimeoutMs = ConfigCatSettings->ReadTimeout;

	switch (ConfigCatSettings->PollingMode)
	{
		case EPollingMode::Auto:
			Options.pollingMode = PollingMode::autoPoll(ConfigCatSettings->AutoPollInterval, ConfigCatSettings->MaxInitWaitTime);
			break;
		case EPollingMode::LazyLoad:
			Options.pollingMode = PollingMode::lazyLoad(ConfigCatSettings->CacheRefreshInterval);
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

	Options.logger = std::make_shared<FConfigCatLogger>();
	Options.offline = ConfigCatSettings->bStartOffline;

	SetupClientHooks(Options);
	SetupClientSslOptions(Options);
	SetupClientOverrides(Options);

	ConfigCatClient = ConfigCatClient::get(SdkKey, &Options);
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
		[WeakThis](const std::string& Error)
		{
			if (WeakThis.IsValid())
			{
				const FString& StringError = UTF8_TO_TCHAR(Error.c_str());

				UE_LOG(LogConfigCat, Error, TEXT("ConfigCatClient Error: %s"), *StringError);

				WeakThis->OnError.Broadcast(StringError);
				WeakThis->OnErrorBp.Broadcast(StringError);
			}
		}
	);
	Options.hooks->addOnClientReady(
		[WeakThis]()
		{
			if (WeakThis.IsValid())
			{
				WeakThis->OnClientReady.Broadcast();
				WeakThis->OnClientReadyBP.Broadcast();
			}
		}
	);
	Options.hooks->addOnConfigChanged(
		[WeakThis](const std::shared_ptr<Settings>& Config)
		{
			if (WeakThis.IsValid())
			{
				FConfigCatConfig NewConfig;

				// TODO: Check if Config will be ever nullptr
				if (Config)
				{
					for (const std::pair<const std::string, Setting>& Setting : *Config)
					{
						NewConfig.Settings.Emplace(UTF8_TO_TCHAR(Setting.first.c_str()), Setting.second);
					}
				}

				WeakThis->OnConfigChanged.Broadcast(NewConfig);
				WeakThis->OnConfigChangedBp.Broadcast(NewConfig);
			}
		}
	);
	Options.hooks->addOnFlagEvaluated(
		[WeakThis](const EvaluationDetails& EvaluationDetails)
		{
			if (WeakThis.IsValid())
			{
				WeakThis->OnFlagEvaluated.Broadcast(EvaluationDetails);
				WeakThis->OnFlagEvaluatedBp.Broadcast(EvaluationDetails);
			}
		}
	);
}

void UConfigCatSubsystem::SetupClientSslOptions(ConfigCatOptions& Options)
{
	Options.sslOptions = std::make_shared<SslOptions>();

	bool bVerifyPeer = true;
	if (GConfig->GetBool(TEXT("/Script/Engine.NetworkSettings"), TEXT("n.VerifyPeer"), bVerifyPeer, GEngineIni))
	{
		Options.sslOptions->verifySSL = {bVerifyPeer};
	}

#if PLATFORM_LINUX || PLATFORM_ANDROID
	//TODO: Make sure that (1) certificate file is copied to Content/ConfigCat and (2) files from Content/ConfigCat are packaged the final package
	const FString CertificateFile = FPaths::ProjectContentDir() + TEXT("ConfigCat/globalsign-root-ca.pem");
	FString CertificateContent = TEXT(""); 
	if (FFileHelper::LoadFileToString(CertificateContent, *CertificateFile))
	{
		UE_LOG(LogConfig, Log, TEXT("Certificate from %s will be used for SSL"), *CertificateFile);
		Options.sslOptions->caBuffer = TCHAR_TO_UTF8(*CertificateContent);
	}
	else
	{
		UE_LOG(LogConfig, Error, TEXT("Failed to read certificate from %s"), *CertificateFile);
	}
#endif
}

void UConfigCatSubsystem::SetupClientOverrides(ConfigCatOptions& Options)
{
	const UConfigCatSettings* ConfigCatSettings = GetDefault<UConfigCatSettings>();
	const OverrideBehaviour Behaviour = [=]()
	{
		switch (ConfigCatSettings->OverrideBehaviour)
		{
		case EOverrideBehaviour::LocalOnly: return OverrideBehaviour::LocalOnly;
		case EOverrideBehaviour::LocalOverRemote:  return OverrideBehaviour::LocalOverRemote;
		case EOverrideBehaviour::RemoteOverLocal: return OverrideBehaviour::RemoteOverLocal;
		}

		checkNoEntry();
	}();

	if(ConfigCatSettings->OverrideMode == EOverrideMode::File)
	{
		//TODO: error: destructor called on non-final 'configcat::FileFlagOverrides' that has virtual functions but non-virtual destructor [-Werror,-Wdelete-non-abstract-non-virtual-dtor]
		const FString FlagsFile = FPaths::ProjectContentDir() + TEXT("ConfigCat/flags.json");
		std::string FlagsFilePath = TCHAR_TO_UTF8(*FlagsFile); 
		Options.flagOverrides = std::make_shared<FileFlagOverrides>(FlagsFilePath, Behaviour);
	}
	else if(ConfigCatSettings->OverrideMode == EOverrideMode::Map)
	{
		//TODO: This would require delayed initialization or static delegates just to bind this + create a config in blueprints is quiet horrible.
		UE_LOG(LogConfig, Error, TEXT("Programatically overriding with a map flag is currently not supported."));
		//std::unordered_map<std::string, Value> OverrideFlags;
		//Options.flagOverrides = std::make_shared<MapFlagOverrides>(OverrideFlags, Behaviour);
	}
}
