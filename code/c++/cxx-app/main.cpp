#include <iostream>
#include <string>

#if defined(_WIN32)
#include <conio.h>
#endif

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
		while (true)
		{
			char c = _getch();
			if (c == '\b')				//Backspace escape symbol
			{
				std::cout << "Back";
				break;
			}

			switch (c)
			{
			case 'w':
				trackPlatform.moveForward();
				break;
			case 's':
				trackPlatform.moveBackward();
				break;
			case ' ':
				trackPlatform.moveStopAll();
				break;
			default:
				break;
			}
		}
	}
	catch(...)
	{
		std::cout << "Exception was catched" << std::endl;
		return 1;
	}

	return 0;
}

