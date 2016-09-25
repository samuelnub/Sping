#include <Util/Constants.h>

void Sping::debugLog(const std::string & message)
{
	if (Sping::DEBUG)
	{
		std::cout << message << "\n";
	}
}
