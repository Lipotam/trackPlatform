using System;

namespace TrackPlatform.Exceptions
{
    public class WSAStartupException : TrackPlatformException
    {
        public WSAStartupException(int errorCode) : base(Convert.ToString(errorCode))
        {
        }
    }
}

