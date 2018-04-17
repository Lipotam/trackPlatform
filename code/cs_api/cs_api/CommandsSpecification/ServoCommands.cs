namespace TrackPlatform.CommandsSpecification
{
    public enum ServoCommands
    {
        SetHorizontalAngle = '\x0001',      //set horizontal angle of servo: obsolete
        SetVerticalAngle = '\x0002',        //set vertical angle of servo: obsolete
        SetHorizVerticalAngles = '\x0003',  //set horizontal and verticalse angles of servo: obsolete
        GetCoodrinates = '\x0004',          //get current angels of horizontal and vertical servos: obsolete
        SetAngle = '\x05',                  //set axis angle
        GetAngle = '\x06',                  //get axis angle
    }
}