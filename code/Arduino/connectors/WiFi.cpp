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
	if (ready != ((Scan() == "AT\r\nOK") == ReturningCommandsOff()))
	{
		return true;
	}
	else
	{
		Reset();
		return false;
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
		Reset();
		return false;
	}
}

bool WiFi::CheckOnAnswer()
{
	if (Scan() = "\r\nOK")
	{
		return true;
	}
	else
	{
		Reset();
		return false;
	}
}

bool WiFi::Reset()
{
	IDCount = -1;
	ready = false;
	opened = false;
	StartingSend("AT+RST");
	if (ready != ((Scan() == "AT+RST\r\nOK") == ReturningCommandsOff()))
	{
		return ready = true;
	}
	else
	{
		Reset();
		return false;
	}
}

bool WiFi::Reset(unsigned long speed)
{
	if (Reset())
	{
		if (ChangeSpeed(speed))
		{
			return true;
		}
		else
		{
			Reset();
			return false;
		}
	}
	else
	{
		Reset();
		return false;
	}
}

bool WiFi::ChangeSpeed(unsigned long speed)
{
	Send("AT+CIOBAUD=" + String(speed));
	if (CheckOnAnswer())
	{
		return true;
	}
	else
	{
		Reset();
		return false;
	}
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
		Reset();
		return "";
	}
}

String WiFi::CheckIPandMAC()
{
	Send("AT+CIFSR");
	if (CheckOnAnswer())
	{
		return ReturnInfo();
	}
	else
	{
		Reset();
		return "";
	}
}

bool WiFi::CreateCurrentHost(String name, String password, int port)
{
	if (Open())
	{
		if (CheckOnAnswer())
		{
			Send("AT+CWSAP_CUR=" + name + "," + password + ",5,3");
			if (CheckOnAnswer())
			{
				if (UseTCP(port))
				{
					return true;
				}
				else
				{
					Reset();
					return false;
				}
			}
			else
			{
				Reset();
				return false;
			}
		}
		else
		{
			Reset();
			return false;
		}
	}
	else
	{
		Reset();
		return false;
	}
}

bool WiFi::Open()
{
	Send("AT+CWMODE_CUR=2");
	if (CheckOnAnswer())
	{
		opened = true;
		return true;
	}
	else
	{
		Reset();
		return false;
	}
}

String WiFi::NetsList()
{
	if (Close())
	{
		Send("AT+CWLAP");
		return ReturnInfo();
	}
	else
	{
		Reset();
		return "";
	}
}

bool WiFi::Close()
{
	Send("AT+CWMODE_CUR=1");
	if (CheckOnAnswer())
	{
		opened = false;
		return true;
	}
	else
	{
		Reset();
		return false;
	}
}

bool WiFi::UseTCP(int port)
{
	Send("AT+CIPMUX=1");
	if (CheckOnAnswer())
	{
		Send("AT+CIPSERVER=1," + String(port));
		if (CheckOnAnswer())
		{
			return true;
		}
		else
		{
			Reset();
			return false;
		}
	}
	else
	{
		Reset();
		return false;
	}
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
		Reset();
	}
}

void WiFi::send(String message)
{
	Write(0, message);
}

String WiFi::read()
{
	return Scan();
}

String WiFi::Read()
{
	return device->readStringUntil('\r');
}

String WiFi::Scan()
{
	delay(100);
	String responce = Read();
	if (responce.indexOf(",CONNECT") == 1)
	{
		String ID = responce.substring(0, 1);
		if ((atoi(ID.c_str()) - 1) == IDCount)
		{
			IDCount++;
			return Scan();
		}
		else
		{
			Reset();
			return "";
		}
	}
	if (responce.indexOf("/r/n+IPD,") == 0)
	{
		String ID = responce.substring(7, 1);
		String message = responce.substring(9, sizeof(responce) - 9);
		String answer;
		if (sizeof(message) < 11)
		{
			answer = message.substring(2, sizeof(message) - 2);
			return answer;
		}
		if (sizeof(message) < 102)
		{
			answer = message.substring(3, sizeof(message) - 3);
			return answer;
		}
		if (sizeof(message) < 1003)
		{
			answer = message.substring(4, sizeof(message) - 4);
			return answer;
		}
		if (sizeof(message) < 10004)
		{
			answer = message.substring(5, sizeof(message) - 5);
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

bool WiFi::Write(int ID, String message)
{
	if (ID > -1 && ID <= IDCount)
	{
		Send("AT+CIPSEND=" + String(ID) + sizeof(message));
		if (CheckOnAnswer())
		{
			Send(message);
			if (Scan() == ("busy s.../r/nRecv " + sizeof(message) + String(" bytes/r/nSEND OK")))
			{
				return true;
			}
			else
			{
				Reset();
				return false;
			}
		}
		else
		{
			Reset();
			return false;
		}
	}
	else
	{
		Reset();
		return false;
	}
}