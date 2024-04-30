// Fill out your copyright notice in the Description page of Project Settings.


#include "Wrapper/ConfigCatConfigWrapper.h"

UConfigCatConfigWrapper* UConfigCatConfigWrapper::CreateConfig(std::shared_ptr<const configcat::Settings> InConfig)
{
	UConfigCatConfigWrapper* Result = NewObject<UConfigCatConfigWrapper>();
	Result->SetConfig(InConfig);
	return Result;
}

void UConfigCatConfigWrapper::SetConfig(std::shared_ptr<const configcat::Settings> InConfig)
{
	Config = InConfig;

	/*
if (Config)
{
	for (const std::pair<const std::string, Setting>& Setting : *Config)
    {
		NewConfig.Settings.Emplace(UTF8_TO_TCHAR(Setting.first.c_str()), Setting.second);
	}
}
	*/

}