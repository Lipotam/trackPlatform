#include <iostream>
#include <string>

#if defined(_WIN32)
#include <conio.h>
#else
#include <cstdio>
#define _getche getchar
#endif

#include "TrackPlatform_Manager.h"
#include "platform_dependent/windows/TCPIP_Connector.h"

int main(int argc, char* argv[])
{
	std::string rx = "COM13", tx = "COM13";
	uint32_t baudrate = 9600U;

	/*std::cout << "rx" << std::endl;
	std::cin >> rx;
	std::cout << "tx" << std::endl;
	std::cin >> tx;
	std::cout << "baudrate" << std::endl;
	std::cin >> baudrate;
*/
	std::cout << "rx = " << rx << " tx = " << tx << " baudrate = " << baudrate << std::endl;

	TCPIP_Connector tcpip("127.0.0.1", 3333);

	try
	{
		TrackPlatform_Manager trackPlatform(bluetooth, rx, tx, baudrate);
		bool isExit = false;
		while (!isExit)
		{
			std::cout << "Input command, please (0 to help): ";
			auto c = _getche();
			std::cout << std::endl;

			switch (c)
			{
			case '0':
				std::cout << "0: help" << std::endl;
				std::cout << "q: quit" << std::endl;
				std::cout << "w: move forward" << std::endl;
				std::cout << "s: move back" << std::endl;
				std::cout << "a: turn left (anticlockwise)" << std::endl;
				std::cout << "d: turn right (clockwise)" << std::endl;
				std::cout << " : stop" << std::endl;
				std::cout << "r: get all line values" << std::endl;
				std::cout << "e: get fixed line value" << std::endl;
				std::cout << "t: get all distance values" << std::endl;
				std::cout << "y: get fixed distance value" << std::endl;
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
			case 'r':
			{
				auto arr = trackPlatform.sensorLineGetAllValues();
				for (auto a : arr)
				{
					std::cout << a << std::endl;
				}
				break;
			}
			case 'e':
			{
				std::cout << "Input num: ";
				int a;
				std::cin >> a;
				std::cout << "Value: " << trackPlatform.sensorLineGetValue(a) << std::endl;
				break;
			}
			case 't':
			{
				auto arr = trackPlatform.sensorDistanceGetAllValues();
				for (auto a : arr)
				{
					std::cout << a << std::endl;
				}
				break;
			}
			case 'y':
			{
				std::cout << "Input num: ";
				int a;
				std::cin >> a;
				std::cout << "Value: " << trackPlatform.sensorDistanceGetValue(a) << std::endl;
				break;
			}
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

