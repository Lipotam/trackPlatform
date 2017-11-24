#include <chrono>
#include <thread>

#include "Logger.h"
#include "trackPlatformAllExceptions.h"
#include "CommandsEnum.h"

#include "TrackPlatform_BasicConnector.h"

extern "C" {
#include "checksum.h"
}

const std::string TrackPlatform_BasicConnector::correctAnswer = "OK";

std::string TrackPlatform_BasicConnector::generatePackage(const std::string& command)
{
	std::string package = static_cast<char>(command.length()) + command;
	uint16_t crc = crc_modbus(reinterpret_cast<const unsigned char*>(package.c_str()), package.length());
	for (size_t i = 0; i < crc_length; ++i)
	{
		package.push_back((reinterpret_cast<char *>(&crc))[i]);
	}
	return package;
}

void TrackPlatform_BasicConnector::sendStartCommand()
{
	const std::string command = std::string() + static_cast<char>(communicationControllerID) + static_cast<char>(startCommunicationCommand) + static_cast<char>(APIWithCRC);
	isConnectedToArduino = true;
	sendOneCommand(command);
	autoConnector->start();
}
void TrackPlatform_BasicConnector::sendStopCommand()
{
	if (!isConnected())
	{
		throw NoConnectionException();
	}
	autoConnector->stop();
	const std::string command = std::string() + static_cast<char>(communicationControllerID) + static_cast<char>(stopCommunicationCommand);
	sendOneCommand(command);
	isConnectedToArduino = false;
}

void TrackPlatform_BasicConnector::sendRenewConnectionCommand()
{
	if (!isConnected())
	{
		throw NoConnectionException();
	}

	const std::string command = std::string() + static_cast<char>(communicationControllerID) + static_cast<char>(refreshConnectionCommunicationCommand);
	sendOneCommand(command);
}

TrackPlatform_BasicConnector::TrackPlatform_BasicConnector() :
	autoConnector(new AutoConnector([this]()
{
	this->sendRenewConnectionCommand();
}, timeoutToAutoreconnectInMs))
{
}

TrackPlatform_BasicConnector::~TrackPlatform_BasicConnector()
{
}

std::string TrackPlatform_BasicConnector::readOneAnswer()
{
	if (!isConnected())
	{
		throw NoConnectionException();
	}

	std::string answer = read();
	uint8_t len = answer[0];
	if (answer.length() != (len + sizeof(len) + crc_length))
	{
		Logger::log("Bad message length");
		throw CorruptedAnswerException();
	}

	if (crc_modbus(reinterpret_cast<const uint8_t*>(answer.c_str()), answer.length()) != 0)
	{
		Logger::log("Bad crc value");
		throw CorruptedAnswerException();
	}

	answer.erase(0, sizeof(len));
	answer.erase(answer.length() - crc_length, crc_length);

	return answer;
}

std::string TrackPlatform_BasicConnector::sendOneCommand(const std::string& s, const bool isWithAnswer)
{
	if (!isConnected())
	{
		throw NoConnectionException();
	}
	const std::string package = generatePackage(s);
	Logger::log("Send: " + package);
	for (auto i = 0; i < timesToAutoreconnect; ++i)
	{
		if (i != 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(timeoutToNextConnectInMs));
		}

		Logger::log("Trying to send command. Attempt " + std::to_string(i + 1));
		write(package);
		try {
			if (readOneAnswer() != correctAnswer)
			{
				Logger::log("Command not parsed");
				continue;
			}

			std::string answer;

			if (isWithAnswer)
			{
				answer = readOneAnswer();
				Logger::log("Read answer: " + answer);
			}

			if (readOneAnswer() != correctAnswer)
			{
				Logger::log("Command not executed");
				continue;
			}

			Logger::log("Sending successfully");
			return answer;
		}
		catch (CorruptedAnswerException&)
		{
			//All is good, module not answered, try again
			Logger::log("Answer is corrupted");
		}
	}

	isConnectedToArduino = false;
	Logger::log("Cannot connect to arduino");
	throw CannotConnectToArduinoException();
}

bool TrackPlatform_BasicConnector::isConnected()
{
	return isConnectedToArduino;
}
