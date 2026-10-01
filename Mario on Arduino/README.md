# Mario on Arduino 🎮

![Mario Cover](../covers/mario.jpg)

A Super Mario-style platformer for Arduino/ESP32 with an SSD1306 OLED, joystick controls, physics, enemies, collectibles, and sound effects.

## Demo

https://youtube.com/shorts/EBJ509lZZzw?si=qdLsbm_wCAou-vTR

## Hardware

[Mario Wiring Diagram]

- Arduino or ESP32
- Adafruit SSD1306 128x64 OLED
- Analog joystick on A0/A1
- Buzzer on digital pin 3

## Wiring

```text
Joystick X -> A0
Joystick Y -> A1
OLED SDA/SCL -> board I2C pins
Buzzer signal -> Digital pin 3
```

## Source

Install Adafruit GFX and Adafruit SSD1306, then open [`Source_Code`](./Source_Code), select the board and port, and upload.
