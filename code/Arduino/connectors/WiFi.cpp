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
	if (ready = (Scan() == "AT\r\nOK") == ReturningCommandsOff())
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
	if (Scan() == "ATE0\r\nOK")
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
	IDCount = -1;
	ready = false;
	opened = false;
}

bool WiFi::CheckOnAnswer()
{
	if (Scan() = "\r\nOK")
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
	IDCount = -1;
	ready = false;
	opened = false;
	StartingSend("AT+RST");
	if (ready = (Scan() == "AT+RST\r\nOK") == ReturningCommandsOff())
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
	Send("AT+CIOBAUD=" + String(speed));
	CheckOnAnswer();
}

String WiFi::VersionCheck()
{
	Send("AT+GMR");
	return ReturnInfo();
}

String WiFi::ReturnInfo()
{
	String str = Scan();
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
	Send("AT+CIFSR");
	CheckOnAnswer();
	return ReturnInfo();
}

bool WiFi::CreateCurrentHost(String name, String password, int port)
{
	Open();
	CheckOnAnswer();
	Send("AT+CWSAP_CUR=" + name + "," + password + ",5,3");
	CheckOnAnswer();
	UseTCP(port);
}

bool WiFi::CreateStaticHost(String name, String password, int port)
{
	Open();
	CheckOnAnswer();
	Send("AT+CWSAP_DEF=" + name + "," + password + ",5,3");
	CheckOnAnswer();
	UseTCP(port);
}

bool WiFi::Open()
{
	Send("AT+CWMODE_CUR=2");
	CheckOnAnswer();
	opened = true;
}

String WiFi::NetsList()
{
	Close();
	Send("AT+CWLAP");
	return ReturnInfo();
}

bool WiFi::Close()
{
	Send("AT+CWMODE_CUR=1");
	CheckOnAnswer();
	opened = false;
}

bool WiFi::UseTCP(int port)
{
	Send("AT+CIPMUX=1");
	CheckOnAnswer();
	Send("AT+CIPSERVER=1," + String(port));
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
	String responce = ConnectingDevice::read();
	if (responce.indexOf(",CONNECT") == 1)
	{
		String ID = responce.substring(0, 1);
		if ((atoi(ID.c_str()) - 1) == IDCount)
		{
			IDCount++;
			Scan();
		}
		else
		{
			FatalError();
		}
	}
	if (responce.indexOf("/r/n+IPD,") == 0)
	{
		String ID = responce.substring(7, 1);
		String message = responce.substring(9, sizeof(responce) - 9);
		String answer;
		if (sizeof(message) < 11)
		{
			answer = message.substring(2, sizeof(message) - 4);
			return answer;
		}
		if (11 <= sizeof(message) < 102)
		{
			answer = message.substring(3, sizeof(message) - 5);
			return answer;
		}
		if (102 <= sizeof(message) < 1003)
		{
			answer = message.substring(4, sizeof(message) - 6);
			return answer;
		}
		if (1003 <= sizeof(message) < 10004)
		{
			answer = message.substring(5, sizeof(message) - 7);
			return answer;
		}
	}
	else
	{
		return responce;
	}
}

String WiFi::CheckStatus()
{
	String response = "";
	if (ready)
	{
		response += "Ready";
		if (opened)
		{
			response += ", Opened, " + String(IDCount+1) + " Connected";
		}
		else
		{
			response += ", Closed";
		}
		return response;
	}
	else
	{
		response += "Fatal Error";
		return response;
	}
}

String WiFi::Write(int ID, String message)
{
	if (-1 < ID <= IDCount)
	{
		Send("AT+CIPSEND=" + String(ID) + sizeof(message));
		if (CheckOnAnswer())
		{
			Send(message);
			if (Scan() == ("busy s.../r/nRecv " + sizeof(message) + String(" bytes/r/nSEND OK")))
			{
				return "Done";
			}
			else
			{
				FatalError();
			}
		}
		else
		{
			FatalError();
		}
	}
	else
	{
		return "Wrong ID";
	}
}