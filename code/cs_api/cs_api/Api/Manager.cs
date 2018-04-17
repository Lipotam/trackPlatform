using System;
using TrackPlatform.Basic;
using TrackPlatform.Connectors;
using TrackPlatform.Other;

namespace TrackPlatform.Api
{
    public class Manager : BasicManagement, IDisposable
    {
        private static BasicConnector CreateConnectorByMode(ConnectionModes mode, CommunicationInfoStruct info)
        {
            BasicConnector res;

            //TODO: add more modes
            switch (mode)
            {
                case ConnectionModes.Usb:
                case ConnectionModes.Bluetooth:
                    res = new SerialConnector(info.SerialInfo.RxPort, info.SerialInfo.TxPort, info.SerialInfo.Baudrate);
                    break;
                case ConnectionModes.WiFi:
                    res = new TcpConnector(info.TcpInfo.Ip, info.TcpInfo.Port);
                    break;
                default:
                    res = null;
                    break;
            }

            return res;
        }

        public Manager(ConnectionModes mode, CommunicationInfoStruct info) : base(CreateConnectorByMode(mode, info))
        {
        }
        public void Dispose()
        {
            Connector?.Dispose();
        }
    }
}
