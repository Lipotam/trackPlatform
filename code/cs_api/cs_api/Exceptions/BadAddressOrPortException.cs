using System;

namespace TrackPlatform.Exceptions
{
    public class BadAddressOrPortException : TrackPlatformException
    {
        public BadAddressOrPortException(int errorCode) : base(Convert.ToString(errorCode))
        {
        }
    }
}

