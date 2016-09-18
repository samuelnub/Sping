#pragma once

#include <memory>

#include <Handler/Handler.h>

namespace Sping
{
	// Game class, contains main loop to call other managers to update their stuff
	class Game
	{
	public:
		Game();
		~Game();

		void tick();

		std::unique_ptr<Handler> handler;

	protected:


	private:


	};
}