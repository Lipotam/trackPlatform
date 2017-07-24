#include <iostream>
#include <string>

#include "TrackPlatform_Manager.h"

int main(int argc, char* argv[])
{
	std::string rx, tx;

	std::cout << "rx" << std::endl;
	std::cin >> rx;
	std::cout << "tx" << std::endl;
	std::cin >> tx;

	std::cout << "rx = " << rx << " tx = " << tx << std::endl;

	try
	{
		TrackPlatform_Manager trackPlatform(bluetooth, rx, tx, 9600U);
	}
	catch(...)
	{
		std::cout << "Exception was catched" << std::endl;
		return 1;
	}

	return 0;
}

