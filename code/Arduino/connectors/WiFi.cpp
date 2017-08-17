#include "WiFi.h"

bool WiFi::isInited = false;

WiFi::WiFi(unsigned long speed) : ConnectingDevice(&Serial2)
{
	if (isInited)
	{
		return;
	}

	isInited = true;
	Serial2.begin(speed);

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

void WiFi::ChangeSpeed(unsigned long speed)
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

bool WiFi::Reset(unsigned long speed)
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