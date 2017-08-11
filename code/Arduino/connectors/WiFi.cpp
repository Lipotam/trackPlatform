#include "WiFi.h"



WiFi::WiFi(int rx, int tx, int speed) : ConnectingDevice(rx, tx, speed)
{
	Check();
	ChangeSpeed(speed);
}

WiFi::~WiFi()
{
}

String WiFi::VersionCheck()
{
	send("AT+GMR");
	return read();
}

String CheckIPandMAC()
{
	send("AT+CIFSR");
	return read();
}

void WiFi::ChangeSpeed(int speed)
{
	if (ready)
	{
		send("AT+CIOBAUD=" + speed);
	}
}

void WiFi::Reset(int speed)
{
	send("AT+RST");
	Check();
	ChangeSpeed(speed);
}

void WiFi::CurrentLog(String name, String password, int port)
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

void WiFi::StaticLog(String name, String password, int port)
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
	send("AT+CIPSERVER=1," + port);
}

void WiFi::Check()
{
	send("AT");
	if (read() == "OK")
	{
		ready = true;
		Close();
	}
	else
	{
		ready = false;
	}
}

