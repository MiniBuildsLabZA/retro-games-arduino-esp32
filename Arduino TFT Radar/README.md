# Arduino TFT Radar

![Arduino TFT Radar Cover](../covers/arduinoradar.jpg)

A compact ultrasonic radar project using an Arduino-compatible board, an HC-SR04 sensor, an SG90 servo, an ST7735 TFT display, and a buzzer.

## Demo

https://youtube.com/shorts/XTIOUEK2b3Q?feature=share

## Features

- 180-degree servo sweep
- HC-SR04 distance measurement
- Radar rings, sweep line, and fading red target trail
- Distance readout in centimeters
- Buzzer alert for nearby objects

## Hardware and pins

| Component | Pin |
|---|---|
| TFT CS / DC / RST | 10 / 9 / 8 |
| HC-SR04 TRIG / ECHO | 2 / 3 |
| Servo signal | 6 |
| Buzzer | 7 |

Connect the display, sensor, servo, and buzzer to the appropriate power and ground pins. Install `Adafruit_GFX`, `Adafruit_ST7735`, and `Servo` from the Arduino Library Manager.

## How it works

The sensor measures distance at each servo angle. Valid measurements are projected onto the radar display and retained briefly as a fading trail. Open `Source Code`, select the board and port, then upload the sketch.

## Notes

The plotted range is configured for 10 cm. If no echo is received, the display shows `--`. Ensure the servo has an adequate power supply.
