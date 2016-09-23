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

	// SDL input reciever class
	class Input
	{
	public:
		Input();
		~Input();

		void tick();

		inline const float &getDelta()
		{
			return this->deltaTime;
		}

	protected:


	private:
		friend class Events;

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

		void keyDownEvent(SDL_Event &event);
		void keyHeldEvent(SDL_Event &event);
		void keyUpEvent(SDL_Event &event);

		void mouseMotionEvent(SDL_Event &event);
		void mouseScrollEvent(SDL_Event &event);
		void mouseButtonDownEvent(SDL_Event &event);
		void mouseButtonUpEvent(SDL_Event &event);

	};
}