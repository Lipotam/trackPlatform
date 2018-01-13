#include "WiFi_my.h"

WiFi_my* pWifi;
void setup() {
	pWifi = new WiFi_my();
}

char readOneSymbol() {
	Serial.println("Input choice: ");
	while (1) {
		if (Serial.available()) {
			return Serial.read();
		}
	}
}
void loop() {
	delay(1000);
	char c, id;
	String str("zero");
	do {
		c = readOneSymbol();
		switch (c)
		{
		case '1':
			str = pWifi->read();
			Serial.println("read: " + str);
			break;
		case '2':
			pWifi->send(str);
			break;
		case '3':
			Serial.print("Input id: ");
			id = readOneSymbol();
			pWifi->stopConnection(id);
			break;

		}
	} while (c != 'q');

}
