using System.Net.Sockets;

namespace TrackPlatform.Exceptions
{
    public class SocketSendException : SocketException
    {
        public SocketSendException(int errorCode) : base(errorCode)
        {
        }
    }
}

