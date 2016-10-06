#include <Game/Game.h>
#include <Util/Constants.h>
#include <Util/Test/TestData.h> // TODO: test lol

// TODO: use initializer lists instead (they initialize in the order they're in in your declaration, not here, so just mirror it
Sping::Game::Game() :
	handler(std::make_unique<Sping::Handler>()),
	renderer(std::make_unique<Sping::Renderer>(*handler))
{
	this->renderer->meshManager->load(
		Sping::ROOT_DIR,
		Sping::Test::vertices,
		Sping::Test::indices,
		Sping::GLDrawUsage::DYNAMIC,
		false
		);

	while(true)
	{
		this->tick();
	}
}

Sping::Game::~Game()
{
}

void Sping::Game::tick()
{
	this->handler->tick();

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	SDL_GL_SwapWindow(this->handler->window->getWindow());
}
