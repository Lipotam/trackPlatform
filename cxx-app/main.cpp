#include <iostream>
#include <string>

#if defined(_WIN32)
#include <conio.h>
#else
#include <cstdio>
#define _getche getchar
#endif

#include "TrackPlatform_Manager.h"
#include "SensorsViewer.h"
#include "ConsolePlatformConnector.h"

int main(int argc, char* argv[])
{
	TrackPlatform_Manager* trackPlatform = nullptr;
	int errorCode = 0;
	try 
	{
		ConsolePlatformConnector platformConnector;
		trackPlatform = platformConnector.connect();
		if (!trackPlatform)
		{
			return 2;
		}

		std::cout << "Connected" << std::endl;

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
				std::cout << "u: show line sensors" << std::endl;
				std::cout << "t: get all distance values" << std::endl;
				std::cout << "y: get fixed distance value" << std::endl;
				std::cout << "i: show distance sensors" << std::endl;
				std::cout << "g: set horisontal servo angle in degree" << std::endl;
				std::cout << "h: set vertical servo angle in degree" << std::endl;
				break;
			case 'q':
				isExit = true;
				break;
			case 'w':
				trackPlatform->moveForward();
				break;
			case 's':
				trackPlatform->moveBackward();
				break;
			case 'a':
				trackPlatform->rotateAntiClockwise();
				break;
			case 'd':
				trackPlatform->rotateClockwise();
				break;
			case ' ':
				trackPlatform->moveStopAll();
				break;
			case 'r':
			{
				auto arr = trackPlatform->sensorLineGetAllValues();
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
				std::cout << "Value: " << trackPlatform->sensorLineGetValue(a) << std::endl;
				break;
			}
			case 'u':
			{
				SensorsViewer sv;
				auto arr = trackPlatform->sensorLineGetAllValues();
				sv.setData(arr, LINE_SENSORS);
				std::cout << std::endl;
				sv.show();
			}
			case 't':
			{
				auto arr = trackPlatform->sensorDistanceGetAllValues();
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
				std::cout << "Value: " << trackPlatform->sensorDistanceGetValue(a) << std::endl;
				break;
			}
			case 'i':
			{
				SensorsViewer sv;
				auto arr = trackPlatform->sensorDistanceGetAllValues();
				sv.setData(arr, DISTANCE_SENSORS);
				std::cout << std::endl;
				sv.show();
			}
			case 'g':
			{
				std::cout << "Input num: ";
				int a;
				std::cin >> a;
				trackPlatform->servoSetHorizontalAngle(a);
				break;
			}
			case 'h':
			{
				std::cout << "Input num: ";
				int a;
				std::cin >> a;
				trackPlatform->servoSetVerticalAngle(a);
				break;
			}
			default: break;
			}
		}
	}
	catch (...)
	{
		std::cout << "Exception was catched" << std::endl;
		errorCode = 1;
	}

	if (trackPlatform)
	{
		delete trackPlatform;
	}
	return errorCode;
}

