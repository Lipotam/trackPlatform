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

	TrackPlatform_Manager trackPlatform(bluetooth, rx, tx, 9600);

	return 0;
}

