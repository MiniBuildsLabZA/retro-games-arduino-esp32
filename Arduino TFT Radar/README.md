# Arduino TFT Radar

A simple radar system built with an ESP32/Arduino-compatible board, an HC-SR04 ultrasonic sensor, a servo motor, and a 1.8" TFT display. The project draws a rotating radar sweep, plots detected objects as fading red points, and beeps when an obstacle is close.

## Features

- Real-time radar sweep on a TFT display
- Ultrasonic distance measurement using HC-SR04
- Servo-driven scanning from 0° to 180°
- Fading trail visualization for detected objects
- Buzzer alert for nearby obstacles
- Distance readout in centimeters on screen

## Hardware Required

- Arduino-compatible board (ESP32/Arduino Uno style code is used here)
- 1.8" ST7735 TFT display
- HC-SR04 ultrasonic sensor
- SG90 or similar servo motor
- Active buzzer
- Jumper wires and breadboard

## Wiring

### TFT Display (ST7735)

- CS -> 10
- DC -> 9
- RST -> 8
- VCC -> 5V
- GND -> GND

### HC-SR04 Ultrasonic Sensor

- TRIG -> 2
- ECHO -> 3
- VCC -> 5V
- GND -> GND

### Servo Motor

- Signal -> 6
- VCC -> 5V
- GND -> GND

### Buzzer

- Positive -> 7
- Negative -> GND

## Software Requirements

Install these Arduino libraries:

- Adafruit_GFX
- Adafruit_ST7735
- Servo

You can install them via the Arduino Library Manager.

## Project Structure

- `Source Code` - main Arduino sketch for the radar system

## Usage

1. Open the sketch in the Arduino IDE.
2. Select the correct board and COM port.
3. Upload the sketch to the microcontroller.
4. Power the circuit and observe the radar sweep.

## Notes

- The radar uses a fixed maximum range of 10 cm for plotted targets.
- The servo sweeps the ultrasonic sensor across the display and updates the radar background in real time.
- If the echo pulse is not received, the code treats the reading as invalid and displays `--`.

## License

This project is provided as-is for educational and hobby use.
