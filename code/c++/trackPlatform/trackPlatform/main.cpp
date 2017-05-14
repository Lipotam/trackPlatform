#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include "ComPort.h"
#include "Commands.h"
#include "Menu.h"
#include <iostream>
#include <string>
using namespace std;

char buf[128];
char* pbuf = buf;
int counter = 0;

ComPort comPort;
HANDLE hEvent;
DWORD bytesRead, bWritten;

HANDLE hThread;



int main() {
	setlocale(LC_ALL, "Russian");
	
	char* portName;
	cout << "Input port name: ";
	cin >> portName;
	
	if (!comPort.init(portName)) {
		return 0;
	}

	comPort.initThreads();

	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	

	comPort.closePort();
	return 0;
}