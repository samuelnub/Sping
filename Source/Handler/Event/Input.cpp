#include <Handler/Event/Input.h>
#include <Util/Constants.h>
#include <iostream>

Sping::Input::Input()
{
	// TODO: find a better place to init everything, or just init each part you want in each class (this guy should be the first sdl-related class to init)
	SDL_Init(SDL_INIT_EVERYTHING);

	this->resetStates();

	if (Sping::DEBUG)
	{
		std::cout << "Initialized the input reciever!\n";
	}
}

Sping::Input::~Input()
{
}

void Sping::Input::tick()
{
	this->resetStates();

	while (SDL_PollEvent(&this->event) != 0)
	{
		this->frameEvents.push_back(this->event);
	}

	if (!this->frameEvents.empty())
	{
		this->process();
		this->frameEvents.clear();
	}
}

void Sping::Input::resetStates()
{
	for (auto &key : this->keyStates)
	{
		switch (key)
		{
		case InputState::PRESSED:
			key = InputState::HELD;
			break;
		case InputState::RELEASED:
			key = InputState::UNHELD;
			break;
		case InputState::HELD:
			break;
		case InputState::UNHELD:
			break;
		default:
			key = InputState::UNHELD;
			break;
		}
	}

	for (auto &button : this->mouseButtonStates)
	{
		switch (button)
		{
		case InputState::PRESSED:
			button = InputState::HELD;
			break;
		case InputState::RELEASED:
			button = InputState::UNHELD;
			break;
		case InputState::HELD:
			break;
		case InputState::UNHELD:
			break;
		default:
			button = InputState::UNHELD;
			break;
		}
	}

	this->mouseState.cursorMovedX = 0;
	this->mouseState.cursorMovedY = 0;
	this->mouseState.scrolledX = 0;
	this->mouseState.scrolledY = 0;

	this->totalTime = SDL_GetTicks();
	this->deltaTime = this->totalTime - this->lastFrameTime;
	this->lastFrameTime = this->totalTime;
}

void Sping::Input::process()
{
	for (auto &event : this->frameEvents)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			SDL_Quit();
			exit(EXIT_SUCCESS);
			break;
		case SDL_KEYDOWN:
			switch (event.key.repeat)
			{
			case true:
				//TODO: here
			case false:
				//TODO: here
			default:
				std::cout << "how was the keydown repeat not a bool...\n";
				break;
			}
			break;
			//TODO: here too
		default:
			break;
		}
	}
}

void Sping::Input::keyDownEvent(SDL_Event & event)
{
	this->keyStates[event.key.keysym.scancode] = InputState::PRESSED;
}

void Sping::Input::keyHeldEvent(SDL_Event & event)
{

}

void Sping::Input::keyUpEvent(SDL_Event & event)
{
}

void Sping::Input::mouseMotionEvent(SDL_Event & event)
{
}

void Sping::Input::mouseScrollEvent(SDL_Event & event)
{
}

void Sping::Input::mouseButtonDownEvent(SDL_Event & event)
{
}

void Sping::Input::mouseButtonUpEvent(SDL_Event & event)
{
}
