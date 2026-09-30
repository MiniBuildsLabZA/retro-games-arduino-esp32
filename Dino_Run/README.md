# Dino Run Game

![Dino Run Cover](../covers/dinorun.jpg)

A dinosaur-themed endless runner for Arduino/ESP32 with an SSD1306 OLED, joystick controls, obstacle avoidance, collision detection, scoring, and sound effects.

## Demo

https://youtube.com/shorts/9tusvMqC588?si=9XAGFWza56ogSxFT

## Hardware

- Arduino or ESP32
- 128x64 SSD1306 OLED display
- Two-axis analog joystick
- Buzzer

## Controls

| Action | Input |
|---|---|
| Move left | Joystick X < 400 |
| Move right | Joystick X > 600 |
| Jump | Joystick Y > 600 |
| Start | Move joystick left or right |

## Features

- Physics-based movement with gravity and jumping
- Three obstacle types and moving cars
- Dinosaur animation frames and background sprites
- Collision detection and game-over handling
- Score tracking and audio feedback

## Wiring

| Component | Pin |
|---|---|
| OLED SDA | A4 or board SDA |
| OLED SCL | A5 or board SCL |
| Joystick X | A0 |
| Joystick Y | A1 |
| Buzzer | 3 |

## Dependencies

- `Adafruit_GFX.h`
- `Adafruit_SSD1306.h`

Install the libraries through the Arduino IDE Library Manager, open the source file, select your board, and upload the sketch.

Created as part of the DIY Arduino/ESP32 Projects collection. 🦖
