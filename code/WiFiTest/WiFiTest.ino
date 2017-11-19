#include "WiFi_my.h"

WiFi_my* pWifi;
void setup() {
	pWifi = new WiFi_my();
}

void loop() {
	delay(1000);
	String data = pWifi->read();
	//pWifi->send(data);
}
