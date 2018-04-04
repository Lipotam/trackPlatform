public enum ControllerEnum
{
	movementControllerID = '\x0001',
	sensorsControllerID = '\x0002',
	servoControllerID = '\x0003',
	communicationControllerID = '\x0004',
}

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

public enum AreaType
{
	light = '\x00', // light area type
	dark = '\x01', // dark area type
}

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

public enum TrackIndex
{
	left_track = 0, //left track id
	right_track = 1 //right track id
}

public enum SensorManagerIndex
{
	line_sensor_index = 0,
	distance_sensor_index = 1
}

public enum ServoIndex
{
	xy_plane = 1, //z axis
	xz_plane = 2, //y axis
}

public enum ServoCommands
{
	set_horizontal_angle = '\x0001', //set horizontal angle of servo: obsolete
	set_vertical_angle = '\x0002', //set vertical angle of servo: obsolete
	set_horiz_vertical_angles = '\x0003', //set horizontal and verticalse angles of servo: obsolete
	get_coodrinates = '\x0004', //get current angels of horizontal and vertical servos: obsolete
	set_angle = '\x05', //set axis angle
	get_angle = '\x06', //get axis angle
}

public enum CommunicationCommands
{
	startCommunicationCommand = 1, //starting communication command
	stopCommunicationCommand = 2, //stopping communication command
	refreshConnectionCommunicationCommand = 3, //refreshing connection timer communication command (since API v3)
}

/**
 * @brief Describes trackPlatform API to working
 * @see https://github.com/Lipotam/trackPlatform/wiki/Api
 * @warning Each API must be described in @ConnectionController handler
 * @warning If you add new version for API, check @ConnectionController::highestAPI field
 */
public enum ApiVersion
{
	startBasicAPI = 1, //default API v1
	APIWithAnswer = 2, //API v2
	APIWithAutoDiconnect = 3, //API v3
	APIWithCRC = 4, //API v4
}

