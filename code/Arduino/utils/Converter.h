#pragma once
#include <Arduino.h>

class Converter
{
public:
	Converter();
	int* parse_command(String command, int begin, char delimetr, int params_num);
	int parse_command(String command, int begin, int end);

	String int_array_to_string(int* arr, int size, char delimiter);
	~Converter();
};
