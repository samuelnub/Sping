#pragma once

#include <Util/GLEWInclude.h>

#include <memory>

#include <Handler/Handler.h>
#include <Render/Renderer.h>

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
		std::unique_ptr<Renderer> renderer;

	protected:


	private:


	};
}