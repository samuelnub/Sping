#pragma once

namespace Sping
{
	const bool DEBUG = true;
	const int THREAD_COUNT = 16;

	enum class Err
	{
		GENERIC = 8008135,
		FATAL = 46290,
		CATASTROPHIC = 3,
		OH_BOY = 0xDEAD
	};
}