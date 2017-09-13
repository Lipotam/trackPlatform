#include "MainController.h"

MainController::MainController() {

}


int* MainController::parse_command(String command, int begin, char delimetr, int paramsLength) {
	int* arr = new int[paramsLength];
	// clean all allocated memory (can use memset from cstdlib)
	for (int i = 0; i < paramsLength; ++i)
	{
		arr[i] = 0;
	}

	command = command.substring(begin);
	begin = 0;
	int delimetrPos = command.indexOf(delimetr);
	for (int i = 0; (i < paramsLength); i++) {
		if ((delimetrPos < 0))
		{
			arr[i] = command.substring(begin).toInt();
			break;
		}
		arr[i] = command.substring(begin, delimetrPos).toInt();
		command = command.substring(delimetrPos + 1);
		begin = 0;
		delimetrPos = command.indexOf(delimetr);
	}
	return arr;
}

int MainController::parse_command(String command, int begin, int end) {
	return command.substring(begin, end).toInt();
}


String MainController::intArrayToString(int* array, int size) {
	String str = "";
	for (int i = 0; i < size; i++) {
		str += String(array[i]);
		str += constants.commands_delimetr;
	}
	if (size > 0)
	{
		str = str.substring(0, str.length() - 1);
	}
	return str;
}


MainController::~MainController() {

}