# Mario on Arduino 🎮

![Mario Cover](../covers/mario.jpg)

A Super Mario-style platformer for Arduino/ESP32 with an SSD1306 OLED, joystick controls, physics, enemies, collectibles, and sound effects.

## Demo

https://youtube.com/shorts/EBJ509lZZzw?si=qdLsbm_wCAou-vTR

## Features

- Smooth left/right movement with camera scrolling
- Gravity, jumping, and falling mechanics
- Tortoise and bug enemies
- Destructible bricks, power-up blocks, flowers, stairs, a castle, and a flag
- Collision detection and victory conditions
- Buzzer sound effects and a victory melody

## Hardware

- Arduino or ESP32
- Adafruit SSD1306 128x64 OLED
- Analog joystick on A0/A1
- Buzzer on digital pin 3

## Controls

| Input | Action |
|---|---|
| Joystick right | Move right / scroll |
| Joystick left | Move left / scroll |
| Joystick up | Jump |

## Wiring

```text
Joystick X -> A0
Joystick Y -> A1
OLED SDA/SCL -> board I2C pins
Buzzer signal -> Digital pin 3
```

## Installation

Install Adafruit GFX and Adafruit SSD1306 using the Arduino IDE Library Manager. Open `Source_Code`, select the board and port, connect the hardware, and upload the sketch.

Sprites and backgrounds are stored in PROGMEM to reduce RAM usage. 🍄
