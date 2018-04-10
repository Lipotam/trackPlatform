using System;
using System.Collections.Generic;
using System.IO.Ports;
using TrackPlatform.Tools;

public class SerialConnector : TrackPlatform_BasicConnector
{
	private const int messageMaxSize = 65535;
	private const int timeoutInMs = 1500;

	private string rxLocation;
	private string txLocation;
	private int baudRate;

	private readonly SerialPort readPort;
	private readonly SerialPort writePort;

	private List<byte> buffer = new List<byte>();
	private readonly byte[] _readBuffer = new byte[messageMaxSize];

	protected override void write(byte[] s)
	{
		writePort.Write(s, 0, s.Length);
	}

	protected override byte[] read()
	{
		if (buffer.Count == 0)
		{
		    int readByte = readPort.ReadByte();
		    if (readByte < 0)
		    {
                throw new TimeoutException();
		    }
			buffer.Add((byte) readByte);
		}

		byte len = buffer[0];
		int substringLen = (int) (sizeof(byte) + len + crc_length);
		if ((substringLen) > buffer.Count)
		{
		    int bytesNeedToRead = (int) Math.Max(substringLen - sizeof(byte), readPort.BytesToRead);

		    int bytesWereRead = readPort.Read(_readBuffer, 0, bytesNeedToRead);

		    if (bytesNeedToRead > bytesWereRead)
		    {
		        throw new TimeoutException();
		    }
		}

		byte[] answer = buffer.GetRange(0, substringLen).ToArray();
		buffer.RemoveRange(0, substringLen);

		return answer;
	}

	public SerialConnector(string rx, string tx, int baudRate)
	{
		this.rxLocation = rx;
		this.txLocation = tx;
		this.baudRate = baudRate;
		this.readPort = new SerialPort(rx, baudRate);
	    readPort.ReadTimeout = timeoutInMs;
		this.writePort = (rx == tx) ? readPort : new SerialPort(tx, baudRate);
	    writePort.WriteTimeout = timeoutInMs;

        //board reloading when connect block
	    writePort.DtrEnable = false;

		sendStartCommand();
	}
	public new void Dispose()
	{
		sendStopCommand();

		this.disconnect();
		if (readPort != writePort)
		{
		    writePort?.Dispose();
		}

	    readPort?.Dispose();
	    base.Dispose();
	}
	public override bool isConnected()
	{
		return (base.isConnected() && readPort.IsOpen && writePort.IsOpen);
	}
	public override void connect()
	{
		if (readPort != null && !readPort.IsOpen)
		{
			readPort.Open();
		}
		if (writePort != null && !writePort.IsOpen)
		{
			writePort.Open();
		}
	}
	public override void disconnect()
	{
		if (readPort != null && readPort.IsOpen)
		{
			readPort.Close();
		}
		if (writePort != null && writePort.IsOpen)
		{
			writePort.Close();
		}
	}
}
