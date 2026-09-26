# Flappy Bird on Arduino

A fun implementation of the classic Flappy Bird game on an Arduino microcontroller with an SSD1306 OLED display.

## 📋 Overview

This project recreates the popular Flappy Bird game for embedded systems. The game features:
- **128x64 OLED Display** for gameplay
- **Button Control** for bird flapping
- **Scrolling Background** with parallax effect
- **Dynamic Obstacles** (pipes) with variable heights and oscillating movement
- **Score Tracking** with audio feedback
- **Game Over Detection** with collision handling
- **Multiple Sprite Animations** for bird movement states
## Demo
Link: https://youtube.com/shorts/XYnEovBdsMg?feature=share
## 🛠️ Hardware Requirements

- **Arduino Board** (Arduino Uno, Nano, or compatible)
- **SSD1306 OLED Display** (128x64, I2C interface)
- **Push Button** (tactile switch)
- **Passive Buzzer** (optional, for sound effects)
- **Resistors** (as needed for debouncing and buzzer)
- **Jumper Wires**
- **USB Cable** for programming and power

### Pin Configuration

```cpp
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define BUZZER_PIN 3       // Passive buzzer output
#define BUTTON 4           // Button input (active LOW)
```

## 📦 Software Dependencies

You'll need to install these libraries via the Arduino IDE Library Manager:

- **Adafruit GFX Library** - Graphics library for display
- **Adafruit SSD1306** - OLED display driver

### Installation Steps

1. Open Arduino IDE
2. Go to **Sketch** → **Include Library** → **Manage Libraries**
3. Search for "Adafruit GFX" and install
4. Search for "Adafruit SSD1306" and install
5. Connect your Arduino and upload the sketch

## 🎮 How to Play

1. **Start the Game**: Upload the code to your Arduino
2. **Flap to Rise**: Press the button to make the bird flap and rise
3. **Release to Fall**: Release the button to let the bird fall
4. **Avoid Pipes**: Navigate through the gaps between pipes
5. **Score Points**: Each pipe you successfully pass increases your score
6. **Game Over**: Colliding with pipes or screen edges ends the game
7. **Reset**: Press the button to restart after Game Over

## 🎯 Game Features

### Bird Movement
- **Flapping Sprite**: 3-frame animation when button is held
- **Falling Sprite**: 3-frame animation when button is released
- **Grace Period**: 300ms delay after button release before falling sprite activates (improves responsiveness)
- **Physics**: 4-unit rise per frame when flapping, 2-unit fall per frame otherwise

### Pipe System
- **Multiple Pipes**: 4 pipes managed simultaneously for smooth gameplay
- **Variable Gap Heights**: Gaps range from 22-34 pixels (adjustable difficulty)
- **Oscillating Pipes**: 60% chance each pipe oscillates vertically (adds challenge)
- **Dynamic Spacing**: Pipes spawn with random spacing (34-55 pixels between them)
- **Collision Detection**: AABB overlap testing for precise hit detection

### Audio & Feedback
- **Score Beep**: 1000Hz tone for 100ms when passing a pipe
- **Score Display**: Current score shown in top-right corner

### Visual Elements
- **Scrolling Background**: Parallax floor effect with continuous scrolling
- **Game Logo**: Flappy Bird logo displayed in corner
- **Game Over Screen**: Static game state displayed with "Game Over" text

## 📝 Code Structure

### Main Functions

| Function | Purpose |
|----------|---------|
| `setup()` | Initialize display and button pin |
| `loop()` | Main game loop |
| `drawFlappBackground()` | Render scrolling background |
| `drawPipes()` | Update and render all pipes |
| `moveBird()` | Handle bird physics and animation |
| `checkCollision()` | Detect collisions and scoring |
| `drawScore()` | Display current score |
| `gameOver()` | Display game over screen |
| `resetGame()` | Reset all game variables |

### Key Variables

```cpp
float birdX, birdY;           // Bird position
int pipeX[NUM_PIPES];         // Pipe horizontal positions
int pipeGapY[NUM_PIPES];      // Pipe gap vertical position
int pipeGapH[NUM_PIPES];      // Pipe gap height
bool pipeOscillate[NUM_PIPES]; // Whether pipe oscillates
int score;                     // Current score
bool isgameOver;              // Game state flag
```

## ⚙️ Customization

### Difficulty Adjustment

```cpp
#define GAP_HEIGHT_MIN 22   // Smaller = harder
#define GAP_HEIGHT_MAX 34   // Larger = easier

#define PIPE_SPACING_MIN 34 // Tighter = harder
#define PIPE_SPACING_MAX 55 // Looser = easier
```

### Game Physics

```cpp
const float pipeOscSpeed = 0.5;  // Vertical oscillation speed
const unsigned long fallDelay = 300; // Grace period after release (ms)
const float frameSpeed = 1.5;    // Animation frame rate
```

### Bird Control

```cpp
birdY -= 4; // Rise amount per frame when flapping
birdY += 2; // Fall amount per frame when not flapping
```

## 🐛 Troubleshooting

| Issue | Solution |
|-------|----------|
| Display not showing | Check I2C address (0x3C default), verify wiring |
| Button not responsive | Check button pin connection, ensure pullup enabled |
| No sound | Verify buzzer is connected to pin 3, check polarity |
| Unstable game | Check power supply, ensure steady voltage to Arduino |
| Sprites flickering | Verify display refresh rate, reduce animation frame speed |

## 📊 Game Specifications

| Parameter | Value |
|-----------|-------|
| Screen Resolution | 128x64 pixels |
| Display Type | SSD1306 OLED (I2C) |
| Number of Pipes | 4 (simultaneous) |
| Bird Size | 15x10 pixels |
| Pipe Width | 13 pixels |
| Pipe Segment Height | 42 pixels |
| Gap Height Range | 22-34 pixels |
| Pipe Speed | 2 pixels/frame |
| Background Speed | 2 pixels/frame |
| Frame Rate | ~60 FPS (display limited) |

## 🎨 Graphics

The project includes pre-rendered bitmap graphics stored in PROGMEM:

- **Background**: Two 128x58 pixel backgrounds (scrolling effect)
- **Pipes**: Top and bottom 13x42 pixel pipe segments
- **Bird**: 3 frames each for flapping and falling states (14-17 pixels wide, 11-12 pixels tall)
- **Floor**: 128x7 pixel floor pattern with brick texture
- **Logo**: 21x17 pixel Flappy Bird logo

## 📖 Credits

- **Game Concept**: Based on the original Flappy Bird by Dong Nguyen
- **Libraries**: Adafruit GFX and Adafruit SSD1306
- **Display**: SSD1306 OLED Display
- **Microcontroller**: Arduino

## 📄 License

This project is provided as-is for educational purposes.

## 🔧 Future Enhancements

Potential improvements for this project:
- [ ] EEPROM high score storage
- [ ] Multiple difficulty levels
- [ ] Different bird/pipe themes
- [ ] Sound effects library
- [ ] Speed progression (pipes speed up with score)
- [ ] Day/night mode for display
- [ ] Accelerometer-based tilt control (with ESP32)
- [ ] WiFi high score leaderboard (with ESP32)

## 🤝 Contributing

Feel free to fork this project and submit improvements! Suggestions for enhancements are welcome.

---

**Happy Flapping! 🐦**
