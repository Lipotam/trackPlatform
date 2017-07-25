#pragma once
#include <Arduino.h>
#include "..\Constants.h"

class MainController
{
public:
	Constants constants;
	MainController();
	int* parse_command(String command, int begin, char delimetr, int paramsLength);
	int parse_command(String command, int begin, int end);

	String intArrayToString(int*, int);
	~MainController();
};
