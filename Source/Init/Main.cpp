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
		std::cout << "Caught an exception! " << static_cast<int>(err) << "\n";
	}

	std::cout << "Bye!\n";

	return 0;
}