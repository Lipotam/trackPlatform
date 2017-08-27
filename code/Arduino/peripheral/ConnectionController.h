#pragma once
#include "../connectors/USB.h"
#include "../connectors/Bluetooth.h"
#include "../connectors/WiFi.h"
#include "../CommandsEnum.h"

class ConnectionController
{
	USB* usb = nullptr;
	Bluetooth* bluetooth = nullptr;
	WiFi* wifi = nullptr;
	ConnectingDevice *device = nullptr;

	static const char connectCommand[];
	static const char disconnectCommand[];
	static const StartCommands lowestAPI = startBasicAPI;
	static const StartCommands highestAPI = APIWithAnswer;

	bool isConnected = false;
	StartCommands connectedAPIversion;

public:
	ConnectionController();
	~ConnectionController();

	void waitForConnection();
	ConnectingDevice* getDevice() const;
	String getCommand();
};
