#include "WiFi_my.h"

WiFi_my* pWifi;
void setup() {
	pWifi = new WiFi_my();
}

void loop() {
	delay(1000);
	/*
	int num = pWifi->waitClient();
	Serial.println("Get client: " + String(num));
	while (true) {
		String data = pWifi->read();
		Serial.println("data: " + data);
		//pWifi->send(data);
	}
	*/
	while (true) {
		String str = pWifi->getMessage();
		if(str.length()) pWifi->send(str);
	}

}
