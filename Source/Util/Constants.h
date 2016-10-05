#pragma once

#include <iostream>
#include <string>

namespace Sping
{
	const bool SPING_DEBUG = true;
	const int THREAD_COUNT = 32;
	const std::string ROOT_DIR = "Resource/";

	enum class Err
	{
		GENERIC,
		FATAL,
		CATASTROPHIC,
		FILE,
		WINDOW,
		SHADER_COMPILE,
		SHADER_LINK,
		IMAGE_LOAD,

		OH_BOY = 0xDEAD
	};

	void debugLog(const std::string &message);
}