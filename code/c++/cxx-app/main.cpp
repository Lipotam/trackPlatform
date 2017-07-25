#include <iostream>
#include <string>

#if defined(_WIN32)
#include <conio.h>
#endif

#include "TrackPlatform_Manager.h"

int main(int argc, char* argv[])
{
	std::string rx = "COM10", tx = "COM10";
	uint32_t baudrate = 9600U;

	/*std::cout << "rx" << std::endl;
	std::cin >> rx;
	std::cout << "tx" << std::endl;
	std::cin >> tx;
	std::cout << "baudrate" << std::endl;
	std::cin >> baudrate;
*/
	std::cout << "rx = " << rx << " tx = " << tx << " baudrate = " << baudrate << std::endl;

	try
	{
		TrackPlatform_Manager trackPlatform(bluetooth, rx, tx, baudrate);
		bool isExit = false;
		while (!isExit)
		{
			auto c = _getche();

			switch (c)
			{
			case '0':
				std::cout << "0: help";
				std::cout << "q: quit";
				std::cout << "w: move forward";
				std::cout << "s: move back";
				std::cout << "a: turn left (anticlockwise)";
				std::cout << "d: turn right (clockwise)";
				std::cout << " : stop";
				break;
			case 'q':
				isExit = true;
				break;
			case 'w':
				trackPlatform.moveForward();
				break;
			case 'a':
				trackPlatform.moveBackward();
				break;
			case 's':
				trackPlatform.rotateAntiClockwise();
				break;
			case 'd':
				trackPlatform.rotateClockwise();
				break;
			case ' ':
				trackPlatform.moveStopAll();
				break;
			default: break;
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

