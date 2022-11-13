/*
   BME280 temperature and humitdity sensor
   - with MQTT publishing
   - over Wifi
   - USB powered
   - and LED blinking for instant diagnostics
*/

#include <ESP8266WiFi.h>

#include "secrets.h"

#define LED_PIN_BLUE  2
#define LED_ON        LOW
#define LED_OFF       HIGH

boolean wifiWasAlive = true;

void setup() {
  setupLED();
  Serial.begin(115200);
  Serial.println();
  notifyStartup();
  setupWifi();
}

void setupLED() {
  pinMode(LED_PIN_BLUE, OUTPUT);
}

void blinkLED(int times, int on_time, int off_time) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN_BLUE, LED_ON);
    delay(on_time);
    digitalWrite(LED_PIN_BLUE, LED_OFF);
    delay(off_time);
  }
}

void notifyStartup() {
  Serial.println("starting...");
  blinkLED(5, 200, 200);
}

void notifyWifiLookup() {
  Serial.print("Looking for WiFi ");
}

void notifyWifiStillTrying() {
  Serial.print(".");
}

void notifyWifiConnected() {
  Serial.printf(" connected to %s\n", WiFi.SSID().c_str());
  blinkLED(1, 2000, 1000);
}

void setupWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);
}

void monitorWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    if (wifiWasAlive == true) {
      wifiWasAlive = false;
      notifyWifiLookup();
    }
    notifyWifiStillTrying();
  } else if (wifiWasAlive == false) {
    wifiWasAlive = true;
    notifyWifiConnected();
  }
}

void endOfLoop() {
  blinkLED(1, 200, 800);
}

void loop() {
  monitorWifi();

  endOfLoop();
}
