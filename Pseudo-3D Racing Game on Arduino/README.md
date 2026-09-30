# Pseudo-3D Racing Game on Arduino

![Pseudo-3D Racing Cover](../covers/pseudo3D.jpg)

A retro-style pseudo-3D racing game for Arduino/ESP32 with perspective road rendering, a player car, an AI opponent, animated sprites, countdown audio, and race results.

## Demo

https://youtu.be/6mhX6DsA06M

## Features

- Perspective-based road rendering
- Curved scrolling track
- Player versus AI opponent
- Random nose/turbo boost events
- Direction-aware car sprites
- Start countdown and finish flags
- Win, loss, and draw results

## Hardware

- Arduino-compatible board or ESP32
- SSD1306 128x64 I2C OLED
- Analog joystick: X on A0, Y on A1
- Speaker/buzzer on pin 3

## Controls

- Up: accelerate
- Down: decelerate
- Left/right: steer
- Center: drive straight

Install Adafruit GFX and Adafruit SSD1306, connect the hardware, open the source sketch, select the board and port, and upload. The project uses PROGMEM for bitmap assets and updates at approximately 40 ms per frame.
