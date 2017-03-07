#include <WiFi.h>

char ssid[] = "TP_LINK-0980";
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while(true);
  }
  if ( status != WL_CONNECTED) {
      Serial.println("No wifi connection");
      while(true);
  }
  else {
    Serial.print("Connected");
  }
}

void loop() {
  delay(5000);
  printWifiData();
  printRouterData();
}

void printWifiData() {
  IPAddress ip = WiFi.localIP();
  Serial.print("IP: ");
  Serial.println(ip);
}

void printRouterData() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
}
