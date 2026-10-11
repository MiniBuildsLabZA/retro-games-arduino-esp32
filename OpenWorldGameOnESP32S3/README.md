# DIY Console Open World Game on ESP32-S3

[![DIY Console Cover](../covers/diyXiaoConsole.jpg)](https://youtube.com/shorts/Ot62HYaMtuk?si=xbsjx3Xgc9jipoXL)

A compact open-world action game for the ESP32-S3 with a DIY handheld console layout, a TFT display, joystick controls, button-based combat, enemy AI, and built-in sound effects.

## Demo

https://youtube.com/shorts/Ot62HYaMtuk?si=xbsjx3Xgc9jipoXL

## Features

- Open-world exploration and scrolling map
- Sword combat with attack combos and hit detection
- Enemy wave logic with multiple enemy types
- Shooter-style ranged enemies and projectile combat
- Health bars, HUD elements, and game-over state
- ESP32-S3 audio output using I2S
- Lightweight sprite rendering for a small TFT display

## Hardware

- ESP32-S3 development board
- ST7735 160x128 TFT display
- Analog joystick
- Buttons for action / sword input
- I2S speaker or buzzer
- 3.3V power source and common ground

## Wiring

![DIY Console Wiring Diagram](./diy_xiao_console_wiring_diagram.jpg)

| Component | Connection |
|---|---|
| TFT CS | D1 |
| TFT RST | D2 |
| TFT DC | D3 |
| I2S BCLK | D6 |
| I2S LRC | D7 |
| I2S DIN | D9 |
| Joystick X | D0 |
| Joystick Y | D4 |
| Action button | D5 |

Connect the display, audio output, joystick, and buttons to the board using the wiring diagram above. Ensure the power rails and ground are shared correctly before uploading.

## Controls

- Move: joystick
- Attack / sword: button press
- Combo follow-up: quick repeated button presses
- Restart after game over: hold the action button after defeat

## Required Libraries

Install the following libraries in the Arduino IDE via **Sketch → Include Library → Manage Libraries**:

- **Adafruit ST7735 and ST7789 Library** - For TFT display control
- **Adafruit GFX Library** - Graphics library dependency for display rendering
- **Wire** - Built-in library for I2C communication (if needed)
- **SPI** - Built-in library for SPI communication

**Installation steps:**
1. Open Arduino IDE
2. Go to Sketch → Include Library → Manage Libraries
3. Search for and install each library listed above
4. Restart Arduino IDE after installation

## Source

Open [`cow_boy.ino`](./cow_boy.ino) in the Arduino IDE or PlatformIO project environment. Include the required asset files in the same folder, select your ESP32-S3 board and port, then upload.

## Notes

The project uses sprite data and generated sound effect tables embedded in the source project files. Adjust pin mappings to suit your DIY console layout if necessary.

---

## 📂 Source Code (Open Source)

https://github.com/MiniBuildsLabZA/retro-games-arduino-esp32

## 🛒 Get the Hardware

**Get the XIAO ESP32-S3:**
https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html?sensecap_affiliate=Rnxy6Vk&referring_service=link

🏷️ **Discount Code:** `XFBTEEYS`

*(Affiliate link: costs you nothing extra and supports the channel)*

## 📱 Follow MiniBuildsLabZA

- Instagram: https://instagram.com/minibuildslabza
- TikTok: https://www.tiktok.com/@minibuildslabza

## License

This project is open source. Please refer to the LICENSE file in the repository for details.

## 💬 Questions?

Drop your questions in the comments section below or open an issue on GitHub!
