#pragma once


enum ControllerEnum {
	movementControllerID = '\001',
	sensorsControllerID = '\002',
	servoControllerID = '\003'
};

enum SensorsEnum {
	distance_sensor_1 = '\001',
	distance_sensor_2 = '\002',
	distance_sensor_3 = '\003',
	distance_sensor_4 = '\004',
	distance_sensor_5 = '\005',
	distance_sensor_all = '\006',

	line_sensor_1 = '\007',
	line_sensor_2 = '\008',
	line_sensor_3 = '\009',
	line_sensor_4 = '\010',
	line_sensor_5 = '\011',
	line_sensor_all = '\012'
};


enum MoveEnum {
	forward = '\001',		  //move forward
	left = '\002',			  //move left 
	right = '\003',			  //move right
	back = '\004',			  //move back
	stop = '\005',			  //stop
	forward_speed = '\006',	  //move forward with established speed
	forward_time = '\007',	  //move forward while established time
	back_speed = '\008',	  //move back with established speed
	track_set_speed = '\009'  //choose track and set passed speed
};

enum TrackDiraction {
	forward_direction = true,
	back_direction = false
};

enum TrackID {
	left_track = 0,
	right_track = 1
};