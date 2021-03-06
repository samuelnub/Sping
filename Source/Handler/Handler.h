#pragma once

#include <memory>
#include <Util/Constants.h>

#include <Handler/Thread/ThreadPool.h>
#include <Handler/File/Settings.h>
#include <Handler/Event/Input.h>
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
		std::unique_ptr<Settings> settings;
		std::unique_ptr<Input> input;
		std::unique_ptr<Window> window;

	protected:


	private:


	};
}