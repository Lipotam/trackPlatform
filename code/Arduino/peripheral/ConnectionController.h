#pragma once
#include "../connectors/USB.h"
#include "../connectors/Bluetooth.h"
#include "../connectors/WiFi.h"

class ConnectionController
{
	USB* usb = nullptr;
	Bluetooth* bluetooth = nullptr;
	WiFi* wifi = nullptr;
	ConnectingDevice *device = nullptr;

	static const char connectCommand[];
	static const char disconnectCommand[];

	bool isConnected = false;

public:
	ConnectionController();

	void waitForConnection();
	ConnectingDevice* getDevice() const;
	String getCommand();
};
