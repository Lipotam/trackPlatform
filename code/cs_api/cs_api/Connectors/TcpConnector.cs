using System;
using TrackPlatform.Basic;

namespace TrackPlatform.Connectors
{
    public class TcpConnector : BasicConnector
    {
        private const int AnswerWaitInMs = 400;

        private byte[] _receivedBuffer = new byte[1];
    
        protected override void write(byte[] s)
        {
            throw new NotImplementedException();
        }
        protected override byte[] read()
        {
            throw new NotImplementedException();
        }

        /**
	 * @brief Create TCP/IP connector to trackPlatform
	 * @warning Only one object of that class in one moment of time is supported
	 *
	 * @param ip IP of trackPlatform Wi-Fi module
	 * @warning Supports only single IP, no masks
	 * @param port Port of TCP/IP server on trackPlatform
	 */
        public TcpConnector(string ip, int port)
        {
            throw new NotImplementedException();
        }
        public override void Dispose()
        {
            this.disconnect();
            base.Dispose();
            throw new NotImplementedException();
        }

        public override bool isConnected()
        {
            throw new NotImplementedException();
        }
        public override void connect()
        {
            throw new NotImplementedException();
        }
        public override void disconnect()
        {
            //if api is connected to arduino
            if (isConnected())
            {
                sendStopCommand();
            }
            throw new NotImplementedException();
        }
    }
}