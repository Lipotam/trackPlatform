#include "ComPort.h"



ComPort::ComPort()
{
	
}


DWORD WINAPI readProc(LPVOID p) {
	while (true) {
		if (ReadFile(hCom, pbuf, 1, &bytesRead, 0) && bytesRead > 0) {
			printf("msg-%s-end %d\n", pbuf, bytesRead);
		}
		if (bytesRead>0)
		{
			WriteFile(hCom, pbuf++, 1, &bWritten, NULL);
			counter++;
			if (counter == 10) {
				SetEvent(hEvent);
				buf[counter] = '\0';
				counter = 0;
				pbuf = buf;
			}
		}
	}
}


VOID WINAPI ComPort::writeProc(PVOID* p) {

}


bool ComPort::init(char* portName) {
	this->portName = portName;
	hCom = CreateFile(strcat("\\\\.\\", portName), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (hCom == INVALID_HANDLE_VALUE) {
		printf("Ошибка открытия %s\n", portName);
		return false;
	}

	GetCommState(hCom, &dcb);
	dcb.BaudRate = CBR_9600;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	fSuccess = SetCommState(hCom, &dcb);

	if (!fSuccess) {
		printf("Попытка вызвать SetCommState провалилась!\n");
		return false;
	}
	printf("%s успешно сконфигурирован\n", portName);
	GetCommState(hCom, &dcb);
	printf("Скорость порта %s равна %d\n", portName, dcb.BaudRate);

	return true;
}

void ComPort::send() {

}

string ComPort::read() {

}

void ComPort::createReadThread() {
	readThread = CreateThread(NULL, 0, readProc,54
		&dwParam, 0, &dwThreadReadId);
}

void ComPort::createWriteThread() {
	writeThread = CreateThread(NULL, 0, writeProc,
		&dwParam, 0, &dwThreadWriteId);
}

void ComPort::initThreads() {
	this->createReadThread();
	this->createWriteThread();
}

void ComPort::closePort() {
	CloseHandle(hCom);
}

ComPort::~ComPort()
{
}
