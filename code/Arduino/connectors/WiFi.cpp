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

bool WiFi::ReturningCommandsOff()
{
	try
	{
		send("ATE0");
	}
	catch (...)
	{
		return false;
	}
	return true;
}

String WiFi::VersionCheck()
{
	try
	{
		send("AT+GMR");
		return ReturnInfo();
	}
	catch (...)
	{
		return "";
	}
}

String WiFi::CheckIPandMAC()
{
	try
	{
		send("AT+CIFSR");
		ReturnCheck();
		return ReturnInfo();
	}
	catch (...)
	{
		return "";
	}
}

bool WiFi::ChangeSpeed(int speed)
{
	try
	{
		send("AT+CIOBAUD=" + String(speed));
		ReturnCheck();
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool WiFi::Reset()
{
	send("AT+RST");
	if (ready = (read() == "AT+RST\r\nOK") == ReturningCommandsOff())
	{
		return ready;
	}
	else
	{
		return;
	}
}

bool WiFi::Reset(int speed)
{
	ready = Reset();
	ChangeSpeed(speed);
	return ready;
}

bool WiFi::CreateCurrentHost(String name, String password, int port)
{
	try
	{
		Open();
		ReturnCheck();
		send("AT+CWSAP_CUR=" + name + "," + password + ",5,3");
		ReturnCheck();
		UseTCP(port);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool WiFi::CreateStaticHost(String name, String password, int port)
{
	try
	{
		Open();
		ReturnCheck();
		send("AT+CWSAP_DEF=" + name + "," + password + ",5,3");
		ReturnCheck();
		UseTCP(port);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

String WiFi::NetsList()
{
	try
	{
		if (opened)
		{
			Close();
		}
		send("AT+CWLAP");
		return ReturnInfo();
	}
	catch (...)
	{
		return "";
	}
}

bool WiFi::Close()
{
	try
	{
		send("AT+CWMODE_CUR=1");
		ReturnCheck();
		opened = false;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool WiFi::Open()
{
	try
	{
		send("AT+CWMODE_CUR=2");
		ReturnCheck();
		opened = true;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool WiFi::UseTCP(int port)
{
	try
	{
		send("AT+CIPMUX=1");
		ReturnCheck();
		send("AT+CIPSERVER=1," + String(port));
		ReturnCheck();
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool WiFi::Check()
{
	send("AT");
	if (ready = (read() == "AT\r\nOK") == ReturningCommandsOff())
	{
		return ready;
	}
	else
	{
		Reset();
	}
}

void WiFi::ReturnCheck()
{
	if (read() != "\r\nOK")
	{
		throw 1;
	}
}

String WiFi::ReturnInfo()
{
	String str = read();
	if (int a = str.indexOf("\r\nOK"))
	{
		return str.substring(0, a);
	}
	else
	{
		throw 1;
	}
}

void WiFi::send(String command)
{
	if (ready)
	{
		ConnectingDevice::send(command + "\r\n");
	}
	else
	{
		throw 1;
	}
}

String WiFi::read()
{
	delay(100);
	return ConnectingDevice::read();
}