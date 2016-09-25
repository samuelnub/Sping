#pragma once

#include <iostream>
#include <string>

namespace Sping
{
	const bool DEBUG = true;
	const int THREAD_COUNT = 32;

	enum class Err
	{
		GENERIC = 8008135,
		FATAL = 46290,
		CATASTROPHIC = 3,
		OH_BOY = 0xDEAD
	};

	void debugLog(const std::string &message);
}