# Mega Man On Arduino

![Mega Man Cover](../covers/megaman.jpg)

A Mega Man-inspired platformer/shooter for Arduino/ESP32 with an SSD1306 128x64 OLED, animated sprites, enemy patterns, projectiles, hitboxes, score, lives, and buzzer effects.

## Hardware

[Mega Man Wiring Diagram]

- Arduino Uno/Nano or ESP32
- SSD1306 128x64 I2C OLED
- Push buttons or joystick
- Passive buzzer

The default sketch uses OLED SDA/SCL, buzzer D3, movement buttons D4/D5, jump D6, and shoot D7. Adjust pin definitions for ESP32 or another board.

## Source

Install Adafruit GFX and Adafruit SSD1306, open the sketch in [`source_code`](./source_code), connect the hardware, select the board and port, and upload.
