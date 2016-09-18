#include <Game/Game.h>
#include <Util/Constants.h>

// TODO: use initializer lists instead (they initialize in the order they're in in your declaration, not here, so just mirror it
Sping::Game::Game() :
	handler(std::make_unique<Handler>())
{
	for (int i = 0; i < 100000000; i++)
	{
		this->tick();
	}
}

Sping::Game::~Game()
{
	// Proper RAII shouldn't have "shutdown()", they should handle themselves in their own destructor
}

void Sping::Game::tick()
{
	this->handler->tick();
}
