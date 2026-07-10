# Bluetooth Nugget — pinout (rev 3.x)

The Bluetooth Nugget is a **LOLIN/Wemos S3 Mini** (ESP32-S3FH4R2) socketed onto the
cat-shaped Nugget PCB. This is the GPIO map the firmware in this repo uses.

## On-board peripherals

| Peripheral | Part | GPIO | Notes |
|---|---|---|---|
| **OLED display** | 128×64 I²C (SH1106/CH1116, SSD1306-compatible) | **SDA = GPIO35, SCL = GPIO36** | I²C address `0x3C`. Mounted 180° — set the driver to rotation-2 / flip (SSD1306 driver renders with no column offset). |
| **Button UP** | tactile, active-low | **GPIO13** | pulled up |
| **Button DOWN** | tactile, active-low | **GPIO18** | pulled up |
| **Button LEFT** | tactile, active-low | **GPIO11** | pulled up |
| **Button RIGHT** | tactile, active-low | **GPIO12** | pulled up |
| **Button A** | tactile, active-low | **GPIO44** | pulled up (also UART0 RX) |
| **Button B** | tactile, active-low | **GPIO43** | pulled up (also UART0 TX) |
| **BOOT** | on the S3 Mini module | **GPIO0** | usable as a 7th button |
| **RGB "ears"** | 2× WS2812 (D1 = left, D2 = right) | **GPIO10 (data)** | chainable out to J4 for more pixels |

> All six face buttons read `LOW` when pressed. Use `pinMode(pin, INPUT_PULLUP)`.

## Connectors

| Connector | Pins |
|---|---|
| **J2 — QWIIC / I²C** | SCL = GPIO36 · SDA = GPIO35 · 3.3V · GND (same bus as the OLED) |
| **J4 — external NeoPixel** | 5V · **NPXL = GPIO10** · GND (level-shifted 5V data for an off-board strip) |
| **J8 — SAO v2** | GND · 3.3V · SDA(GPIO35) · SCL(GPIO36) · GPIO04 · GPIO02 |
| **Left header** | 5V · NPXL(GPIO10) · GND · 3.3V · GND · GPIO16 · GPIO04 · GPIO02 |
| **Top header** | GPIO43 · GPIO44 · GPIO36 · GPIO35 · GPIO18 · GPIO16 · GND · 5V |
| **Solder pads** (both ears) | 3.3V · LED OUT (GPIO10 chain) · GND |

## Optional RFM95 LoRa backpack

Not used by any firmware in this repo, but for reference the backpack taps:

| Signal | GPIO |
|---|---|
| SCK | 6 |
| MISO | 7 |
| MOSI | 8 |
| CS / NSS | 9 |
| DIO0 / IRQ | 16 |
| RESET | 4 |

The backpack deliberately uses GPIO 6/7/8/9 (unrouted on the base board) so the buttons
stay live while LoRa runs.

## Free GPIO (no backpack fitted)

**GPIO 6, 7, 8, 9, 16, 4, 2** are free for your own projects. Taken: 10 (NeoPixel),
11/12/13/18/43/44 (buttons), 35/36 (I²C/OLED).

## Build target

- **PlatformIO:** `board = lolin_s3_mini`, `board_build.arduino.memory_type = qio_qspi`, `-D ARDUINO_USB_CDC_ON_BOOT=1`
- **Arduino IDE / arduino-cli:** board **"LOLIN S3 Mini"** (`esp32:esp32:lolin_s3_mini`); Flash 4 MB, PSRAM **QSPI**, USB CDC On Boot **Enabled**
- It enumerates over **native USB** (`/dev/cu.usbmodem*`); the console is USB-CDC serial at 115200.
