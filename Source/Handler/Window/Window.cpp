#include <Handler/Window/Window.h>
#include <Handler/Handler.h>

Sping::Window::Window(Handler &handler) :
	handler(handler)
{
	// TODO: multithreading doesnt work when initting window :(
	this->handler.threadPool->enqueue([=] {
		this->init();
	});

	std::cout << "lol this should happen before window inits\n";
}

Sping::Window::~Window()
{
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
}

void Sping::Window::init()
{
	// TODO: proper read from settings (after it has initialized of course)

	this->window = SDL_CreateWindow("Wololo", 100, 100, 1280, 720, SDL_WINDOW_OPENGL);
	if (this->window == nullptr)
	{
		throw Sping::Err::OH_BOY;
	}
	/*
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_VIDEO_OPENGL);
	if (this->renderer == nullptr)
	{
		throw Sping::Err::OH_BOY;
	}
	*/
	Sping::debugLog("Created the window, in another thread!");
}
