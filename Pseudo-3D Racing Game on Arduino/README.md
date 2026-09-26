# Pseudo-3D Racing Game on Arduino

A retro-style 3D racing game implemented for Arduino microcontrollers with an SSD1306 OLED display.

## Overview

This game features a pseudo-3D racing experience where you control a player car and compete against an opponent. The game uses perspective rendering to create a sense of depth and speed on a small OLED screen.

## Features

- **Pseudo-3D Graphics**: Perspective-based road rendering that creates depth illusion
- **Dynamic Road**: Curved racing track that scrolls with perspective
- **Two-Player Competition**: Control player car while an AI opponent races
- **Nose Boost**: Random turbo boosts activate during the race
- **Animated Sprites**: Direction-aware car sprites (left, right, straight)
- **Race Start/Finish**: Visual flags and countdown timer before race begins
- **Win/Loss/Draw Results**: Clear race outcome display
## Demo
Link: https://youtu.be/6mhX6DsA06M
## Hardware Requirements

- Arduino or Arduino-compatible board (tested on ESP32)
- SSD1306 OLED Display (128x64 pixels, I2C connection)
- Joystick analog input (A0 for X-axis, A1 for Y-axis)
- Speaker/buzzer on pin 3 (for sound effects)

## Wiring

```
OLED Display (I2C):
- SDA -> Arduino SDA (A4 on Uno, 21 on Mega)
- SCL -> Arduino SCL (A5 on Uno, 20 on Mega)
- GND -> GND
- VCC -> 5V

Joystick:
- X-axis -> A0
- Y-axis -> A1
- GND -> GND
- +5V -> 5V

Speaker:
- Signal -> Pin 3
- GND -> GND
```

## Controls

- **Up (Joystick Y < 300)**: Accelerate forward (increase speed, move toward finish line)
- **Down (Joystick Y > 600)**: Decelerate backward (decrease speed, move away from finish)
- **Left (Joystick X < 300)**: Steer left
- **Right (Joystick X > 600)**: Steer right
- **Center**: Drive straight

## Game Mechanics

### Race Phases

1. **Start Screen**: Logo and "START" flag visible
2. **Countdown**: 3-2-1-GO with audio countdown beeps
3. **Racing**: Control your car and reach the finish line
4. **Race Complete**: Display winner, loser, or draw result with "STOP" flag

### Opponent Behavior

- The opponent AI follows a predetermined path with constant speed
- Random "nose boost" events trigger boosting for one car (40% chance every 2.5 seconds)
- Opponent can move up/down relative to road position based on boost status

### Scoring

- **Destination counter** decreases as you move closer to finish
- First car to reach 0 destination wins
- Draw occurs if both reach 0 at same time

## Code Structure

- **Game State Variables**: Speed, player/opponent positions, race flags, countdown timer
- **Bitmap Arrays**: Pre-rendered sprite graphics for cars and track elements
- **Main Functions**:
  - `drawRoad()`: Renders perspective road with gradient effect
  - `drawPlayer()`: Handles player input and draws player sprite
  - `drawOpp()`: Updates and draws opponent car
  - `drawCountdown()`: Manages pre-race countdown
  - `checkRaceEnd()`: Detects race completion
  - `endRace()`: Displays final results

## Installation

1. Install the Adafruit GFX and Adafruit SSD1306 libraries via Arduino IDE
2. Wire components according to the diagram above
3. Copy the code to Arduino IDE
4. Select correct board and COM port
5. Upload the sketch

## Dependencies

- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306 Library](https://github.com/adafruit/Adafruit_SSD1306)
- Arduino Wire library (built-in)
- Arduino Math library (built-in)

## Tips & Tricks

- The "nose" boost mode creates a special sprite state for the opponent
- Audio feedback (beeps) improves game feel during countdown
- Road curves are smooth thanks to sine wave calculations
- The perspective effect depends on precise coordinate scaling

## Customization

- Adjust `speed` variable for game difficulty
- Modify `NOSE_DURATION` (5000ms) to change boost length
- Change random chance in `loop()` to adjust boost frequency
- Edit sprite bitmaps to create custom car designs

## Performance

- Frame update rate: ~40ms per loop iteration
- Uses minimal RAM with PROGMEM for all bitmaps
- Compatible with standard Arduino boards

## Future Enhancements

- Multiple difficulty levels
- Score/lap tracking
- Sound effects library
- More track variations
- Collision detection

## License

Part of the Retro Games Arduino/ESP32 collection by MiniBuildsLabZA

## Troubleshooting

- **Display not showing**: Check I2C address (default 0x3C)
- **No input response**: Verify joystick calibration (should read 0-1023)
- **Slow performance**: Reduce bitmap sizes or increase delay timing
- **No sound**: Check speaker connection to pin 3
