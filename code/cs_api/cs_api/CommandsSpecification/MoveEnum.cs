namespace TrackPlatform.CommandsSpecification
{
    public enum MoveEnum
    {
        forward = '\x0001', //move forward: obsolete
        left = '\x0002', //move left: obsolete
        right = '\x0003', //move right: obsolete
        back = '\x0004', //move back: obsolete
        stop = '\x0005', //stop
        forward_speed = '\x0006', //move forward with established speed
        forward_time = '\x0007', //move forward while established time: obsolete
        back_speed = '\x08', //move back with established speed: obsolete
        track_set_speed = '\x09', //choose track and set passed speed
        clockwise = '\x0A', //clockwise rotation with speed
        track_all_set_speed = '\x0B', //set passed speed to every track
    }
}