#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <array>

namespace Sping
{
	enum class InputState
	{
		PRESSED,
		HELD,
		RELEASED,
		UNHELD // lol good naming
	};

	struct MouseInfo
	{
		int cursorPosX = 0;
		int cursorPosY = 0;

		int cursorMovedX = 0;
		int cursorMovedY = 0;

		int scrolledX = 0;
		int scrolledY = 0;
	};

	class Handler;

	// SDL input reciever class
	class Input
	{
	public:
		Input(Handler &handler);
		~Input();

		void tick();

		inline const float &getDelta()
		{
			return this->deltaTime;
		}

	protected:


	private:
		friend class Events;

		Handler &handler;

		SDL_Event event;
		std::vector<SDL_Event> frameEvents;

		std::array<InputState, 1024> keyStates;
		std::array<InputState, 5> mouseButtonStates;
		MouseInfo mouseState;

		// At constructor, and every tick
		void resetStates();
		void process();

		float deltaTime = 0.0f;
		float lastFrameTime = 0.0f;
		float totalTime = 0.0f; // up&up it goes

		void keyPressedEvent(SDL_Event &event);
		void keyHeldEvent(SDL_Event &event);
		void keyReleasedEvent(SDL_Event &event);

		void mouseMotionEvent(SDL_Event &event);
		void mouseScrollEvent(SDL_Event &event);
		void mouseButtonPressedEvent(SDL_Event &event);
		void mouseButtonReleasedEvent(SDL_Event &event);

	};
}