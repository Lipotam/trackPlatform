using System;
using System.Linq;
using System.Text;
using System.Threading;
using TrackPlatform.Exceptions;
using TrackPlatform.Other;
using TrackPlatform.Tools;

public abstract class TrackPlatform_BasicConnector : IDisposable
{
	private bool isConnectedToArduino = false;
	private Timer autoConnector = null;

	protected const uint timesToAutoreconnect = 3;
	protected const int timeoutToNextConnectInMs = 500;
	protected const uint timeoutToAutoreconnectInMs = 4500;
	protected readonly byte[] correctAnswer = Encoding.ASCII.GetBytes("OK");
	protected readonly byte[] errorAnswer = Encoding.ASCII.GetBytes("ERROR");
	protected const uint crc_length = sizeof(ushort);
	protected const uint len_length = sizeof(byte);

    protected Mutex readWriteAtomicMutex = new Mutex();

    protected abstract void write(byte[] s);
	protected abstract byte[] read();
	protected virtual byte[] readOneAnswer()
	{
		if (!isConnected())
		{
			throw new NoConnectionException();
		}

	    byte[] answer = read();
		byte len = answer[0];
		if (answer.Length != (len + len_length + crc_length))
		{
			Logger.Log("Bad message length");
			throw new CorruptedAnswerException();
		}

		if (Crc16.Modbus(answer) != 0)
		{
			Logger.Log("Bad crc value");
			throw new CorruptedAnswerException();
		}

		answer = answer.SubArray(0, (int)len_length);
		answer = answer.SubArray((int)(answer.Length - crc_length), (int)crc_length);

		return answer;
	}

	/**
	 * @brief Send start connection command
	 * @warning Must be called in constructor after configuring and opening connection
	 */
	protected void sendStartCommand()
	{
		byte[] command =
		{
		    (byte)ControllerEnum.communicationControllerID,
		    (byte)CommunicationCommands.startCommunicationCommand,
		    (byte)ApiVersion.APIWithCRC,
		};
		isConnectedToArduino = true;
		sendOneCommand(command);
		autoConnector.Change(timeoutToAutoreconnectInMs, timeoutToAutoreconnectInMs);
	}
	/**
	* @brief Send stop connection command
	* @warning Must be called in destructor before closing and deleting connection
	*/
	protected void sendStopCommand()
	{
		if (!isConnected())
		{
			throw new NoConnectionException();
		}
		autoConnector.Change(Timeout.Infinite, Timeout.Infinite);
	    byte[] command =
	    {
	        (byte)ControllerEnum.communicationControllerID,
	        (byte)CommunicationCommands.stopCommunicationCommand,
	    };
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
			throw new NoConnectionException();
		}

	    byte[] command =
	    {
	        (byte)ControllerEnum.communicationControllerID,
	        (byte)CommunicationCommands.refreshConnectionCommunicationCommand,
	    };
		sendOneCommand(command);
	}


	protected virtual byte[] generatePackage(byte[] command)
	{
	    byte[] package = command.Add((byte) command.Length, 0);
	    ushort crc = Crc16.Modbus(package);
	    return package.Concat(BitConverter.GetBytes(crc));
	}

	protected virtual byte[] sendOneCommand_unsafe(byte[] s, bool isWithAnswer)
	{
		if (!isConnected())
		{
			throw new NoConnectionException();
		}
		byte[] package = generatePackage(s);
		Logger.Log("Send: " + package);
		for (var i = 0; i < timesToAutoreconnect; ++i)
		{
			if (i != 0)
			{
                Thread.Sleep(timeoutToNextConnectInMs);
			}

			Logger.Log("Trying to send command. Attempt " + Convert.ToString(i + 1));
			write(package);
			try
			{
				byte[] managedAnswer = readOneAnswer();
				if (managedAnswer.SequenceEqual(errorAnswer))
				{
					Logger.Log("Error was getted (part 1)");
					continue;
				}
				if (!managedAnswer.SequenceEqual(correctAnswer))
				{
					Logger.Log("Command not parsed");
					continue;
				}

				byte[] answer = new byte[0];

				if (isWithAnswer)
				{
					answer = readOneAnswer();
					Logger.Log("Read answer: " + answer);
				}

				managedAnswer = readOneAnswer();
				if (managedAnswer.SequenceEqual(errorAnswer))
				{
					Logger.Log("Error was getted (part 2)");
					continue;
				}
				if (!managedAnswer.SequenceEqual(correctAnswer))
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
		throw new CannotConnectToArduinoException();
	}

    public TrackPlatform_BasicConnector()
    {
        autoConnector = new Timer(state => sendRenewConnectionCommand(), null, Timeout.Infinite, Timeout.Infinite);
    }

	/**
	 * @brief Send one command and read answer to it, if requires
	 * @warning By default returns one portion of data from rx, must be overriden if require
	 * @return Answer from command
	 */
	public byte[] sendOneCommand(byte[] s, bool isWithAnswer = false)
	{
		readWriteAtomicMutex.WaitOne();

		try
		{
			byte[] answer = sendOneCommand_unsafe(s, isWithAnswer);
			readWriteAtomicMutex.ReleaseMutex();
			return answer;
		}
		catch
		{
			readWriteAtomicMutex.ReleaseMutex();
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

    public virtual void Dispose()
    {
        readWriteAtomicMutex.Close();
    }
}
