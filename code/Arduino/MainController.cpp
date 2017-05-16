#include "MainController.h"

MainController::MainController() {

}


int* MainController::parse_command(String command, int begin, char delimetr, int paramsLength) {
	int* arr = new int[paramsLength];
	for (int i = 0; i < paramsLength; i++) {
		int delimetrPos = command.indexOf(delimetr);
		if (delimetrPos >= 0) {
			arr[i] = command.substring(begin, delimetrPos).toInt();
			begin = delimetrPos + 1;
			command = command.substring(begin, command.length());
		}
	}
	return arr;
}

int MainController::parse_command(String command, int begin, int end) {
	return command.substring(begin, end).toInt();
}

MainController::~MainController() {

}