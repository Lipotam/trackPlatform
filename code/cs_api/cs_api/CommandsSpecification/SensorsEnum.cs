namespace TrackPlatform.CommandsSpecification
{
    public enum SensorsEnum
    {
        DistanceSensor = '\x0001',          //get value from single distance sensor
        DistanceSensorAll = '\x0002',       //get value from all distance sensors
        LineSensor = '\x0003',              //get value from single line sensor
        LineSensorAll = '\x0004',           //get value from all line sensors
        RawDistanceSensor = '\x05',         //get raw value from single distance sensor
        RawDistanceSensorAll = '\x06',      //get raw value from all distance sensors
        RawLineSensor = '\x07',             //get raw value from single line sensor
        RawLineSensorAll = '\x08',          //get raw value from all line sensors
    }
}