namespace TrackPlatform.CommandsSpecification
{
    public enum CommunicationCommands
    {
        Start = 1,                  //starting communication command
        Stop = 2,                   //stopping communication command
        RefreshConnection = 3,      //refreshing connection timer communication command (since API v3)
    }
}