namespace TrackPlatform.CommandsSpecification
{
    public enum MoveEnum
    {
        Forward = '\x0001',                             //move forward: obsolete
        Left = '\x0002',                                //move left: obsolete
        Right = '\x0003',                               //move right: obsolete
        Back = '\x0004',                                //move back: obsolete
        Stop = '\x0005',                                //stop
        ForwardSpeed = '\x0006',                        //move forward with established speed
        ForwardTime = '\x0007',                         //move forward while established time: obsolete
        BackSpeed = '\x0008',                           //move back with established speed: obsolete
        TrackSetSpeed = '\x0009',                       //choose track and set passed speed
        Clockwise = '\x000A',                           //clockwise rotation with speed
        TrackAllSetSpeed = '\x000B',                    //set passed speed to every track
    }
}