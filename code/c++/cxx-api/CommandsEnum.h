#ifndef _COMMANDS_ENUM_H_
#define _COMMANDS_ENUM_H_

enum ControllerEnum {
	movementControllerID = '\001',
	sensorsControllerID = '\002',
	servoControllerID = '\003'
};

enum SensorsEnum {
	distance_sensor = '\001',		//get value from single distance senceor
	distance_sensor_all = '\002',	//get value from all distance senceors
	line_sensor = '\003',			//get value from single line senceor
	line_sensor_all = '\004'		//get value from all line senceors
};


enum MoveEnum {
	forward = '\001',		  //move forward
	left = '\002',			  //move left
	right = '\003',			  //move right
	back = '\004',			  //move back
	stop = '\005',			  //stop
	forward_speed = '\006',	  //move forward with established speed
	forward_time = '\007',	  //move forward while established time
	back_speed = '\010',	  //move back with established speed
	track_set_speed = '\011'  //choose track and set passed speed
};

enum TrackDiraction {
	forward_direction = true, //rotation of track in forward diration
	back_direction = false    //rotation of track in backword diration
};

enum TrackID {
	left_track = 0,	//left track id
	right_track = 1	//right track id
};

enum ServoCommands {
	set_horizontal_angle = '\001',		//set horizontal angle of servo
	set_vertical_angle = '\002',		//set vertical angle of servo
	set_horiz_vertical_angles = '\003', //set horizontal and verticalse angles of servo
	get_coodrinates = '\004',			//get current angels of horizontal and vertical servos
};

#endif /* _COMMANDS_ENUM_H_ */
