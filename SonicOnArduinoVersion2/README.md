# SonicOnArduino Version 2

![Sonic Cover](../covers/sonic.jpg)

An upgraded Sonic-style game for Arduino/ESP32 and an SSD1306 128x64 OLED. Version 2 adds new sprites, boss animations, hitboxes, rings, health, and level elements.

## Demo

https://youtube.com/shorts/aVP9bUrWy6I?si=uQBOLwSgrFjfXYXB

## Features

- Player, enemy, and boss sprite bitmaps stored in PROGMEM
- Boss fight with animation frames and hitboxes
- Ring collection and score tracking
- Health, jumping, and gravity
- Buzzer sound feedback

## Hardware

- ESP32 or Arduino
- SSD1306 128x64 I2C OLED
- Passive buzzer
- Momentary button
- Two-axis analog joystick

Typical connections use board I2C pins, buzzer pin 3, button pin 4, and analog inputs A0/A1. Remap these pins when required by your board; ESP32 users should select ADC-capable pins.

## Dependencies and installation

Install Adafruit GFX and Adafruit SSD1306 through the Arduino IDE Library Manager. Open the main sketch in `Source-code`, select the correct board and port, then compile and upload.

Sprites are kept in PROGMEM to reduce RAM usage. The SSD1306 address is typically `0x3C`.
