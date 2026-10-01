# Arduino TFT Radar

[![Arduino TFT Radar Cover](../covers/arduinoradar.jpg)](https://youtube.com/shorts/XTIOUEK2b3Q?feature=share)

A compact ultrasonic radar project using an Arduino-compatible board, an HC-SR04 sensor, an SG90 servo, an ST7735 TFT display, and a buzzer.

## Demo

https://youtube.com/shorts/XTIOUEK2b3Q?feature=share

## Features

- 180-degree servo sweep
- HC-SR04 distance measurement
- Radar rings, sweep line, and fading red target trail
- Distance readout in centimeters
- Buzzer alert for nearby objects

## Hardware

- Arduino-compatible board
- HC-SR04 ultrasonic sensor
- SG90 servo motor
- ST7735 TFT display
- Passive buzzer

## Wiring

![Arduino TFT Radar Wiring Diagram](../wiring/arduinoradarwiring.jpg)

| Component | Pin |
|---|---|
| TFT CS / DC / RST | 10 / 9 / 8 |
| HC-SR04 TRIG / ECHO | 2 / 3 |
| Servo signal | 6 |
| Buzzer | 7 |

Connect the display, sensor, servo, and buzzer to the appropriate power and ground pins. Install `Adafruit_GFX`, `Adafruit_ST7735`, and `Servo` from the Arduino Library Manager.

## Source

Open the source sketch in this directory, select the board and port, and upload it.
