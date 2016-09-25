#include <Handler/Handler.h>

// TODO: initializer list
Sping::Handler::Handler() :
	threadPool(std::make_unique<Sping::ThreadPool>(Sping::THREAD_COUNT)),
	input(std::make_unique<Sping::Input>(*this)),
	window(std::make_unique<Sping::Window>(*this))
{
}

Sping::Handler::~Handler()
{
}

void Sping::Handler::tick()
{
	input->tick();
}