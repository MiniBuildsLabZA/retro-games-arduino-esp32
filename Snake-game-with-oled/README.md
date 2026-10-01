# Snake Game with OLED

A classic Snake game with OLED display support and joystick controls.

## Hardware

[Snake Game Wiring Diagram]

- Arduino-compatible board or ESP32
- SSD1306 128x64 I2C OLED
- Two-axis analog joystick
- Optional buzzer, if enabled by the sketch

## Wiring

Connect the OLED to the board's I2C SDA/SCL pins and the joystick axes to the analog inputs defined in `Source-code`. Connect all modules to the appropriate power and ground pins.

## Source

Open [`Source-code`](./Source-code) in the Arduino IDE, install the required OLED libraries, select the board and port, and upload.
