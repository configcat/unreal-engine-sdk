// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "ConfigCatSubsystem.h"

#include <ConfigCatCppSDK/Include/configcatclient.h>
#include <ConfigCatCppSDK/Include/configcatuser.h>

#include "ConfigCatLog.h"
#include "ConfigCatLogger.h"
#include "ConfigCatSettings.h"
#include "ConfigCatuser.h"
#include "Logging/LogVerbosity.h"

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

		const ConfigCatUser NativeUser = User.ToNative();
		const ConfigCatUser* TargetUser = User.IsValid() ? &NativeUser : nullptr;

		const std::string& FlagKey = TCHAR_TO_UTF8(*Key);
		return Client->getValue(FlagKey, DefaultValue, TargetUser);
	}
} // namespace


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

	const std::shared_ptr<ConfigCatUser> DefaultUser = std::make_shared<ConfigCatUser>(User.ToNative());
	ConfigCatClient->setDefaultUser(DefaultUser);
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