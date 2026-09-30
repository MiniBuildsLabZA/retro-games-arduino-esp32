# Mega Man On Arduino

![Mega Man Cover](../covers/megaman.jpg)

A Mega Man-inspired platformer/shooter for Arduino/ESP32 with an SSD1306 128x64 OLED, animated sprites, enemy patterns, projectiles, hitboxes, score, lives, and buzzer effects.

## Demo

https://youtube.com/shorts/n5QhOsj3owc?si=HiZ63yME2TeshqBR

## Features

- Left/right movement and jumping
- Projectile shooting
- Multiple enemy states and types
- Hitbox-based collision detection
- Score and lives HUD
- Bitmap sprites stored in PROGMEM
- Passive buzzer sound effects

## Hardware

- Arduino Uno/Nano or ESP32
- SSD1306 128x64 I2C OLED
- Push buttons or joystick
- Passive buzzer

The default sketch uses OLED SDA/SCL, buzzer D3, movement buttons D4/D5, jump D6, and shoot D7. Adjust pin definitions for ESP32 or another board.

## Installation

Install Adafruit GFX and Adafruit SSD1306 through the Arduino IDE Library Manager. Open the sketch in `source_code`, connect the hardware, select the board and port, and upload.

Use the left/right controls to move, the jump control to jump, and the shoot control to fire. Happy gaming!
