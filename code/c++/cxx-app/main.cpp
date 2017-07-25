#include <iostream>
#include <string>

#if defined(_WIN32)
#include <conio.h>
#endif

//#include "TrackPlatform_Manager.h"
#include "SerialConnector.h"

int main(int argc, char* argv[])
{
	std::string rx = "COM6", tx = "COM6";
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
		SerialConnector connector(rx, tx, baudrate);
		//TrackPlatform_Manager trackPlatform(bluetooth, rx, tx, baudrate);
		while (true)
		{
			std::string s;
			std::cout << "Request: ";
			std::cin >> s;
			while (std::cin.get() != '\n'){ }
			if (s == "quit")
			{
				break;
			}
			connector.write(s);
			std::cout << "Answer: " << connector.read() << std::endl;
		}
	}
	catch(...)
	{
		std::cout << "Exception was catched" << std::endl;
		return 1;
	}

	return 0;
}

