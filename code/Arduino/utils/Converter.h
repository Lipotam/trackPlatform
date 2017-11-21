#pragma once
#include <Arduino.h>
#include "../config/Constants.h"

class Converter
{
public:
	Constants constants;
	Converter();
	int* parse_command(String command, int begin, char delimetr, int paramsLength);
	int parse_command(String command, int begin, int end);

	String intArrayToString(int*, int);
	~Converter();
};
