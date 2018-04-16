using System;

namespace TrackPlatform.Exceptions
{
    public class TrackPlatformException : Exception
    {
        public TrackPlatformException()
        {
        }

        public TrackPlatformException(string errorMessage) : base(errorMessage)
        {
        }
    }
}
