# SonicOnArduino

This folder contains the SonicOnArduino example — a small Sonic-style side-scrolling game for Arduino / ESP32 using an SSD1306 128x64 OLED. The project's primary source is a single C++ source file (containing the game logic and sprite bitmaps) located at:

SonicOnArduino/SourceCode

Summary
- Monochrome sprites stored in PROGMEM for low RAM usage
- Side-scrolling level with rings, simple enemies (meat & motor bugs), trees and a boss
- Player movement, jumping, ring collection, basic scoring and simple buzzer sounds
Demo
-Link: https://youtube.com/shorts/8RqrcE4Sohk?feature=share
Hardware
- MCU: Arduino Uno / Nano / ESP32 (adjust pins for your board)
- SSD1306 I2C 128x64 OLED display
- Buzzer on a PWM-capable digital pin
- Button for input (and optional analog joystick)

Default wiring used in the code
- SSD1306: I2C (Wire). AVR: SDA=A4, SCL=A5. ESP32: SDA=21, SCL=22.
- Buzzer: digital pin 3 (BUZZER_PIN)
- Button: digital pin 4 (BUTTON)
- Joystick/potentiometers: A0 (X), A1 (Y)

Software / Libraries
- Adafruit GFX
- Adafruit SSD1306

The main file includes these headers and constructs an Adafruit_SSD1306 instance. If your display requires a reset pin or a different constructor signature, update the constructor.

How to run
1. Open this repository in Arduino IDE or PlatformIO.
2. Install the Adafruit GFX and Adafruit SSD1306 libraries.
3. Inspect SonicOnArduino/SourceCode and adjust pin definitions if needed.
4. Compile and upload to your board.

Notes
- The sprite bitmaps are large arrays kept in PROGMEM to save RAM — avoid editing them unless you understand the format.
- The code is intended as an educational demo; physics and timings are simple and configurable.

License
No license is provided in the repository. If you want to reuse or distribute this code, consider adding a LICENSE file (for example, MIT).

Contributing
If you'd like to improve the project (smaller sprites, bug fixes, enhanced controls), please fork and submit a PR with details of your changes.
