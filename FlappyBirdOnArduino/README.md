# Flappy Bird on Arduino

![Flappy Bird Cover](../covers/flappybird.jpg)

A Flappy Bird-style game for Arduino with an SSD1306 128x64 OLED, button control, scrolling backgrounds, animated birds, pipes, scoring, and collision detection.

## Demo

https://youtube.com/shorts/XYnEovBdsMg?feature=share

## Hardware

- Arduino Uno, Nano, or compatible board
- SSD1306 128x64 I2C OLED
- Push button on pin 4
- Optional passive buzzer on pin 3

## How to play

Press the button to flap upward and release it to fall. Avoid the pipes, score by passing them, and press the button to restart after game over.

## Features

- Three-frame flapping and falling animations
- Four simultaneous pipes with variable gaps
- Oscillating pipe movement and dynamic spacing
- AABB collision detection
- Score beep and score display
- Parallax background and game-over screen

Install Adafruit GFX and Adafruit SSD1306 through the Arduino IDE Library Manager, open `SourceCode`, select the board and port, and upload the sketch. The default display address is `0x3C`.
