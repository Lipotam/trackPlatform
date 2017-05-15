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
	forward = '\001',
	left = '\002',
	right = '\003',
	back = '\004',
	stop = '\005'
};

enum TrackDiraction {
	forward_direction = true,
	back_direction = false
};