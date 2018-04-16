namespace TrackPlatform.Other
{
    public static class Logger
    {
        #region Private config

        private const string MessageAddingPrefix = "TrackPlaftorm log: ";

        #endregion

        public delegate void LogCallback(string message);

        public static event LogCallback LogMessage;

        public static void Log(string message)
        {
            OnLogMessage(MessageAddingPrefix + message);
        }

        #region Private implementation

        private static void OnLogMessage(string message)
        {
            LogMessage?.Invoke(message);
        }

        #endregion
    }
}