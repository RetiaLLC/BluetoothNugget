# Bluetooth Nugget — example sketches

Bare-bones Arduino examples to get you writing your own Nugget firmware. Each folder is a
standalone `.ino` you can open in the Arduino IDE.

## Setup (once)
1. Arduino IDE → **Boards Manager** → install **esp32 by Espressif**.
2. Select board **"LOLIN S3 Mini"**. Set **PSRAM: QSPI PSRAM**, **USB CDC On Boot: Enabled**.
3. **Library Manager** → install **Adafruit SSD1306**, **Adafruit GFX**, **Adafruit NeoPixel**.

## The examples
| Folder | Shows |
|---|---|
| [`oled_hello/`](oled_hello) | Draw text + a cat face on the 128×64 OLED (I²C on 35/36, flipped) |
| [`buttons_and_ears/`](buttons_and_ears) | Read the 6 buttons; light the two WS2812 "ears" (GPIO10) |
| [`wifi_scan/`](wifi_scan) | Passive Wi-Fi scan, results paged on the OLED |

Pins are in [../docs/pinout.md](../docs/pinout.md). Flash with the IDE, or:

```bash
arduino-cli compile -b esp32:esp32:lolin_s3_mini oled_hello
arduino-cli upload  -b esp32:esp32:lolin_s3_mini -p <PORT> oled_hello
```
