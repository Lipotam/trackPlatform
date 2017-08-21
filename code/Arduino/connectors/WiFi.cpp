#include "WiFi.h"

WiFi::WiFi(unsigned long speed) : ConnectingDevice(&Serial2)
{
	if (isInited)
	{
		return;
	}
	isInited = true;
	Serial2.begin(speed);
	if (CheckOnReady())
	{
		ChangeSpeed(speed);
	}
}

WiFi::~WiFi()
{
}

bool WiFi::CheckOnReady()
{
	StartingSend("AT");
	if (ready = (read() == "AT\r\nOK") == ReturningCommandsOff())
	{
		return ready;
	}
	else
	{
		Reset();
	}
}

bool WiFi::ReturningCommandsOff()
{
	StartingSend("ATE0");
	if (CheckOnAnswer())
	{
		return true;
	}
	else
	{
		FatalError();
	}
}

void WiFi::FatalError()
{
	ready = false;
}

bool WiFi::CheckOnAnswer()
{
	if (read() != "\r\nOK")
	{
		return true;
	}
	else
	{
		FatalError();
	}
}

bool WiFi::Reset()
{
	StartingSend("AT+RST");
	if (ready = (read() == "AT+RST\r\nOK") == ReturningCommandsOff())
	{
		return ready;
	}
	else
	{
		FatalError();
	}
}

bool WiFi::Reset(unsigned long speed)
{
	if (Reset())
	{
		ChangeSpeed(speed);
	}
}

bool WiFi::ChangeSpeed(unsigned long speed)
{
	send("AT+CIOBAUD=" + String(speed));
	CheckOnAnswer();
}

String WiFi::VersionCheck()
{
	send("AT+GMR");
	return ReturnInfo();
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
		FatalError();
	}
}

String WiFi::CheckIPandMAC()
{
	send("AT+CIFSR");
	CheckOnAnswer();
	return ReturnInfo();
}

bool WiFi::CreateCurrentHost(String name, String password, int port)
{
	Open();
	CheckOnAnswer();
	send("AT+CWSAP_CUR=" + name + "," + password + ",5,3");
	CheckOnAnswer();
	UseTCP(port);
}

bool WiFi::CreateStaticHost(String name, String password, int port)
{
	Open();
	CheckOnAnswer();
	send("AT+CWSAP_DEF=" + name + "," + password + ",5,3");
	CheckOnAnswer();
	UseTCP(port);
}

bool WiFi::Open()
{
	send("AT+CWMODE_CUR=2");
	CheckOnAnswer();
	opened = true;
}

String WiFi::NetsList()
{
	Close();
	send("AT+CWLAP");
	return ReturnInfo();
}

bool WiFi::Close()
{
	send("AT+CWMODE_CUR=1");
	CheckOnAnswer();
	opened = false;
}

bool WiFi::UseTCP(int port)
{
	send("AT+CIPMUX=1");
	CheckOnAnswer();
	send("AT+CIPSERVER=1," + String(port));
	CheckOnAnswer();
}

void WiFi::StartingSend(String command)
{
	ConnectingDevice::send(command + "\r\n");
}

void WiFi::Send(String command)
{
	if (ready)
	{
		ConnectingDevice::send(command + "\r\n");
	}
	else
	{
		FatalError();
	}
}

String WiFi::Scan()
{
	delay(100);
	return ConnectingDevice::read();
}

String WiFi::CheckStatus()
{
	String response = "";
	if (isInited)
	{
		response += "Inited";
	}
	if (!isInited)
	{
		response += "Not Inited";
	}
	if (ready)
	{
		response += ", Ready";
	}
	if (!ready)
	{
		response += ", Not Ready";
	}
	if (opened)
	{
		response += ", Opened";
	}
	if (!opened)
	{
		response += ", Closed";
	}
	return response;
}

String WiFi::Write(String message)
{

}

String WiFi::Read()
{

}