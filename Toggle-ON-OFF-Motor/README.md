# Toggle ON/OFF Motor

![Toggle Motor Cover](../covers/togglemotor.jpg)

A touchscreen toggle project for controlling a motor with an Arduino and TFT-enabled interface.

## Hardware

- Arduino-compatible TFT-enabled board
- TFT touchscreen
- Motor
- Transistor or motor driver and flyback diode
- External motor power supply

## Wiring

![Toggle ON/OFF Motor Wiring Diagram](../wiring/toggle_wiring_diagram.jpg)

See the wiring reference diagram above. Do not power a motor directly from an Arduino GPIO; use an appropriately rated driver circuit and common ground.

## Source

Open the sketch in [`source-code`](./source-code), select the board and port, verify the touchscreen calibration and motor-driver wiring, and upload.
