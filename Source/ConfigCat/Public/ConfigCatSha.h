// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <string>

namespace configcat
{

	/**
	 * Implementation of the configcat hashing functions for Sha1 & Sha256
	 * @note This is done to avoid the extra dependency on hash-node library for the Unreal Engine SDK
	 */
	std::string sha1(const std::string& input);
	std::string sha256(const std::string& input);
}