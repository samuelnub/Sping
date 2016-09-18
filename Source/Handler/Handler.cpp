#include <Handler/Handler.h>

// TODO: initializer list
Sping::Handler::Handler() :
	threadPool(std::make_unique<Sping::ThreadPool>(Sping::THREAD_COUNT))
{
}

Sping::Handler::~Handler()
{
}

void Sping::Handler::tick()
{
}
