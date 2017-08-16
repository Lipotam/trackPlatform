#include "WiFi.h"



WiFi::WiFi(int rx, int tx, int speed) : ConnectingDevice(rx, tx, speed)
{
	if (Check())
	{
		ChangeSpeed(speed);
	}
	else
	{
		Reset(speed);
	}
}

WiFi::~WiFi()
{
}

String WiFi::VersionCheck()
{
	send("AT+GMR");
	return read();
}

String WiFi::CheckIPandMAC()
{
	send("AT+CIFSR");
	return read();
}

void WiFi::ChangeSpeed(int speed)
{
	if (ready)
	{
		send("AT+CIOBAUD=" + String(speed));
	}
}

bool WiFi::Reset()
{
	send("AT+RST");
	ready = (read() == "OK");
	return ready;
}

bool WiFi::Reset(int speed)
{
	ready = Reset();
	ChangeSpeed(speed);
	return ready;
}

void WiFi::CreateCurrentHost(String name, String password, int port)
{
	if (ready)
	{
		if (!opened)
		{
			Open();
		}
		send("AT+CWSAP_CUR=" + name + "," + password + ",5,3");
		UseTCP(port);
	}
}

void WiFi::CreateStaticHost(String name, String password, int port)
{
	if (ready)
	{
		if (!opened)
		{
			Open();
		}
		send("AT+CWSAP_DEF=" + name + "," + password + ",5,3");
		UseTCP(port);
	}
}

String WiFi::NetsList()
{
	if (ready)
	{
		if (opened)
		{
			Close();
		}
		send("AT+CWLAP");
		return read();
	}
}

void WiFi::Close()
{
	send("AT+CWMODE_CUR=1");
	opened = false;
}

void WiFi::Open()
{
	send("AT+CWMODE_CUR=2");
	opened = true;
}

void WiFi::UseTCP(int port)
{
	send("AT+CIPMUX=1");
	send("AT+CIPSERVER=1," + String(port));
}

bool WiFi::Check()
{
	send("AT");
	ready = (read() == "OK");
	return ready;
}

void WiFi::send(String command)
{
	ConnectingDevice::send(command + "\r\n");
}