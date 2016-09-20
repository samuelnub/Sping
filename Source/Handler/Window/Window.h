#pragma once

#include <SDL2/SDL.h>
#include <atomic>

namespace Sping
{
	class Handler;

	// Window handler class, tell it to resize the window, update its info, all that stuff
	class Window
	{
	public:
		Window(Handler &handler);
		~Window();

		const bool &locked()
		{
			return this->locked;
		}

	protected:


	private:
		Handler &handler;

		SDL_Window *window;

		int windowFlags; // Enums | OR'ed

		SDL_Renderer *renderer;

		std::atomic<bool> locked = true;

		void init();

	};
}