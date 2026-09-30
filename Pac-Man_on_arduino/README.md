# Pac-Man on Arduino

![Pac-Man Cover](../covers/pacman.jpg)

A classic Pac-Man game for Arduino/ESP32 with a 128x64 SSD1306 OLED, joystick input, maze nodes, pellets, animated sprites, ghosts, and buzzer sounds.

## Demo

https://youtube.com/shorts/aVP9bUrWy6I?si=33jqzH-mrr6xtznP

## Features

- Four-direction joystick control with buffered turns
- Maze navigation using connected path nodes
- Four ghosts with random pathfinding
- Pellet collection and scoring
- Collision detection and sprite animation
- Buzzer feedback

## Hardware

- Arduino-compatible board or ESP32
- SSD1306 128x64 I2C OLED
- Analog joystick on A0/A1
- Buzzer on pin 2

Install Adafruit GFX and Adafruit SSD1306 using the Arduino IDE Library Manager. Connect the display and controls, upload the sketch, and start playing.
