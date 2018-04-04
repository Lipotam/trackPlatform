using System.Net.Sockets;

namespace TrackPlatform.Exceptions
{
    public class SocketShutdownException : SocketException
    {
        public SocketShutdownException(int errorCode) : base(errorCode)
        {
        }
    }
}

