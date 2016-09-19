#include <Handler/Window/Window.h>
#include <Handler/Handler.h>

Sping::Window::Window(Handler & handler) :
	handler(handler)
{
	this->handler.threadPool->enqueue([=] {
		this->init();
	});
}

Sping::Window::~Window()
{
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
}

void Sping::Window::init()
{
	// TODO: proper read from settings (after it has initialized of course)

	this->window = SDL_CreateWindow("Wololo", 100, 100, 1280, 720, NULL);
	if (this->window == nullptr)
	{
		throw Sping::Err::OH_BOY;
	}
}
