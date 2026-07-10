// Bluetooth Nugget — buttons + NeoPixel "ears"
// Reads the 6 face buttons (active-low) and lights the 2 WS2812 ears on GPIO10.
// UP/DOWN change brightness, LEFT/RIGHT cycle color, A = white flash, B = off.
#include <Adafruit_NeoPixel.h>

#define UP 13
#define DOWN 18
#define LEFT 11
#define RIGHT 12
#define BTN_A 44
#define BTN_B 43
const int BUTTONS[] = {UP, DOWN, LEFT, RIGHT, BTN_A, BTN_B};

#define EARS_PIN 10
#define EARS_N   2
Adafruit_NeoPixel ears(EARS_N, EARS_PIN, NEO_GRB + NEO_KHZ800);

uint16_t hue = 0;
uint8_t  bright = 40;      // start dim — the ears are bright!

void setup() {
  Serial.begin(115200);
  for (int p : BUTTONS) pinMode(p, INPUT_PULLUP);
  ears.begin();
  ears.setBrightness(bright);
  ears.show();
}

void loop() {
  if (!digitalRead(UP))    bright = min(bright + 5, 255);
  if (!digitalRead(DOWN))  bright = max(bright - 5, 0);
  if (!digitalRead(LEFT))  hue -= 512;
  if (!digitalRead(RIGHT)) hue += 512;

  uint32_t color = ears.ColorHSV(hue);
  if (!digitalRead(BTN_A)) color = ears.Color(255, 255, 255);  // white flash
  if (!digitalRead(BTN_B)) color = 0;                          // off

  ears.setBrightness(bright);
  ears.fill(color);
  ears.show();
  delay(40);
}
