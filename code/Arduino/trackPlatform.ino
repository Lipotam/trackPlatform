#include "Constants.h"
#include "Commands.h"
#include "SoftwareSerial.h"

Constants constants;
SoftwareSerial BTserial(constants.bluetooth_RX, constants.bluetooth_TX);
String inString = "";
Commands commands;

void setup()
{
	Serial.begin(constants.bluetooth_serial_speed);
	BTserial.begin(constants.bluetooth_serial_speed);
	BTserial.listen();
}

void loop()
{
	if (BTserial.available() > 0) {
		while (BTserial.available() > 0) {
			char code = BTserial.read();
			inString += code;
		}

		int com = inString.toInt();
		
		/* should be constants in case from Commands.h, but get error! */
		
		switch (com)
		{
		case 0:
			BTserial.write("TEST: OK");
			break;
		case 1:
			BTserial.write("MOVING FORWARD");
			break;
		case 2:
			BTserial.write("TURNING LEFT");
			break;
		case 3:
			BTserial.write("TURNING RIGHT");
			break;
		case 4:
			BTserial.write("MOVING BACK");
			break;
		default:
			break;
		}

		inString = "";
	}

}
