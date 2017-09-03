#pragma once
#include <iostream>
#include <windows.h>
#include <ctime>
#include <atomic>
#include "TrackPlatform_Manager.h"

struct Data {
	std::atomic_bool* pIsRepeat;
	TrackPlatform_Manager* pTrackPlatform;
	uint32_t frequency;
};
unsigned int threadFun(Data* data);

class AutoConnector {
private:
	HANDLE connectingThread;
	TrackPlatform_Manager* pTrackPlatform;
	std::atomic_bool isRepeat;
	uint32_t frequency;

public:
	AutoConnector(TrackPlatform_Manager& tp, uint32_t f = reconnectTime);
	void start();
	void stop();
	bool isConnecting();
	static const uint32_t reconnectTime = 1000;
};