using System;

//C++ TO C# CONVERTER WARNING: The following #include directive was ignored:
//#include "serial/serial.h"

public class SerialConnector : TrackPlatform_BasicConnector
{
	private const size_t messageMaxSize = 65535;
	private const size_t timeoutInMs = 1500;

	private string rxLocation;
	private string txLocation;
	private uint32_t baudRate = new uint32_t();

	private serial.Serial readPort;
	private serial.Serial writePort;

	private string buffer;


	//#include "trackPlatformAllExceptions.h"

	//#include "checksum.h"

	protected override void write(string s)
	{
		writePort.write(s);
		writePort.flush();
	}
	protected override string read()
	{
		if (string.IsNullOrEmpty(buffer))
		{
			buffer += readPort.read(sizeof(uint8_t));
		}
		if (string.IsNullOrEmpty(buffer))
		{
			throw TimeoutException();
		}
		uint8_t len = buffer[0];
		uint16_t substring_len = sizeof(uint8_t) + len + crc_length;
		if ((substring_len) > buffer.Length)
		{
			buffer += readPort.read(Math.Max(substring_len - sizeof(uint8_t), readPort.available()));
		}

		if ((substring_len) > buffer.Length)
		{
			throw TimeoutException();
		}

		string answer = buffer.Substring(0, substring_len);
		buffer = buffer.Remove(0, substring_len);

		return answer;
	}
	protected override string generatePackage(string command)
	{
		string package = (sbyte)command.Length + command;
//C++ TO C# CONVERTER TODO TASK: There is no equivalent to 'reinterpret_cast' in C#:
		uint16_t crc = crc_modbus(reinterpret_cast<const byte>(package), package.Length);
		for (size_t i = 0; i < crc_length; ++i)
		{
//C++ TO C# CONVERTER TODO TASK: There is no equivalent to 'reinterpret_cast' in C#:
			package.push_back((reinterpret_cast<sbyte>(crc))[i]);
		}
		return package;
	}

	public SerialConnector(string rx, string tx, uint32_t baudRate)
	{
		this.rxLocation = rx;
		this.txLocation = tx;
//C++ TO C# CONVERTER TODO TASK: The following line was determined to be a copy assignment (rather than a reference assignment) - this should be verified and a 'CopyFrom' method should be created:
//ORIGINAL LINE: this.baudRate = baudRate;
		this.baudRate.CopyFrom(baudRate);
		this.readPort = new serial.Serial(rx, baudRate, serial.Timeout.simpleTimeout(timeoutInMs));
		this.writePort = (rx == tx) ? readPort : new serial.Serial(tx, baudRate, serial.Timeout.simpleTimeout(timeoutInMs));
		sendStartCommand();
	}
	public new void Dispose()
	{
		sendStopCommand();

		this.disconnect();
		if (readPort != writePort)
		{
			if (writePort != null)
			{
				writePort.Dispose();
			}
		}
		if (readPort != null)
		{
			readPort.Dispose();
		}
		base.Dispose();
	}
	public override bool isConnected()
	{
		return (base.isConnected() && readPort.isOpen() && writePort.isOpen());
	}
	public override void connect()
	{
		if (readPort != null && !readPort.isOpen())
		{
			readPort.open();
		}
		if (writePort != null && !writePort.isOpen())
		{
			writePort.open();
		}
	}
	public override void disconnect()
	{
		if (readPort != null && readPort.isOpen())
		{
			readPort.close();
		}
		if (writePort != null && writePort.isOpen())
		{
			writePort.close();
		}
	}
}
