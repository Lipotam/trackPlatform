using System;

//C++ TO C# CONVERTER WARNING: The following #include directive was ignored:
//#include "trackPlatformAllExceptions.h"



public abstract class TrackPlatform_BasicConnector : System.IDisposable
{
	private bool isConnectedToArduino = false;
	private AutoConnector autoConnector = null;

	protected const uint8_t timesToAutoreconnect = 3;
	protected const uint32_t timeoutToNextConnectInMs = 500;
	protected const uint32_t timeoutToAutoreconnectInMs = 4500;
	protected readonly string correctAnswer = "OK";
	protected readonly string errorAnswer = "ERROR";
	protected const uint8_t crc_length = 2;

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
			Logger.log("Bad message length");
			throw CorruptedAnswerException();
		}

//C++ TO C# CONVERTER TODO TASK: There is no equivalent to 'reinterpret_cast' in C#:
		if (crc_modbus(reinterpret_cast<const uint8_t>(answer), answer.Length) != 0)
		{
			Logger.log("Bad crc value");
			throw CorruptedAnswerException();
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
			throw NoConnectionException();
		}
		string package = generatePackage(s);
		Logger.log("Send: " + package);
		for (var i = 0; i < timesToAutoreconnect; ++i)
		{
			if (i != 0)
			{
				std::this_thread.sleep_for(std::chrono.milliseconds(timeoutToNextConnectInMs));
			}

			Logger.log("Trying to send command. Attempt " + Convert.ToString(i + 1));
			write(package);
			try
			{
				string managedAnswer = readOneAnswer();
				if (managedAnswer == errorAnswer)
				{
					Logger.log("Error was getted (part 1)");
					continue;
				}
				if (managedAnswer != correctAnswer)
				{
					Logger.log("Command not parsed");
					continue;
				}

				string answer;

				if (isWithAnswer)
				{
					answer = readOneAnswer();
					Logger.log("Read answer: " + answer);
				}

				managedAnswer = readOneAnswer();
				if (managedAnswer == errorAnswer)
				{
					Logger.log("Error was getted (part 2)");
					continue;
				}
				if (managedAnswer != correctAnswer)
				{
					Logger.log("Command not executed");
					continue;
				}

				Logger.log("Sending successfully");
				return answer;
			}
			catch (CorruptedAnswerException)
			{
				//All is good, module not answered, try again
				Logger.log("Answer is corrupted");
			}
			catch (TimeoutException)
			{
				//All is good, module not answered, try again
				Logger.log("Timeout exception");
			}
		}

		isConnectedToArduino = false;
		Logger.log("Cannot connect to arduino");
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
}
//C++ TO C# CONVERTER TODO TASK: The following method format was not recognized, possibly due to an unrecognized macro:
, timeoutToAutoreconnectInMs))
{
}

