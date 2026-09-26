# Arduino TFT Radar

A compact ultrasonic radar project built around an Arduino-compatible board, a servo motor, an HC-SR04 sensor, and a 1.8-inch ST7735 TFT display. The system scans the surroundings in a sweeping motion and displays the detected objects as colored points on a radar screen, giving the impression of a simple radar system.

## Overview

This project demonstrates how to combine:

- an ultrasonic distance sensor,
- a rotating servo motor,
- a TFT display,
- and a buzzer

into a small radar-style detector. The sensor measures distance while the servo rotates through a defined angle range, and each measurement is plotted on the screen as a fading trail to represent moving or nearby objects.

## Features

- 180° radar sweep using a servo motor
- Ultrasonic distance sensing using HC-SR04
- ST7735 TFT radar display
- Real-time object detection and tracking
- Fading red trail for detected targets
- Buzzer alert for nearby obstacles
- Distance readout in centimeters

## Hardware Required

- Arduino-compatible microcontroller (ESP32 or Arduino Uno compatible board)
- 1.8" ST7735 TFT display
- HC-SR04 ultrasonic sensor
- Servo motor (SG90 or similar)
- Active buzzer
- Breadboard and jumper wires
- 5V power source

## Pin Connections

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

## Required Libraries

Install the following libraries in the Arduino IDE:

- Adafruit_GFX
- Adafruit_ST7735
- Servo

You can install them from the Arduino Library Manager:

1. Open Arduino IDE
2. Go to Sketch > Include Library > Manage Libraries
3. Search for the library names above
4. Click Install

## Project Structure

- `Source Code` - contains the Arduino sketch for the radar project
- `README.md` - project documentation

## How It Works

1. The ultrasonic sensor sends a pulse and waits for the echo.
2. The measured echo time is converted into distance in centimeters.
3. The servo rotates the sensor across the scan range.
4. Each detected point is mapped into radar coordinates.
5. The TFT display draws the radar rings, sweep line, and object points.
6. If an object is close, the buzzer emits a short alert.

## Operation

1. Open the project sketch in the Arduino IDE.
2. Connect the hardware exactly as shown above.
3. Select the correct board and port.
4. Upload the code.
5. Power the system and watch the radar sweep.

## Notes

- The project uses a maximum detection range of 10 cm for plotted target points.
- If the sensor does not receive an echo, the code displays `--` instead of a distance value.
- The sweep animation is created by drawing a line from the center to the current angle, then clearing the previous line on the next update.
- The detected points slowly fade over time to simulate a radar trace.

## Troubleshooting

### No display output

- Check the TFT wiring and power supply
- Confirm the correct ST7735 library is installed
- Verify the board and port settings in Arduino IDE

### No distance readings

- Check the TRIG and ECHO connections
- Verify the ultrasonic sensor is powered correctly
- Ensure the sensor is not obstructed by wiring or noise

### Servo not moving

- Confirm the signal pin is connected to pin 6
- Ensure the servo gets adequate power
- Check that the servo is not overloaded or jammed

### Buzzer not beeping

- Verify pin 7 is correct
- Check the buzzer polarity
- Confirm the tone code is being triggered by a close object

## License

This project is provided for educational and hobby use. Feel free to modify and experiment with it.

## Example Use Cases

- Obstacle detection
- Simple proximity sensor demo
- Educational radar visualization
- Embedded systems learning project

## Future Improvements

- Add a more accurate distance calibration routine
- Add target tracking for multiple objects
- Add a mode switch for indoor/outdoor range tuning
- Implement a cleaner UI for minimum and maximum distance display
