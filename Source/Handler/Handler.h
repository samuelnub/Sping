#pragma once

#include <memory>
#include <Util/Constants.h>

#include <Handler/Thread/ThreadPool.h>
//TODO: settings manager should be sandwiched here
#include <Handler/Window/Window.h>

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
		std::unique_ptr<Window> window;

	protected:


	private:


	};
}