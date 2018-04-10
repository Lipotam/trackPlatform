namespace TrackPlatform.CommandsSpecification
{
    public enum ServoCommands
    {
        set_horizontal_angle = '\x0001', //set horizontal angle of servo: obsolete
        set_vertical_angle = '\x0002', //set vertical angle of servo: obsolete
        set_horiz_vertical_angles = '\x0003', //set horizontal and verticalse angles of servo: obsolete
        get_coodrinates = '\x0004', //get current angels of horizontal and vertical servos: obsolete
        set_angle = '\x05', //set axis angle
        get_angle = '\x06', //get axis angle
    }
}