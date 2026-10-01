# SonicOnArduino Version 2

[![Sonic v2 Cover](../covers/sonicv2.jpg)](https://youtube.com/shorts/6b8Iq4P6gBc?feature=share)

An upgraded Sonic-style game for Arduino/ESP32 and an SSD1306 128x64 OLED. Version 2 adds new sprites, boss animations, hitboxes, rings, health, and level elements.

## Demo

https://youtube.com/shorts/6b8Iq4P6gBc?feature=share

## Hardware

- ESP32 or Arduino
- SSD1306 128x64 I2C OLED
- Passive buzzer
- Momentary button
- Two-axis analog joystick

## Wiring

![Sonic v2 Wiring Diagram](../wiring/wiring1.jpg)

| Component | Pin |
|---|---|
| OLED SDA | board SDA |
| OLED SCL | board SCL |
| Buzzer | 3 |
| Button | 4 |
| Joystick X | A0 |
| Joystick Y | A1 |

Remap these pins when required by your board; ESP32 users should select ADC-capable pins.

## Source

Install Adafruit GFX and Adafruit SSD1306, then open the main sketch in [`Source-code`](./Source-code), select the correct board and port, and upload.
