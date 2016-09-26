#include <Util/Constants.h>

void Sping::debugLog(const std::string & message)
{
	if (Sping::SPING_DEBUG == true)
	{
		std::cout << message << "\n";
	}
}
