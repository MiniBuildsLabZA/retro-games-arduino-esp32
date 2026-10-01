# Toggle ON/OFF Motor

A touchscreen toggle project for controlling a motor with an Arduino and TFT-enabled interface.

## Hardware

[Toggle ON/OFF Motor Wiring Diagram]

- Arduino-compatible TFT-enabled board
- TFT touchscreen
- Motor and suitable external motor power supply
- Transistor or motor driver and flyback diode where required

## Wiring

Use the existing [`toggle_wiring_diagram.PNG`](./toggle_wiring_diagram.PNG) as the wiring reference. Do not power a motor directly from an Arduino GPIO; use an appropriately rated driver circuit and common ground.

## Source

Open the sketch in [`source-code`](./source-code), select the board and port, verify the touchscreen calibration and motor-driver wiring, and upload.
