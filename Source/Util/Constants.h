#pragma once

#include <iostream>
#include <string>

namespace Sping
{
	const bool SPING_DEBUG(true);
	const int THREAD_COUNT(32);

	enum class Err
	{
		GENERIC,
		FATAL,
		CATASTROPHIC,
		FILE_ERROR,

		OH_BOY = 0xDEAD
	};

	void debugLog(const std::string &message);
}