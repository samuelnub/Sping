#pragma once

#include <memory>
#include <Util/Constants.h>

#include <Handler/Thread/ThreadPool.h>

namespace Sping
{
	// Handler manager, to encapsulate it more from the main game class
	class Handler
	{
	public:
		Handler();
		~Handler();

		void tick();

		std::unique_ptr<ThreadPool> threadPool;

	protected:


	private:


	};
}