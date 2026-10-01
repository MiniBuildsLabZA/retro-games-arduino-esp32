# Block Breaker on Arduino

![Block Breaker Cover](../covers/blockbreaker.jpg)

A classic block-breaking game for Arduino with an SSD1306 OLED, joystick paddle controls, collision detection, and score tracking.

## Hardware

[Block Breaker Wiring Diagram]

- Arduino-compatible board
- SSD1306 128x64 I2C OLED
- Analog joystick module
- Optional buzzer, if enabled by the sketch

## Wiring

Use the board's I2C pins for the OLED. Connect the joystick X and Y outputs to the analog inputs used in `Source-code`; connect power and ground to the corresponding board pins.

## Source

Open [`Source-code`](./Source-code) in the Arduino IDE, install the required display libraries, select the board and port, and upload.
