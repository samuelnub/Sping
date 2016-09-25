#pragma once

#include <SDL2/SDL.h>

namespace Sping
{
	class Handler;

	// Window handler class, tell it to resize the window, update its info, all that stuff
	class Window
	{
	public:
		Window(Handler &handler);
		~Window();

		inline const SDL_Window *getWindow()
		{
			return this->window;
		}

	protected:


	private:
		Handler &handler;

		SDL_Window *window;

		int windowFlags; // Enums | OR'ed

		SDL_Renderer *renderer;

		void init();

	};
}