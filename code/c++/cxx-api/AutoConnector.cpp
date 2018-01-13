#include "AutoConnector.h"

AutoConnector::AutoConnector(std::function<void()> c, uint32_t f) : pConnectingThread(nullptr), callback(c),
                                                                    frequency(f)
{
	isRepeat.store(false);
}

AutoConnector::~AutoConnector() {
	stop();
}

void AutoConnector::start() {
	if (!isRepeat.load() && !pConnectingThread)
	{
		Data d;
		d.callback = callback;
		d.pIsRepeat = &isRepeat;
		d.frequency = frequency;
		isRepeat.store(true);
		pConnectingThread = new std::thread([d]() {
			while (d.pIsRepeat->load())
			{
				d.callback();
				std::this_thread::sleep_for(std::chrono::milliseconds(d.frequency));
			}
		});
	}
}

void AutoConnector::stop() {
	if (isRepeat.load() && pConnectingThread) {
		isRepeat.store(false);
		pConnectingThread->join();
		delete pConnectingThread;
		pConnectingThread = nullptr;
	}
}

bool AutoConnector::isConnecting() {
	return isRepeat.load();
}