namespace TrackPlatform.CommandsSpecification
{
    public enum SensorsEnum
    {
        distance_sensor = '\x0001', //get value from single distance sensor
        distance_sensor_all = '\x0002', //get value from all distance sensors
        line_sensor = '\x0003', //get value from single line sensor
        line_sensor_all = '\x0004', //get value from all line sensors
        raw_distance_sensor = '\x05', //get raw value from single distance sensor
        raw_distance_sensor_all = '\x06', //get raw value from all distance sensors
        raw_line_sensor = '\x07', //get raw value from single line sensor
        raw_line_sensor_all = '\x08', //get raw value from all line sensors
    }
}