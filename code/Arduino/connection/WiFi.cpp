#include "WiFi.h"
#include "DebugSerial.h"

WiFi::WiFi(unsigned long speed) : IConnector(&Serial2)
{
	if (isInited)
	{
		return;
	}
	isInited = true;
	Serial2.begin(speed);
	DebugSerial::getSerial()->println(__LINE__);
	if (CheckOnReady())
	{
		DebugSerial::getSerial()->println(__LINE__);
		ChangeSpeed(speed);
	}
	DebugSerial::getSerial()->println(__LINE__);

	CreateCurrentHost("qwertuiop", "qwertuiop", 1001);
}

WiFi::~WiFi()
{
}

bool WiFi::CheckOnReady()
{
	DebugSerial::getSerial()->println(__LINE__);
	StartingSend("AT");
	DebugSerial::getSerial()->println(__LINE__);
	if (ready != ((Scan() == "AT")))
	{
		DebugSerial::getSerial()->println(__LINE__);
		if (ready != ((Scan() == "\r\nOK") == ReturningCommandsOff()))
		{
			DebugSerial::getSerial()->println(__LINE__);
			return true;
		}
		else
		{
			DebugSerial::getSerial()->println(__LINE__);
			Reset();
			return false;
		}
	}
	else
	{
		DebugSerial::getSerial()->println(__LINE__);
		Reset();
		return false;
	}
}

bool WiFi::ReturningCommandsOff()
{
	StartingSend("ATE0");
	DebugSerial::getSerial()->println(__LINE__);
	if (Scan() == "ATE0")
	{
		DebugSerial::getSerial()->println(__LINE__);
		if (Scan() == "\r\nOK")
		{
			DebugSerial::getSerial()->println(__LINE__);
			return true;
		}
		else
		{
			DebugSerial::getSerial()->println(__LINE__);
			Reset();
			return false;
		}
	}
	else
	{
		DebugSerial::getSerial()->println(__LINE__);
		Reset();
		return false;
	}
}

bool WiFi::CheckOnAnswer()
{
	if (Scan() == "\r\nOK")
	{
		DebugSerial::getSerial()->println(__LINE__);
		return true;
	}
	else
	{
		DebugSerial::getSerial()->println(__LINE__);
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
	DebugSerial::getSerial()->println(__LINE__);
	StartingSend("AT+RST");
	DebugSerial::getSerial()->println(__LINE__);
	if (ready != ((Scan() == "AT+RST")))
	{
		DebugSerial::getSerial()->println(__LINE__);
		if (ready != ((Scan() == "\r\nOK") == ReturningCommandsOff()))
		{
			DebugSerial::getSerial()->println(__LINE__);
			return ready = true;
		}
		else
		{
			DebugSerial::getSerial()->println(__LINE__);
			Reset();
			return false;
		}
	}
	else
	{
		DebugSerial::getSerial()->println(__LINE__);
		Reset();
		return false;
	}
}

bool WiFi::Reset(unsigned long speed)
{
	if (Reset())
	{
		DebugSerial::getSerial()->println(__LINE__);
		if (ChangeSpeed(speed))
		{
			DebugSerial::getSerial()->println(__LINE__);
			return true;
		}
		else
		{
			DebugSerial::getSerial()->println(__LINE__);
			Reset();
			return false;
		}
	}
	else
	{
		DebugSerial::getSerial()->println(__LINE__);
		Reset();
		return false;
	}
}

bool WiFi::ChangeSpeed(unsigned long speed)
{
	DebugSerial::getSerial()->println(__LINE__);
	Send("AT+CIOBAUD=" + String(speed));
	if (CheckOnAnswer())
	{
		DebugSerial::getSerial()->println(__LINE__);
		return true;
	}
	else
	{
		DebugSerial::getSerial()->println(__LINE__);
		Reset();
		return false;
	}
}

String WiFi::VersionCheck()
{
	DebugSerial::getSerial()->println(__LINE__);
	Send("AT+GMR");
	return ReturnInfo();
}

String WiFi::ReturnInfo()
{
	String str = Scan();
	if (int a = str.indexOf("\r\nOK"))
	{
		DebugSerial::getSerial()->println(__LINE__);
		return str.substring(0, a);
	}
	else
	{
		DebugSerial::getSerial()->println(__LINE__);
		Reset();
		return "";
	}
}

String WiFi::CheckIPandMAC()
{
	DebugSerial::getSerial()->println(__LINE__);
	Send("AT+CIFSR");
	return ReturnInfo();
}

bool WiFi::CreateCurrentHost(String name, String password, int port)
{
	if (Open())
	{
		DebugSerial::getSerial()->println(__LINE__);
		if (CheckOnAnswer())
		{
			DebugSerial::getSerial()->println(__LINE__);
			Send("AT+CWSAP_CUR=" + name + "," + password + ",5,3");
			DebugSerial::getSerial()->println(__LINE__);
			if (CheckOnAnswer())
			{
				if (UseTCP(port))
				{
					DebugSerial::getSerial()->println(__LINE__);
					return true;
				}
				else
				{
					DebugSerial::getSerial()->println(__LINE__);
					Reset();
					return false;
				}
			}
			else
			{
				DebugSerial::getSerial()->println(__LINE__);
				Reset();
				return false;
			}
		}
		else
		{
			DebugSerial::getSerial()->println(__LINE__);
			Reset();
			return false;
		}
	}
	else
	{
		DebugSerial::getSerial()->println(__LINE__);
		Reset();
		return false;
	}
}

bool WiFi::Open()
{
	DebugSerial::getSerial()->println(__LINE__);
	Send("AT+CWMODE_CUR=2");
	DebugSerial::getSerial()->println(__LINE__);
	if (CheckOnAnswer())
	{
		DebugSerial::getSerial()->println(__LINE__);
		opened = true;
		DebugSerial::getSerial()->println(__LINE__);
		return true;
	}
	else
	{
		DebugSerial::getSerial()->println(__LINE__);
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
	DebugSerial::getSerial()->println(__LINE__);
	Send("AT+CIPMUX=1");
	DebugSerial::getSerial()->println(__LINE__);
	if (CheckOnAnswer())
	{
		DebugSerial::getSerial()->println(__LINE__);
		Send("AT+CIPSERVER=1," + String(port));
		if (CheckOnAnswer())
		{
			DebugSerial::getSerial()->println(__LINE__);
			return true;
		}
		else
		{
			DebugSerial::getSerial()->println(__LINE__);
			Reset();
			return false;
		}
	}
	else
	{
		DebugSerial::getSerial()->println(__LINE__);
		Reset();
		return false;
	}
}

void WiFi::StartingSend(String command)
{
	IConnector::write_answer(command + "\r\n");
}

void WiFi::Send(String command)
{
	if (ready)
	{
		IConnector::write_answer(command + "\r\n");
	}
	else
	{
		Reset();
	}
}

void WiFi::write_answer(String message)
{
	Write(0, message);
}

String WiFi::read_message()
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
		DebugSerial::getSerial()->println(__LINE__);
		Send("AT+CIPSEND=" + String(ID) + sizeof(message));
		DebugSerial::getSerial()->println(__LINE__);
		if (CheckOnAnswer())
		{
			DebugSerial::getSerial()->println(__LINE__);
			Send(message);
			DebugSerial::getSerial()->println(__LINE__);
			if (Scan() == ("busy s..."))
			{
				DebugSerial::getSerial()->println(__LINE__);
				if (Scan() == ("/r/nRecv " + sizeof(message) + String(" bytes/r/nSEND OK")))
				{
					DebugSerial::getSerial()->println(__LINE__);
					if (Scan() == ("/r/nSEND OK"))
					{
						DebugSerial::getSerial()->println(__LINE__);
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