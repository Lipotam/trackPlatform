#ifndef _COMMANDS_ENUM_H_
#define _COMMANDS_ENUM_H_

enum ControllerEnum {
	movementControllerID = '\001',
	sensorsControllerID = '\002',
	servoControllerID = '\003',
	communicationControllerID = '\004',
};

enum SensorsEnum {
	distance_sensor = '\001',		//get value from single distance senceor
	distance_sensor_all = '\002',	//get value from all distance senceors
	line_sensor = '\003',			//get value from single line senceor
	line_sensor_all = '\004'		//get value from all line senceors
};

enum AreaType {
	light = '\x00',				// light area type
	dark = '\x01',				// dark area type
};

enum MoveEnum {
	forward = '\001',		  //move forward: obsolete
	left = '\002',			  //move left: obsolete
	right = '\003',			  //move right: obsolete
	back = '\004',			  //move back: obsolete
	stop = '\005',			  //stop
	forward_speed = '\006',	  //move forward with established speed
	forward_time = '\007',	  //move forward while established time: obsolete
	back_speed = '\x08',	  //move back with established speed: obsolete
	track_set_speed = '\x09', //choose track and set passed speed
	clockwise = '\x0A',		  //clockwise rotation with speed
};

enum TrackIndex {
	left_track = 0,	//left track id
	right_track = 1	//right track id
};

enum SensorManagerIndex {
	line_sensor_index = 0,
	distance_sensor_index = 1
};

enum ServoIndex {
	xy_plane = 1,	//z axis
	xz_plane = 2,	//y axis
};

enum ServoCommands {
	set_horizontal_angle = '\001',		//set horizontal angle of servo: obsolete
	set_vertical_angle = '\002',		//set vertical angle of servo: obsolete
	set_horiz_vertical_angles = '\003', //set horizontal and verticalse angles of servo: obsolete
	get_coodrinates = '\004',			//get current angels of horizontal and vertical servos: obsolete
	set_angle = '\x05',					//set axis angle
	get_angle = '\x06',					//get axis angle
};

enum CommunicationCommands {
	startCommunicationCommand = 1,		//starting communication command
	stopCommunicationCommand = 2,		//stopping communication command
	refreshConnectionCommunicationCommand = 3,		//refreshing connection timer communication command (since API v3)
};

/**
 * @brief Describes trackPlatform API to working
 * @see https://github.com/Lipotam/trackPlatform/wiki/Api
 * @warning Each API must be described in @ConnectionController handler
 * @warning If you add new version for API, check @ConnectionController::highestAPI field
 */
enum ApiVersion {
	startBasicAPI = 1,							//default API v1
	APIWithAnswer = 2,							//API v2
	APIWithAutoDiconnect = 3,					//API v3
	APIWithCRC = 4,								//API v4
};

#endif /* _COMMANDS_ENUM_H_ */
