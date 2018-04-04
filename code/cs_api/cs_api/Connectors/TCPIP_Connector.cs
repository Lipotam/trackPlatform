using System;

public class TCPIP_Connector : TrackPlatform_BasicConnector
{
	private string ip;
	private uint16_t port = new uint16_t();

	private string receivedBuffer;

	private const uint16_t onePacketMaxSize = 512;
	private const int32_t microsecondsToWaitAnswer = 400 * 1000;


	private addrinfo addressInfo = null;
	private int connectedSocket = DefineConstants.INVALID_SOCKET;

	private bool isSocketConnected = false;

	private void configureSocket()
	{
		addrinfo hints = new addrinfo();

		// Configure socket
//C++ TO C# CONVERTER TODO TASK: The memory management function 'memset' has no equivalent in C#:
		memset(hints, 0, sizeof(addrinfo));
		hints.ai_family = AF_UNSPEC; // AF_UNSPEC for IPv6 or IPv4 (automatically); AF_INET6 for IPv6; AF_INET for IPv4
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
		int iResult = getaddrinfo(ip, Convert.ToString(port).c_str(), hints, addressInfo);
		if (iResult != 0)
		{
			addressInfo = null;
			throw BadAddressOrPortException(iResult);
		}
	}
	private void closeSocket()
	{
		if (connectedSocket != DefineConstants.INVALID_SOCKET)
		{
			(...) close(__VA_ARGS__)(connectedSocket);
			connectedSocket = DefineConstants.INVALID_SOCKET;
		}
	}

	protected override string generatePackage(string command)
	{
		return ((sbyte)command.Length + command);
	}

	//#include "checksum.h"

	protected override void write(string s)
	{
		// Send an initial buffer (returns byte sended)
#if _WIN32
		int iResult = send(connectedSocket, s, (int)s.Length, 0);
#else
		int iResult = send(connectedSocket, s, s.Length, 0);
#endif
		if (iResult == DefineConstants.SOCKET_ERROR)
		{
			throw SocketSendException(errno);
		}
	}
	protected override string read()
	{
		string recvbuf = new string(new char[onePacketMaxSize]);

		int iResult;

		do
		{
			// Check if something is already in buffer (and wait `microsecondsToWaitAnswer` if required)
			timeval tval = new timeval(0, microsecondsToWaitAnswer);

#if _WIN32
			fd_set readSockets = new fd_set(1, {connectedSocket});
			iResult = select(0, readSockets, null, null, tval);
#else
			fd_set readSockets = new fd_set();
			FD_ZERO(readSockets);
			FD_SET(connectedSocket, readSockets);
			iResult = select(connectedSocket + 1, readSockets, null, null, tval);
#endif
			if (iResult == DefineConstants.SOCKET_ERROR)
			{
				throw SocketException(errno);
			}
			if (iResult == 0)
			{
				break;
			}

			// Receive data until the server closes the connection
			iResult = recv(connectedSocket, recvbuf, sizeof(sbyte), 0);
			if (iResult < 0)
			{
				throw SocketReceiveException(errno);
			}

			receivedBuffer += (string)(recvbuf, iResult);
		} while (iResult > 0);

		uint8_t len = receivedBuffer[0];
		if ((len + sizeof(char)) > receivedBuffer.Length)
		{
			throw TimeoutException();
		}

		uint16_t substring_len = sizeof(uint8_t) + len;
		string answer = receivedBuffer.Substring(0, substring_len);
		receivedBuffer = receivedBuffer.Remove(0, substring_len);

		//emulating receiving crc16
//C++ TO C# CONVERTER TODO TASK: There is no equivalent to 'reinterpret_cast' in C#:
		uint16_t crc = crc_modbus(reinterpret_cast<const byte>(answer), answer.Length);
		for (size_t i = 0; i < crc_length; ++i)
		{
//C++ TO C# CONVERTER TODO TASK: There is no equivalent to 'reinterpret_cast' in C#:
			answer.push_back((reinterpret_cast<sbyte>(crc))[i]);
		}
		return answer;
	}

	protected bool connectSocket()
	{
		if (isSocketConnected)
		{
			return false;
		}

		// Attempt to connect to the first address returned by
		// the call to getaddrinfo
		addrinfo ptr = addressInfo;

		// Create a SOCKET for connecting to server
		connectedSocket = socket(ptr.ai_family, ptr.ai_socktype, ptr.ai_protocol);

		if (connectedSocket == DefineConstants.INVALID_SOCKET)
		{
			throw SocketException(errno);
		}

		// Connect to server.
#if _WIN32
		int iResult = global::connect(connectedSocket, addressInfo.ai_addr, (int)addressInfo.ai_addrlen);
#else
		int iResult = global::connect(connectedSocket, addressInfo.ai_addr, addressInfo.ai_addrlen);
#endif
		if (iResult == DefineConstants.SOCKET_ERROR)
		{
			closeSocket();
			return false;
		}

		isSocketConnected = true;
		return true;
	}
	protected bool disconnectSocket()
	{
		if (!isSocketConnected)
		{
			return false;
		}

		// shutdown the sending and recieving data by socket
		int iResult = shutdown(connectedSocket, SHUT_RDWR);
		if (iResult == DefineConstants.SOCKET_ERROR)
		{
			throw SocketShutdownException(errno);
		}

		closeSocket();
		isSocketConnected = false;
		return true;
	}

	/**
	 * @brief Create TCP/IP connector to trackPlatform
	 * @warning Only one object of that class in one moment of time is supported
	 *
	 * @param ip IP of trackPlatform Wi-Fi module
	 * @warning Supports only single IP, no masks
	 * @param port Port of TCP/IP server on trackPlatform
	 */
	public TCPIP_Connector(string ip, uint16_t port)
	{
		this.ip = ip;
//C++ TO C# CONVERTER TODO TASK: The following line was determined to be a copy assignment (rather than a reference assignment) - this should be verified and a 'CopyFrom' method should be created:
//ORIGINAL LINE: this.port = port;
		this.port.CopyFrom(port);
#if _WIN32
		// Initialize Winsock
		int iResult = WSAStartup(MAKEWORD(2, 2), wsaData);
		if (iResult != 0)
		{
			throw WSAStartupException(iResult);
		}
#endif

		configureSocket();
		this.connect();
	}
	public override void Dispose()
	{
		this.disconnect();
		if (addressInfo != null)
		{
			freeaddrinfo(addressInfo);
		}
#if _WIN32
		WSACleanup();
#endif
		base.Dispose();
	}

	public override bool isConnected()
	{
		return (base.isConnected() && isSocketConnected);
	}
	public override void connect()
	{
		if (connectSocket())
		{
			sendStartCommand();
		}
		else
		{
			throw NoConnectionException();
		}
	}
	public override void disconnect()
	{
		//if api is connected to arduino
		if (isConnected())
		{
			sendStopCommand();
		}

		disconnectSocket();
	}
}