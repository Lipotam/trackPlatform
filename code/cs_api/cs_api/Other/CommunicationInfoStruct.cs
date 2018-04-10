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
            public string RxPort { get; set; } = string.Empty;
            public string TxPort { get; set; } = string.Empty;
            public int Baudrate  { get; set; } = 0;
        }
        public readonly SerialConnectionInfo SerialInfo = new SerialConnectionInfo();

        public class TcpConnectionInfo
        {
            public string Ip { get; set; } = string.Empty;
            public int Port { get; set; } = 0;
        }
        public readonly TcpConnectionInfo TcpInfo = new TcpConnectionInfo();
    }
}

