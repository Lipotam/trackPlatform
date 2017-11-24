#pragma once
#include "../connectors/USB.h"
#include "../connectors/Bluetooth.h"
#include "../connectors/WiFi_my.h"
#include "../CommandsEnum.h"
#include "../utils/Timer.h"

class ConnectionController
{
	USB* usb = nullptr;
	Bluetooth* bluetooth = nullptr;
	WiFi_my* wifi = nullptr;
	ConnectingDevice *device = nullptr;

	static const char connectCommand[];
	static const char disconnectCommand[];
	static const char refreshCommand[];
	static const StartCommands lowestAPI = startBasicAPI;
	static const StartCommands highestAPI = APIWithAutoDiconnect;

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
