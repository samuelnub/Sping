#include <Handler/Event/Input.h>
#include <Handler/Handler.h>
#include <Util/Constants.h>
#include <iostream>

Sping::Input::Input(Handler &handler) :
	handler(handler)
{
	// TODO: find a better place to init everything, or just init each part you want in each class (this guy should be the first sdl-related class to init)
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Sping::debugLog({ "Unable to initialize SDL!\n" });
	}

	this->resetStates();

	Sping::debugLog("Initialized the input reciever!");
}

Sping::Input::~Input()
{
}

void Sping::Input::tick()
{
	this->resetStates();

	if (this->handler.window->getWindow() != nullptr)
	{
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
			if (event.key.repeat)
				this->keyHeldEvent(event);
			else
				this->keyPressedEvent(event);
			break;
		case SDL_KEYUP:
			this->keyReleasedEvent(event);
			break;
		case SDL_MOUSEMOTION:
			this->mouseMotionEvent(event);
			break;
		case SDL_MOUSEWHEEL:
			this->mouseScrollEvent(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			this->mouseButtonPressedEvent(event);
			break;
		case SDL_MOUSEBUTTONUP:
			this->mouseButtonReleasedEvent(event);
			break;

		// TODO: expand with other event types in the future

		default:
			break;
		}
	}
}

void Sping::Input::keyPressedEvent(SDL_Event & event)
{
	this->keyStates[event.key.keysym.scancode] = InputState::PRESSED;

	Sping::debugLog({ "Pressed key " + std::to_string(event.key.keysym.scancode)});
}

void Sping::Input::keyHeldEvent(SDL_Event & event)
{
	this->keyStates[event.key.keysym.scancode] = InputState::HELD;

	Sping::debugLog("Held key");
}

void Sping::Input::keyReleasedEvent(SDL_Event & event)
{
	this->keyStates[event.key.keysym.scancode] = InputState::RELEASED;
}

void Sping::Input::mouseMotionEvent(SDL_Event & event)
{
	this->mouseState.cursorPosX = event.motion.x;
	this->mouseState.cursorPosY = event.motion.y;
	this->mouseState.cursorMovedX = event.motion.xrel;
	this->mouseState.cursorMovedY = event.motion.yrel;
}

void Sping::Input::mouseScrollEvent(SDL_Event & event)
{
	this->mouseState.scrolledX = event.wheel.x;
	this->mouseState.scrolledY = event.wheel.y;
}

void Sping::Input::mouseButtonPressedEvent(SDL_Event & event)
{
	// AFAIK, SDL doesn't have a mouse button "held" state
	this->mouseButtonStates[event.button.button] = (
		this->mouseButtonStates[event.button.button] != InputState::HELD ||
		this->mouseButtonStates[event.button.button] != InputState::PRESSED
		) ? InputState::PRESSED : this->mouseButtonStates[event.button.button];

	Sping::debugLog("Pressed mouse button");
}

void Sping::Input::mouseButtonReleasedEvent(SDL_Event & event)
{
	this->mouseButtonStates[event.button.button] = (
		this->mouseButtonStates[event.button.button] != InputState::UNHELD ||
		this->mouseButtonStates[event.button.button] != InputState::RELEASED
		) ? InputState::RELEASED : this->mouseButtonStates[event.button.button];
}
