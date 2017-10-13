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

	CreateCurrentHost("qwertuiop", "qwertuiop", 1001);
}

WiFi::~WiFi()
{
}

bool WiFi::CheckOnReady()
{
	StartingSend("AT");
	if (ready != ((Scan() == "AT")))
	{
		if (ready != ((Scan() == "\r\nOK") == ReturningCommandsOff()))
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

bool WiFi::ReturningCommandsOff()
{
	StartingSend("ATE0");
	if (Scan() == "ATE0")
	{
		if (Scan() == "\r\nOK")
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

bool WiFi::CheckOnAnswer()
{
	if (Scan() == "\r\nOK")
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
	IDList = "";
	ready = false;
	opened = false;
	StartingSend("AT+RST");
	if (ready != ((Scan() == "AT+RST")))
	{
		if (ready != ((Scan() == "\r\nOK") == ReturningCommandsOff()))
		{
			return ready = true;
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
	return ReturnInfo();
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
	if (messagecount >= 0)
	{
		String answer = MessageBox.pop();
		messagecount--;
		return answer;
	}
	else
	{
		return "";
	}
}

String WiFi::Read()
{
	return device->readStringUntil('\r');
}

String WiFi::Scan()
{
	delay(100);
	String responce = Read();
	if (int x = (responce.indexOf(",CONNECT") >= 1) && responce.indexOf(",CONNECT") <= 3)
	{
		String ID = responce.substring(0, x);
		if (-1 == (IDList.indexOf("." + ID + ".")))
		{
			IDList += "." + ID + ".";
			IDCount++;
			return Scan();
		}
		else
		{
			Reset();
			return "";
		}
	}
	if (int y = (responce.indexOf(",CLOSED") >= 1) && responce.indexOf(",CLOSED") <= 3)
	{
		String ID = responce.substring(0, y);
		if (0 <= (IDList.indexOf("." + ID + ".")))
		{
			IDList = (IDList.substring(IDList.indexOf("." + ID + "."), (sizeof(ID) + 2)) + (IDList.substring((IDList.indexOf("." + ID + ".") + sizeof(ID) + 2), (sizeof(IDList) - (IDList.indexOf("." + ID + ".") + (sizeof(ID) + 2))))));
			IDCount--;
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
		responce = responce.substring(6, sizeof(responce) - 6);
		int count = 1;
		while (responce[count] != ',')
		{
			count++;
		}
		String ID = responce.substring(0, count - 1);
		responce = responce.substring(count + 1, sizeof(responce) - count - 1);
		count = 1;
		while (responce[count] != ',')
		{
			count++;
		}
		responce = responce.substring(count + 1, sizeof(responce) - count - 1);
		messagecount++;
		MessageBox.push(ID + ": " + responce);
		return Scan();
	}
	else
	{
		return responce;
	}
}

String WiFi::CheckStatus()
{
	String response;
	if (ready)
	{
		response = "Ready";
		if (opened)
		{
			response += ", Opened, " + String(IDCount + 1) + " Connected, " + String(messagecount + 1) + " Incoming Messages";
		}
		else
		{
			response += ", Closed";
		}
		return response;
	}
	else
	{
		response = "Fatal Error";
		return response;
	}
}

bool WiFi::Write(int ID, String message)
{
	if (0 <= (IDList.indexOf("." + String(ID) + ".")))
	{
		Send("AT+CIPSEND=" + String(ID) + sizeof(message));
		if (CheckOnAnswer())
		{
			Send(message);
			if (Scan() == ("busy s..."))
			{
				if (Scan() == ("/r/nRecv " + sizeof(message) + String(" bytes/r/nSEND OK")))
				{
					if (Scan() == ("/r/nSEND OK"))
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
	else
	{
		Reset();
		return false;
	}
}