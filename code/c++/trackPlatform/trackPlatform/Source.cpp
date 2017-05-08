#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <locale.h>
char buf[128];
char* pbuf = buf;
int counter = 0;

HANDLE hCom, hEvent;
DWORD bytesRead, bWritten;

BOOL fSuccess;
HANDLE hThread;
DWORD dwParam, dwThreadId;

VOID WINAPI ThreadProc(PVOID* dummy) {
	printf("Ждите данные из порта СОМ12...\n");
	while (true) {
		if(ReadFile(hCom, pbuf, 1, &bytesRead, 0) && bytesRead > 0) {
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

int main() {
	setlocale(LC_ALL, "Russian");
	char* pcComPort = "СОМ12";
	DCB dcb;
	FILE* fout;
	hCom = CreateFile("\\\\.\\COM12", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (hCom == INVALID_HANDLE_VALUE) {
		printf("Ошибка открытия COM12!\n");
		while (!kbhit());
		return 1;
	}
	GetCommState(hCom, &dcb);
	dcb.BaudRate = CBR_9600;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	fSuccess = SetCommState(hCom, &dcb);
	if (!fSuccess) {
		printf("Попытка вызвать SetCommState провалилась!\n");
		while (!kbhit());
		return 1;
	}
	printf("COM порт %s успешно сконфигурирован\n", pcComPort);
	GetCommState(hCom, &dcb);
	printf("Скорость порта %s равна %d\n", pcComPort, dcb.BaudRate);

	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc,
		&dwParam, 0, &dwThreadId);
	if ((fout = fopen("F:\\test.txt", "a+")) == NULL) {
		printf("Не могу создать файл F:\\test");
		while (!kbhit());
		return 1;
	}
	printf("Нажмите клавишу для выхода...\n");
	do {
		WaitForSingleObject(hEvent, INFINITE);
		printf("%s\n", buf);
		fwrite(buf, sizeof(char), 10, fout);
	} while (!kbhit());
	fclose(fout);
	CloseHandle(hCom);
	return 0;
}