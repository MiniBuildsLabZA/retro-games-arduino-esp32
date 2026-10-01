# Bounce on Arduino

[![Bounce Cover](../covers/bounce.jpg)](https://youtu.be/t_ZkNgfslVo)

A bouncing-ball physics game for Arduino with an SSD1306 OLED and interactive paddle controls.

## Hardware

- Arduino-compatible board
- SSD1306 128x64 I2C OLED
- Analog joystick module
- Optional buzzer, if enabled by the sketch

## Wiring

![Bounce Wiring Diagram](../wiring/wiring1.jpg)

Connect the OLED to the board's I2C SDA/SCL pins. Connect the joystick axes to the analog inputs defined in `source_code`, then connect power and ground.

## Source

Open [`source_code`](./source_code) in the Arduino IDE, install the required libraries, select the board and port, and upload.
