#pragma once
#include <iostream>
#include <string.h>
#include <windows.h> <WINDOWS.H>
#include <strsafe.h> <STRSAFE.H>
#include <stdio.h><STDIO.H>
using namespace std;

class ComPort
{
private:
	char* portName;
	DCB dcb;
	BOOL fSuccess;
	HANDLE readThread;
	HANDLE writeThread;
	DWORD dwParam, dwThreadReadId, dwThreadWriteId;

public:
	HANDLE hCom;
	ComPort();
	bool init(char* portName);
	void send();
	string read();
	void createReadThread();
	void createWriteThread();
	void initThreads();
	//DWORD WINAPI readProc(LPVOID);
	DWORD WINAPI writeProc(LPVOID);
	void closePort();
	~ComPort();
};

