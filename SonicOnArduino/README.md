# SonicOnArduino

![Sonic Cover](../covers/sonic.jpg)

A Sonic-style side-scrolling game for Arduino/ESP32 using an SSD1306 128x64 OLED. It includes sprite animations, ring collection, enemies, trees, a boss, scoring, and buzzer sounds.

## Demo

https://youtube.com/shorts/8RqrcE4Sohk?feature=share

## Hardware

- Arduino Uno/Nano or ESP32
- SSD1306 128x64 I2C OLED
- Buzzer on pin 3
- Button on pin 4
- Optional joystick or potentiometers on A0/A1

Install Adafruit GFX and Adafruit SSD1306, inspect `SourceCode`, adjust pin definitions if necessary, and compile and upload the sketch.

Large monochrome bitmap arrays are stored in PROGMEM to reduce RAM usage. The project is an educational demo with configurable physics and timing.
