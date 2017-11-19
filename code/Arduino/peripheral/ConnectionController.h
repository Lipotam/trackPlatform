#pragma once
#include "../connection/USB.h"
#include "../connection/Bluetooth.h"
#include "../connection/WiFi.h"
#include "../config/CommandsEnum.h"
#include "../utils/Timer.h"

class ConnectionController
{
	USB* usb = nullptr;
	Bluetooth* bluetooth = nullptr;
	WiFi* wifi = nullptr;
	ConnectingDevice *device = nullptr;

	static const char connectCommand[];
	static const char disconnectCommand[];
	static const char refreshCommand[];
	static const StartCommands lowestAPI = startBasicAPI;
	static const StartCommands highestAPI = APIWithCRC;

	bool isConnected = false;
	StartCommands connectedAPIversion;

	bool waitForCommandOnDevice(Timer* timer);

public:
	ConnectionController();
	~ConnectionController();

	void waitForConnection();
	ConnectingDevice* getDevice() const;
	String getCommand();
};
