using System;
using TrackPlatform.Basic;
using TrackPlatform.Connectors;
using TrackPlatform.Other;

namespace TrackPlatform.Api
{
    public class Manager : BasicManagement, IDisposable
    {
        private static BasicConnector createConnectorByMode(ConnectionModes mode, CommunicationInfoStruct info)
        {
            BasicConnector res = null;

            //TODO: add more modes
            switch (mode)
            {
                case ConnectionModes.USB:
                case ConnectionModes.bluetooth:
                    res = new SerialConnector(info.SerialInfo.rxPort, info.SerialInfo.txPort, info.SerialInfo.baudrate);
                    break;
                case ConnectionModes.WiFi:
                    res = new TcpConnector(info.TcpInfo.ip, info.TcpInfo.port);
                    break;
                default:
                    res = null;
                    break;
            }

            return res;
        }

        public Manager(ConnectionModes mode, CommunicationInfoStruct info) : base(createConnectorByMode(mode, info))
        {
        }
        public void Dispose()
        {
            connector?.Dispose();
        }
    }
}
