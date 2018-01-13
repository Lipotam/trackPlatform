#include "Converter.h"

Converter::Converter() {

}


int* Converter::parse_command(String command, int begin, char delimetr, int params_num) {
	int* arr = new int[params_num];
	// clean all allocated memory (can use memset from cstdlib)
	for (int i = 0; i < params_num; ++i)
	{
		arr[i] = 0;
	}

	command = command.substring(begin);
	begin = 0;
	int delimetr_pos = command.indexOf(delimetr);
	for (int i = 0; (i < params_num); i++) {
		if ((delimetr_pos < 0))
		{
			arr[i] = command.substring(begin).toInt();
			break;
		}
		arr[i] = command.substring(begin, delimetr_pos).toInt();
		command = command.substring(delimetr_pos + 1);
		begin = 0;
		delimetr_pos = command.indexOf(delimetr);
	}
	return arr;
}

int Converter::parse_command(String command, int begin, int end) {
	return command.substring(begin, end).toInt();
}


String Converter::int_array_to_string(int* arr, int size, char delimiter) {
	String str;
	for (int i = 0; i < size; i++) {
		if (i > 0)
		{
			str += delimiter;
		}
		str += String(arr[i]);
	}
	return str;
}


Converter::~Converter() {

}