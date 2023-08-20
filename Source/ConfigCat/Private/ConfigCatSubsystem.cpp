// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "ConfigCatSubsystem.h"

#include <ConfigCatCppSDK/Include/configcatclient.h>
#include <ConfigCatCppSDK/Include/configcatuser.h>
#include <Kismet/GameplayStatics.h>
#include <Logging/LogVerbosity.h>
#include <Misc/ConfigCacheIni.h>

#include "ConfigCatLog.h"
#include "ConfigCatLogger.h"
#include "ConfigCatSettings.h"
#include "ConfigCatUser.h"
#include "ConfigCatValue.h"

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
} // namespace


UConfigCatSubsystem* UConfigCatSubsystem::Get(const UObject* WorldContext)
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContext);
	return GameInstance->GetSubsystem<UConfigCatSubsystem>();
}

bool UConfigCatSubsystem::GetBoolValue(const FString& Key, bool bDefaultValue, const FConfigCatUser& User)
{
	return GetValue(ConfigCatClient, Key, bDefaultValue, User);
}

int32 UConfigCatSubsystem::GetIntValue(const FString& Key, int32 DefaultValue, const FConfigCatUser& User)
{
	return GetValue(ConfigCatClient, Key, DefaultValue, User);
}

double UConfigCatSubsystem::GetDoubleValue(const FString& Key, double DefaultValue, const FConfigCatUser& User)
{
	return GetValue(ConfigCatClient, Key, DefaultValue, User);
}

FString UConfigCatSubsystem::GetStringValue(const FString& Key, FString DefaultValue, const FConfigCatUser& User)
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
	// TODO: we need to eliminate unwanted lib files from GitHub artifacts

	UE_LOG(LogConfigCat, Log, TEXT("ConfigCat Subsystem initialized"));

	const UConfigCatSettings* ConfigCatSettings = GetDefault<UConfigCatSettings>();
	const std::string& SdkKey = TCHAR_TO_UTF8(*ConfigCatSettings->SdkKey);

	ConfigCatOptions Options;
	Options.baseUrl = TCHAR_TO_UTF8(*ConfigCatSettings->BaseUrl);
	Options.dataGovernance = ConfigCatSettings->DataGovernance == EDataGovernance::Global ? Global : EuOnly;
	Options.connectTimeoutMs = ConfigCatSettings->ConnectionTimeout;
	Options.readTimeoutMs = ConfigCatSettings->ReadTimeout;

	Options.sslOptions = std::make_shared<SslOptions>();

	bool bVerifyPeer = true;
	if (GConfig->GetBool(TEXT("/Script/Engine.NetworkSettings"), TEXT("n.VerifyPeer"), bVerifyPeer, GEngineIni))
	{
		Options.sslOptions->verifySSL = {bVerifyPeer};
	}

	// TODO: This should only happen on android & probably linux (need testing to confirm). Or maybe we should leave it in for all platforms?
	const FString ConfigCatCert = "-----BEGIN CERTIFICATE-----\n"
								  "MIIDdTCCAl2gAwIBAgILBAAAAAABFUtaw5QwDQYJKoZIhvcNAQEFBQAwVzELMAkG\n"
								  "A1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv\n"
								  "b3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw05ODA5MDExMjAw\n"
								  "MDBaFw0yODAxMjgxMjAwMDBaMFcxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i\n"
								  "YWxTaWduIG52LXNhMRAwDgYDVQQLEwdSb290IENBMRswGQYDVQQDExJHbG9iYWxT\n"
								  "aWduIFJvb3QgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDaDuaZ\n"
								  "jc6j40+Kfvvxi4Mla+pIH/EqsLmVEQS98GPR4mdmzxzdzxtIK+6NiY6arymAZavp\n"
								  "xy0Sy6scTHAHoT0KMM0VjU/43dSMUBUc71DuxC73/OlS8pF94G3VNTCOXkNz8kHp\n"
								  "1Wrjsok6Vjk4bwY8iGlbKk3Fp1S4bInMm/k8yuX9ifUSPJJ4ltbcdG6TRGHRjcdG\n"
								  "snUOhugZitVtbNV4FpWi6cgKOOvyJBNPc1STE4U6G7weNLWLBYy5d4ux2x8gkasJ\n"
								  "U26Qzns3dLlwR5EiUWMWea6xrkEmCMgZK9FGqkjWZCrXgzT/LCrBbBlDSgeF59N8\n"
								  "9iFo7+ryUp9/k5DPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8E\n"
								  "BTADAQH/MB0GA1UdDgQWBBRge2YaRQ2XyolQL30EzTSo//z9SzANBgkqhkiG9w0B\n"
								  "AQUFAAOCAQEA1nPnfE920I2/7LqivjTFKDK1fPxsnCwrvQmeU79rXqoRSLblCKOz\n"
								  "yj1hTdNGCbM+w6DjY1Ub8rrvrTnhQ7k4o+YviiY776BQVvnGCv04zcQLcFGUl5gE\n"
								  "38NflNUVyRRBnMRddWQVDf9VMOyGj/8N7yy5Y0b2qvzfvGn9LhJIZJrglfCm7ymP\n"
								  "AbEVtQwdpf5pLGkkeB6zpxxxYu7KyJesF12KwvhHhm4qxFYxldBniYUr+WymXUad\n"
								  "DKqC5JlR3XC321Y9YeRq4VzW9v493kHMB65jUr9TU/Qr6cf9tveCX4XSQRjbgbME\n"
								  "HMUfpIBvFSDJ3gyICh3WZlXi/EjJKSZp4A==\n"
								  "-----END CERTIFICATE-----\n";

	Options.sslOptions->caBuffer = TCHAR_TO_UTF8(*ConfigCatCert);

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
			}
		}
	);
	Options.hooks->addOnClientReady(
		[WeakThis]()
		{
			if (WeakThis.IsValid())
			{
				WeakThis->OnClientReady.Broadcast();
			}
		}
	);
	Options.hooks->addOnConfigChanged(
		[WeakThis](std::shared_ptr<Settings> Config)
		{
			if (WeakThis.IsValid())
			{
			}
		}
	);
	Options.hooks->addOnFlagEvaluated(
		[WeakThis](const EvaluationDetails& EvaluationDetails)
		{
			if (WeakThis.IsValid())
			{
			}
		}
	);

	Options.logger = std::make_shared<FConfigCatLogger>();
	Options.offline = ConfigCatSettings->bStartOffline;

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