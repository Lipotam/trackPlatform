/**
 * @brief Information to communicator. 
 * @attention You must fill info about required communication before send it to class constructor
 */
namespace TrackPlatform.Other
{
    public class CommunicationInfoStruct
    {
        public class SerialConnectionInfo
        {
            public string rxPort;
            public string txPort;
            public int baudrate;
        }
        public readonly SerialConnectionInfo SerialInfo = new SerialConnectionInfo();

        public class TcpConnectionInfo
        {
            public string ip;
            public int port;
        }
        public readonly TcpConnectionInfo TcpInfo = new TcpConnectionInfo();
    }
}

