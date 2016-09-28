#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace Sping
{
	class Handler;

	// Window handler class, tell it to resize the window, update its info, all that stuff
	// TODO: window info struct that other classes can get info about the current window state, as well as wrapper functions here to set window size, fullscreen etc...
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

		void init();

	};
}