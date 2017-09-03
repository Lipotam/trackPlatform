#include "AutoConnector.h"

unsigned int threadFun(Data* data) {
	while ((data->pIsRepeat)->load()) {
		uint32_t startTime = clock();
		uint32_t endTime = startTime + ((double)data->frequency) / 1000 * CLOCKS_PER_SEC;
		while (clock() < endTime && (data->pIsRepeat)->load()) {
			Sleep(1);
		}
		data->pTrackPlatform->sensorLineGetAllValues();
	}
	return 0;
}

AutoConnector::AutoConnector(TrackPlatform_Manager& tp, uint32_t f) : pTrackPlatform(&tp), frequency(f) {
	isRepeat.store(false);
}

void AutoConnector::start() {
	if (!isRepeat.load())
	{
		Data *d = new Data();
		d->pIsRepeat = &isRepeat;
		d->pTrackPlatform = pTrackPlatform;
		d->frequency = frequency;
		isRepeat.store(true);
		connectingThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&threadFun, (LPVOID)d, 0, NULL);
	}
}

void AutoConnector::stop() {
	if (isRepeat.load()) {
		isRepeat.store(false);
		WaitForSingleObject(connectingThread, INFINITE);
	}
}

bool AutoConnector::isConnecting() {
	return isRepeat.load();
}