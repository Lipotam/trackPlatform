#include "BluetoothConnector.h"

BluetoothConnector::BluetoothConnector(const std::string& rx, const std::string& tx, uint32_t baudRate)
	: TrackPlatform_BasicConnector(rx, tx, baudRate), readPort(new serial::Serial(rx, baudRate)), writePort((rx == tx) ? readPort : new serial::Serial(tx, baudRate))
{
}

BluetoothConnector::~BluetoothConnector()
{
	if (readPort != writePort)
	{
		delete writePort;
	}
	delete readPort;
}

std::string BluetoothConnector::read()
{
	return readPort->read(messageMaxSize);
}

void BluetoothConnector::write(const std::string& s)
{
	writePort->write(s);
}

bool BluetoothConnector::isConnected()
{
	return (readPort->isOpen() && writePort->isOpen());
}
