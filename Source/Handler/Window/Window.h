#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace Sping
{
	class Handler;

	// Window handler class, tell it to resize the window, update its info, all that stuff
	class Window
	{
	public:
		Window(Handler &handler);
		~Window();

		inline SDL_Window *getWindow()
		{
			return this->window;
		}

	protected:


	private:
		Handler &handler;

		SDL_Window *window;
		SDL_GLContext glContext;

		int windowFlags; // Enums | OR'ed

		void init();

	};
}