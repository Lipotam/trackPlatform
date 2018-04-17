using System;
using System.IO;
using System.Net.Sockets;

namespace TrackPlatform.Connectors
{
    public class TcpConnector : StreamingConnector
    {
        private readonly string _ip;
        private readonly int _port;
        private readonly TcpClient _tcpConnect;

        protected override Stream ReadStream => _tcpConnect.GetStream();
        protected override Stream WriteStream => _tcpConnect.GetStream();

        protected override int ReadAvailable => _tcpConnect.Available;

        /// <summary>
        /// Create TCP/IP connector to trackPlatform
        /// </summary>
        /// <remarks>
        /// Only one object of that class in one moment of time is supported
        /// </remarks>
        /// <param name="ip">IP of trackPlatform Wi-Fi module</param>
        /// <param name="port">Port of TCP/IP server on trackPlatform</param>
        public TcpConnector(string ip, int port)
        {
            _ip = ip;
            _port = port;

            _tcpConnect = new TcpClient
            {
                ReceiveTimeout = ReadWriteTimeoutInMs,
                SendTimeout = ReadWriteTimeoutInMs
            };

            SendStartCommand();
        }

        public override void Dispose()
        {
            base.Dispose();

            //Fixed in newer framework
            //_tcpConnect?.Dispose();
        }

        public override bool IsConnected()
        {
            return (base.IsConnected() && _tcpConnect.Connected);
        }
        public override void Connect()
        {
            _tcpConnect.Connect(_ip, _port);
        }
        public override void Disconnect()
        {
            if (_tcpConnect != null && _tcpConnect.Connected)
            {
                _tcpConnect.Close();
            }
        }
    }
}