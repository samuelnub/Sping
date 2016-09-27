#include <Handler/Handler.h>

// TODO: initializer list
Sping::Handler::Handler() :
	threadPool(std::make_unique<Sping::ThreadPool>(Sping::THREAD_COUNT)),
	settings(std::make_unique<Sping::Settings>(*this)),
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