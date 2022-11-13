/*
 * BME280 temperature and humitdity sensor 
 * - with MQTT publishing 
 * - over Wifi
 * - USB powered
 * - and LED blinking for instant diagnostics
 */

#include <ESP8266WiFi.h>

#include "secrets.h"

boolean wifiWasAlive = true;

void setup() {
  Serial.begin(115200);
  Serial.println();
  setupWifi();
}

void setupWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);
}

void loop() {
  monitorWifi();

  delay(1000);
}

void monitorWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    if (wifiWasAlive == true) {
      wifiWasAlive = false;
      Serial.print("Looking for WiFi ");
    }
    Serial.print(".");
  } else if (wifiWasAlive == false) {
    wifiWasAlive = true;
    Serial.printf(" connected to %s\n", WiFi.SSID().c_str());
    delay(1000);
  }
}
