// Bluetooth Nugget — OLED hello world
// 128x64 SSD1306-compatible OLED on I2C: SDA=35, SCL=36, addr 0x3C.
// The panel is mounted 180°, so we setRotation(2) to render upright.
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SDA_PIN 35
#define SCL_PIN 36
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(2);            // panel is mounted upside-down
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(6, 4);
  display.println("Bluetooth");
  display.setCursor(28, 22);
  display.println("Nugget");
  // a tiny cat face
  display.setTextSize(1);
  display.setCursor(40, 48);
  display.println("=^..^=");
  display.display();
}

void loop() {}
