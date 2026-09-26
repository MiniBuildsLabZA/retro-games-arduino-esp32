# Racing Game on ESP32

A compact racing game for ESP32 and SSD1306 OLED displays. The project features a top-down race track, multiple AI cars, a finish screen, and simple button-based controls.

## Overview

This game turns a small OLED display into a miniature arcade race. The player controls a car around a pre-defined track and races against several opponents to determine the final finishing position.

## Features

- Top-down race track drawing
- Multiple AI-controlled cars
- Player position tracking
- Starting screen and finish screen overlays
- Button-based directional controls
- Lightweight game loop suitable for ESP32
## Demo
Link: https://youtube.com/shorts/Xz7EnjQXIHw?feature=share
## Hardware Requirements

- ESP32 development board
- 128x64 SSD1306 OLED display
- 4 push buttons
- Breadboard and jumper wires

## Wiring Diagram

```text
OLED (I2C)
----------
SDA -> GPIO 21
SCL -> GPIO 22
VCC -> 3.3V
GND -> GND

Buttons
-------
UP    -> GPIO 32
DOWN  -> GPIO 33
LEFT  -> GPIO 25
RIGHT -> GPIO 26

Connection style:
- Each button should be wired to a GPIO with pull-up enabled
- Pressing a button connects the GPIO to GND
```

## Controls

Use the four directional buttons to steer the car:

- Up: move car upward
- Down: move car downward
- Left: move car left
- Right: move car right

A press on any direction button starts the race from the title screen.

## Gameplay

1. The game opens on a start screen showing the race cover art.
2. Press any direction button to begin.
3. The player car starts at the beginning of the track.
4. AI cars move automatically along predefined route points.
5. The race ends when all cars have reached the finish line.
6. A result screen shows the player's final finishing position.

## Track System

The game uses a set of coordinate arrays to define the road path. The AI cars follow those points and smoothly move toward the next track segment. The player is free to navigate within the playing area while the cars update each frame.

## Libraries

This project uses:

- Adafruit_GFX
- Adafruit_SSD1306
- Wire

## Installation

1. Install the Arduino IDE or PlatformIO.
2. Install the necessary libraries.
3. Open the source file in this folder.
4. Select the ESP32 board and correct serial port.
5. Upload the project to the board.

## Notes

- The display uses the SSD1306 I2C address `0x3C`.
- The project stores bitmap graphics in program memory for efficient display updates.
- The main loop updates gameplay and rendering at a controlled pace for ESP32 stability.

## Possible Improvements

- Add lap timing and countdown
- Add sound effects and music
- Add a menu system and difficulty options
- Add collisions and boost pickups
- Add a smarter AI opponent behavior system

## License

This project is part of the Retro Games Arduino/ESP32 collection by MiniBuildsLabZA.

## Author

MiniBuildsLabZA
