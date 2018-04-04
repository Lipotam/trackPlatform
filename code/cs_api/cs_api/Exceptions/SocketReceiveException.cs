using System.Net.Sockets;

namespace TrackPlatform.Exceptions
{
    public class SocketReceiveException : SocketException
    {
        public SocketReceiveException(int errorCode) : base(errorCode)
        {
        }
    }
}

