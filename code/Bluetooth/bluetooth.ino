#include <SoftwareSerial.h>

SoftwareSerial BTserial(2, 3);
char data = '';

void setup()
{
	Serial.begin(9600);
	BTserial.begin(9600);  
}

void loop()
{
	if (BTserial.available() > 0)
	{
		data = BTserial.read();
		Serial.print(data);
		Serial.print("\n");
	}
}
