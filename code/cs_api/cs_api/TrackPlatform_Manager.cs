public class TrackPlatform_Manager : TrackPlatform_BasicManagement
{
	private static TrackPlatform_BasicConnector createConnectorByMode(ConnectionModes mode, CommunicationInfoStruct info)
	{
		TrackPlatform_BasicConnector res;

		//TODO: add more modes
		switch (mode)
		{
		case ConnectionModes.USB:
		case ConnectionModes.bluetooth:
//C++ TO C# CONVERTER TODO TASK: The following line was determined to contain a copy constructor call - this should be verified and a copy constructor should be created:
//ORIGINAL LINE: res = new SerialConnector(info.SerialInfo.rxPort, info.SerialInfo.txPort, info.SerialInfo.baudrate);
			res = new SerialConnector(info.SerialInfo.rxPort, info.SerialInfo.txPort, new uint32_t(info.SerialInfo.baudrate));
			break;
		case ConnectionModes.WiFi:
//C++ TO C# CONVERTER TODO TASK: The following line was determined to contain a copy constructor call - this should be verified and a copy constructor should be created:
//ORIGINAL LINE: res = new TCPIP_Connector(info.TCPIPInfo.ip, info.TCPIPInfo.port);
			res = new TCPIP_Connector(info.TCPIPInfo.ip, new uint16_t(info.TCPIPInfo.port));
			break;
		default:
			res = null;
			break;
		}

		return res;
	}

	public TrackPlatform_Manager(ConnectionModes mode, CommunicationInfoStruct info) : base(createConnectorByMode(mode, info))
	{
	}
	public new void Dispose()
	{
		TrackPlatform_BasicConnector connector = getConnector();
		if (connector != null)
		{
			if (connector != null)
			{
				connector.Dispose();
			}
		}
		base.Dispose();
	}
}


//C++ TO C# CONVERTER NOTE: The following #define macro was replaced in-line:
//ORIGINAL LINE: #define SOCKET int
