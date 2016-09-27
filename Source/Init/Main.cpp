#include <iostream>
#include <Util/Constants.h>
#include <Game/Game.h>

int main(int argc, char *args[])
{
	std::cout << "Hi!\n";

	try
	{
		Sping::Game Game;
	}
	catch (Sping::Err err)
	{
		Sping::debugLog({ "Ey doe, caught an exception with an ID of " + std::to_string(static_cast<int>(err)) });
	}

	std::cout << "Bye!\n";

	return 0;
}