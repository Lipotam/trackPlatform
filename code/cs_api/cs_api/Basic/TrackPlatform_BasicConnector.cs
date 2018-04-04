using System;
using TrackPlatform.Exceptions;
using TrackPlatform.Other;
using TrackPlatform.Tools;

public abstract class TrackPlatform_BasicConnector : System.IDisposable
{
	private bool isConnectedToArduino = false;
	private AutoConnector autoConnector = null;

	protected const uint timesToAutoreconnect = 3;
	protected const uint timeoutToNextConnectInMs = 500;
	protected const uint timeoutToAutoreconnectInMs = 4500;
	protected const string correctAnswer = "OK";
	protected const string errorAnswer = "ERROR";
	protected const uint crc_length = 2;

	protected std::recursive_mutex readWriteAtomicMutex = new std::recursive_mutex();

	protected abstract void write(string s);
	protected abstract string read();
	protected virtual string readOneAnswer()
	{
		if (!isConnected())
		{
			throw NoConnectionException();
		}

		string answer = read();
		uint8_t len = answer[0];
		if (answer.Length != (len + sizeof(uint8_t) + crc_length))
		{
			Logger.Log("Bad message length");
			throw CorruptedAnswerException();
		}

//C++ TO C# CONVERTER TODO TASK: There is no equivalent to 'reinterpret_cast' in C#:
		if (Crc16.Modbus(reinterpret_cast<const uint8_t>(answer), answer.Length) != 0)
		{
			Logger.Log("Bad crc value");
			throw new CorruptedAnswerException();
		}

		answer = answer.Remove(0, sizeof(uint8_t));
		answer = answer.Remove(answer.Length - crc_length, crc_length);

		return answer;
	}

	/**
	 * @brief Send start connection command
	 * @warning Must be called in constructor after configuring and opening connection
	 */
	protected void sendStartCommand()
	{
		string command = string() + (sbyte)ControllerEnum.communicationControllerID + (sbyte)CommunicationCommands.startCommunicationCommand + (sbyte)ApiVersion.APIWithCRC;
		isConnectedToArduino = true;
		sendOneCommand(command);
		autoConnector.start();
	}
	/**
	* @brief Send stop connection command
	* @warning Must be called in destructor before closing and deleting connection
	*/
	protected void sendStopCommand()
	{
		if (!isConnected())
		{
			throw NoConnectionException();
		}
		autoConnector.stop();
		string command = string() + (sbyte)ControllerEnum.communicationControllerID + (sbyte)CommunicationCommands.stopCommunicationCommand;
		sendOneCommand(command);
		isConnectedToArduino = false;
	}
	/**
	* @brief Send renew connection command
	* @warning Must be called periodically
	*/
	protected void sendRenewConnectionCommand()
	{
		if (!isConnected())
		{
			throw NoConnectionException();
		}

		string command = string() + (sbyte)ControllerEnum.communicationControllerID + (sbyte)CommunicationCommands.refreshConnectionCommunicationCommand;
		sendOneCommand(command);
	}


	//#include "checksum.h"


	protected virtual string generatePackage(string command)
	{
		return command;
	}

	protected virtual string sendOneCommand_unsafe(string s, bool isWithAnswer)
	{
		if (!isConnected())
		{
			throw new NoConnectionException();
		}
		string package = generatePackage(s);
		Logger.Log("Send: " + package);
		for (var i = 0; i < timesToAutoreconnect; ++i)
		{
			if (i != 0)
			{
				std::this_thread.sleep_for(std::chrono.milliseconds(timeoutToNextConnectInMs));
			}

			Logger.Log("Trying to send command. Attempt " + Convert.ToString(i + 1));
			write(package);
			try
			{
				string managedAnswer = readOneAnswer();
				if (managedAnswer == errorAnswer)
				{
					Logger.Log("Error was getted (part 1)");
					continue;
				}
				if (managedAnswer != correctAnswer)
				{
					Logger.Log("Command not parsed");
					continue;
				}

				string answer;

				if (isWithAnswer)
				{
					answer = readOneAnswer();
					Logger.Log("Read answer: " + answer);
				}

				managedAnswer = readOneAnswer();
				if (managedAnswer == errorAnswer)
				{
					Logger.Log("Error was getted (part 2)");
					continue;
				}
				if (managedAnswer != correctAnswer)
				{
					Logger.Log("Command not executed");
					continue;
				}

				Logger.Log("Sending successfully");
				return answer;
			}
			catch (CorruptedAnswerException)
			{
				//All is good, module not answered, try again
				Logger.Log("Answer is corrupted");
			}
			catch (TimeoutException)
			{
				//All is good, module not answered, try again
				Logger.Log("Timeout exception");
			}
		}

		isConnectedToArduino = false;
		Logger.Log("Cannot connect to arduino");
		throw CannotConnectToArduinoException();
	}

//C++ TO C# CONVERTER TODO TASK: Only lambda expressions having all locals passed by reference can be converted to C#:
//ORIGINAL LINE: TrackPlatform_BasicConnector() : autoConnector(new AutoConnector([this]()
//C++ TO C# CONVERTER TODO TASK: The implementation of the following method could not be found:
//	TrackPlatform_BasicConnector() : autoConnector(new AutoConnector(() => TangibleLambdaToken1virtual ~TrackPlatform_BasicConnector();

	/**
	 * @brief Send one command and read answer to it, if requires
	 * @warning By default returns one portion of data from rx, must be overriden if require
	 * @return Answer from command
	 */
	public string sendOneCommand(string s, bool isWithAnswer = false)
	{
		readWriteAtomicMutex.@lock();

		try
		{
			string answer = sendOneCommand_unsafe(s, isWithAnswer);
			readWriteAtomicMutex.unlock();
			return answer;
		}
		catch
		{
			readWriteAtomicMutex.unlock();
			throw;
		}
	}
	public virtual bool isConnected()
	{
		return isConnectedToArduino;
	}
	/**
	 * @brief Manual connect if not already connected
	 */
	public abstract void connect();
	/**
	 * @brief Manual disconnect
	 */
	public abstract void disconnect();

    public void Dispose()
    {
        readWriteAtomicMutex.try_lock();
        readWriteAtomicMutex.unlock();
    }
}
