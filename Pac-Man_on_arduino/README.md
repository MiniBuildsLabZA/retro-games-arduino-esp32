# Pac-Man on Arduino

![Pac-Man Cover](../covers/pacman.jpg)

A classic Pac-Man game implementation for Arduino on a small OLED display (128x64 pixels) using an Adafruit SSD1306 display and joystick input.

## Demo
Link: https://youtube.com/shorts/aVP9bUrWy6I?si=33jqzH-mrr6xtznP

## Overview

This sketch brings the iconic Pac-Man arcade game to life on embedded hardware, featuring player-controlled Pac-Man, AI-driven ghosts, collectible pellets, and a maze environment.

## Game Elements

- **Pac-Man**: Controlled via analog joystick (pins A0/A1), moves along predefined maze nodes with smooth animation across 4 directions
- **Ghosts**: 4 enemies that move randomly through the maze with intelligent pathfinding
- **Pellets**: Scattered collectibles throughout the map that increase your score when eaten
- **Maze**: Defined by 36 valid path nodes connected in a graph network, creating the playable area

## Features

### Controls
- **Joystick**: Move Pac-Man in 4 directions (UP, DOWN, LEFT, RIGHT)
- **Buffered Input**: Queue your next turn direction while moving
- **Instant Reversal**: Turn around on-edge for classic Pac-Man feel

### Gameplay
- **Collision Detection**: Contact with ghosts resets Pac-Man to starting position
- **Score System**: Increment score by eating pellets
- **Sprite Animation**: Multi-frame animated sprites for Pac-Man movement
- **Sound Effects**: Buzzer support (pin 2) for eat and death sounds

### Ghost AI
- Random pathfinding through valid maze nodes
- Avoids immediate reversal for natural movement
- 4 ghosts with different starting positions

## Hardware Requirements

- Arduino or compatible board (ESP32, etc.)
- **Display**: Adafruit SSD1306 OLED (128x64 pixels, I2C)
- **Input**: Analog joystick (connected to A0, A1)
- **Audio**: Buzzer (connected to pin 2)
- **I2C Communication**: SDA/SCL pins

## Pin Configuration

| Component | Pin |
|-----------|-----|
| Joystick X-axis | A1 |
| Joystick Y-axis | A0 |
| Buzzer | 2 |
| Display SDA | SDA |
| Display SCL | SCL |
| Display Address | 0x3C |

## Libraries Used

- `Adafruit_GFX.h` - Graphics library for drawing
- `Adafruit_SSD1306.h` - OLED display driver

## Setup & Installation

1. Install Adafruit GFX and SSD1306 libraries via Arduino IDE
2. Connect hardware according to pin configuration
3. Upload the sketch to your Arduino board
4. Power on and enjoy!

## Game Mechanics

- Movement is grid-based along predefined nodes
- Pac-Man moves 1 pixel per frame toward target node
- Pellets are detected within a 2-pixel collision radius
- Ghosts also move along the same node graph
- Starting position: Node (30, 8)

## Future Enhancements

- Implement smarter ghost AI (chase logic)
- Add power-up pellets for ghost vulnerability
- Multiple lives system
- Difficulty levels
- High score storage

---

Created as part of the DIY Arduino/ESP32 Projects collection for beginners learning embedded systems and game development.
