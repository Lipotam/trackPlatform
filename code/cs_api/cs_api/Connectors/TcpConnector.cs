using System;
using TrackPlatform.Basic;

namespace TrackPlatform.Connectors
{
    public class TcpConnector : BasicConnector
    {
        private const int AnswerWaitInMs = 400;

        private byte[] _receivedBuffer = new byte[1];
    
        protected override void Write(byte[] s)
        {
            throw new NotImplementedException();
        }
        protected override byte[] Read()
        {
            throw new NotImplementedException();
        }

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
            throw new NotImplementedException();
        }
        public override void Dispose()
        {
            base.Dispose();
            throw new NotImplementedException();
        }

        public override bool IsConnected()
        {
            throw new NotImplementedException();
        }
        public override void Connect()
        {
            throw new NotImplementedException();
        }
        public override void Disconnect()
        {
            throw new NotImplementedException();
        }
    }
}