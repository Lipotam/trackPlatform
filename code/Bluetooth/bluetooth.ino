#include <SoftwareSerial.h>
SoftwareSerial BTserial(50, 51); // RX | TX

char c = ' ';

void setup()
{
  Serial.begin(9600);
  Serial.println("Arduino is ready");

  BTserial.begin(9600);

  BTserial.listen();
}

void loop()
{
  if (BTserial.available())
  {
    c = BTserial.read();
    Serial.write(c);
  }
  
  if (Serial.available())
  {
    c =  Serial.read();
    BTserial.write(c);
  }
}
