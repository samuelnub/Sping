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
		RELEASED
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

	// SDL input reciever class
	class Input
	{
	public:
		Input();
		~Input();

		void tick();

	protected:


	private:
		friend class Events;

		SDL_Event event;
		std::vector<SDL_Event> frameEvents;

		std::array<InputState, 1024> keyStates;
		std::array<InputState, 5> mouseButtonStates;
		MouseInfo mouseState;

		float deltaTime;
		float lastFrameTime;
		float totalTime; // up&up it goes

	};
}