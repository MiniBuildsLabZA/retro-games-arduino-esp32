# Racing Game on ESP32

![Racing Game on ESP32 Cover](../covers/esp32racinggame.jpg)

A compact top-down racing game for ESP32 and a 128x64 SSD1306 OLED. Race around a predefined track against AI-controlled cars and view the final finishing position.

## Demo

https://youtube.com/shorts/Xz7EnjQXIHw?feature=share

## Hardware

- ESP32 board
- SSD1306 128x64 I2C OLED
- Four directional buttons

## Wiring

![Racing Game on ESP32 Wiring Diagram](../wiring/esp32racinggamewiring.jpg)

| Component | Connection |
|---|---|
| SSD1306 SDA | GPIO 21 |
| SSD1306 SCL | GPIO 22 |
| OLED power | 3.3V and GND |
| Up button | GPIO 32 |
| Down button | GPIO 33 |
| Left button | GPIO 25 |
| Right button | GPIO 26 |

Wire each button between its GPIO and GND, using the GPIO pull-up configuration.

## Source

Install Adafruit GFX, Adafruit SSD1306, and Wire. Open the source file in this directory, select an ESP32 board and serial port, and upload.
