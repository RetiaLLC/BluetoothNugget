// Bluetooth Nugget — passive Wi-Fi scan on the OLED
// Lists nearby networks (SSID / channel / RSSI). Fully passive: it only listens.
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  Serial.begin(115200);
  Wire.begin(35, 36);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(2);
  display.setTextColor(SSD1306_WHITE);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
}

void loop() {
  int n = WiFi.scanNetworks(false /*async*/, false /*hidden*/, true /*passive*/);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.printf("Wi-Fi: %d nets\n", n);
  for (int i = 0; i < n && i < 6; i++) {
    String s = WiFi.SSID(i);
    if (s.length() > 14) s = s.substring(0, 14);
    display.printf("%-14s %d\n", s.c_str(), WiFi.RSSI(i));
  }
  display.display();
  WiFi.scanDelete();
  delay(3000);
}
