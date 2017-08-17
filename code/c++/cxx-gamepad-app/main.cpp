#include <iostream>
#include <string>

#include "GamepadManager.h"
#include "ConnectionModes.h"
#include "TrackPlatform_Manager.h"

int main(int argc, char* argv[])
{
	std::string rtx = "COM13";
	uint32_t baudrate = 9600U;

	std::cout << "rx = tx = " << rtx << "; baudrate = " << baudrate << std::endl;

	try
	{
		TrackPlatform_Manager trackPlatform(bluetooth, rtx, rtx, baudrate);
		GamepadManager manager(&trackPlatform);
		manager.run();
	}
	catch(...)
	{
		std::cout << "Exception was catched" << std::endl;
		return 1;
	}

	return 0;
}

