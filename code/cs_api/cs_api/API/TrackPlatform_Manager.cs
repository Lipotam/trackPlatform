using System;

public class TrackPlatform_Manager : TrackPlatform_BasicManagement, IDisposable
{
	private static TrackPlatform_BasicConnector createConnectorByMode(ConnectionModes mode, CommunicationInfoStruct info)
	{
		TrackPlatform_BasicConnector res = null;

		//TODO: add more modes
		switch (mode)
		{
		case ConnectionModes.USB:
		case ConnectionModes.bluetooth:
			res = new SerialConnector(info.SerialInfo.rxPort, info.SerialInfo.txPort, info.SerialInfo.baudrate);
			break;
		case ConnectionModes.WiFi:
            //TODO: uncomment line
		    //res = new TCPIP_Connector(info.TcpInfo.ip, info.TcpInfo.port);
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
	public void Dispose()
	{
	    connector?.Dispose();
	}
}


//C++ TO C# CONVERTER NOTE: The following #define macro was replaced in-line:
//ORIGINAL LINE: #define SOCKET int
