# WLEDkitty for the Bluetooth Nugget — build recipe

WLED ([wled/WLED](https://github.com/wled/WLED)) tuned for the Bluetooth Nugget
(LOLIN S3 Mini, ESP32-S3, 4 MB). Boots into a Pride rainbow on the onboard ears,
shows live status on the 128×64 OLED, and adds on-device button control.

## PlatformIO env (`platformio_override.ini`)

```ini
[env:nugget]
extends = env:esp32s3_4M_qspi            ; board = lolin_s3_mini, 4MB, qio_qspi PSRAM
custom_usermods = usermod_v2_four_line_display_ALT
build_flags = ${env:esp32s3_4M_qspi.build_flags}
  -D DATA_PINS=10                        ; onboard 2x WS2812 ears (chainable out J4)
  -D DEFAULT_LED_COUNT=2
  -D BTNPIN=44,43,13,18,11,12            ; A, B, UP, DOWN, LEFT, RIGHT
  -D I2CSDAPIN=35
  -D I2CSCLPIN=36
  -D FLD_TYPE=SSD1306_64                 ; 128x64 SSD1306-compatible (SH1106/CH1116)
  -D FLD_FLIP_DEFAULT                    ; OLED mounted 180deg
  -D DEFAULT_MODE=63                     ; boot effect = Pride 2015
  -D DEFAULT_BOOT_FX=63                  ; global effectCurrent also set (led.cpp applies it over the segment)
```

## Two small WLED source patches (also needed for the badge build)

- `wled00/button.cpp`: D-pad handlers (button indices 2-5): UP/DOWN = brightness +/-,
  LEFT/RIGHT = primary-color hue -/+ (short = step, long = repeat).
- `usermods/usermod_v2_four_line_display_ALT/usermod_v2_four_line_display.h`: guard the
  `flip` default behind `FLD_FLIP_DEFAULT` so the 180° mount is baked in.

## Build & merge

```bash
pio run -e nugget
esptool --chip esp32s3 merge-bin -o wledkitty-nugget.factory.bin \
  --flash-mode dio --flash-freq 80m --flash-size 4MB \
  0x0 bootloader.bin 0x8000 partitions.bin 0xE000 boot_app0.bin 0x10000 firmware.bin
```

## Flash

```bash
esptool --chip esp32s3 --port <PORT> write-flash 0x0 wledkitty-nugget.factory.bin
```

Controls: **A** on/off · **B** next effect · **UP/DOWN** brightness · **LEFT/RIGHT** color.
Join `WLED-AP` (pw `wled1234`) → http://4.3.2.1 for the full web UI.
