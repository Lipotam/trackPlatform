//All constants are binded for Arduino Mega without Extension Shield
#include <SoftwareSerial.h>
SoftwareSerial BTserial(50, 51); // RX | TX

char c = ' ';

void setup()
{
  Serial.begin(9600);
  Serial.println("Arduino is ready");

  // HC-05 default serial speed for commincation mode is 9600
  BTserial.begin(9600);

  BTserial.listen();
  if (BTserial.isListening()) {
    Serial.println("Listening");
  }
}

void loop()
{
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTserial.available())
  {
    c = BTserial.read();
    Serial.write(c);
  }

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
  {
    c =  Serial.read();
    Serial.println(c);
    BTserial.write(c);
  }
}
