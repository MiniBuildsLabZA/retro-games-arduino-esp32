# XIAO RP2040 Console

[![XIAO RP2040 Console Cover](../covers/rp2040console.jpg)](https://youtube.com/shorts/zhR7zLngFXc?si=1gQ5dL1BJf7RmPIX)

A compact handheld retro-gaming console built around the Seeed XIAO RP2040. This project brings together multiple classic arcade-inspired games in one portable device, including Mario-style platformer gameplay, Sonic-inspired action, Pac-Man-inspired maze chasing, and other lightweight retro challenges.

## Demo

https://youtube.com/shorts/zhR7zLngFXc?si=1gQ5dL1BJf7RmPIX

## Features

- Seeed XIAO RP2040 Plus and Seeed XIAO Expansion Board -based handheld console design
- Built-in joystick controls for navigation and movement
- Multi-game arcade-style library in one firmware build
- Includes Mario-inspired, Sonic-inspired, Pac-Man-inspired, and other retro games
- Small-form portable design for a DIY gaming console
- OLED display output with fast, lightweight game logic
- Simple Arduino/PlatformIO-style firmware development flow

## Hardware

- Seeed XIAO RP2040 Plus
- Seeed XIAO Expansion Board
- 128x64 OLED display
- Joystick module
- Buttons for A/B/menu/navigation
- Optional buzzer or speaker
- Battery pack and power switch (optional for portable use)

## Buy the Hardware

Get your hardware ready on the links below and use discount coupon code: XFBTEEYS

- XIAO RP2040 Plus: https://www.seeedstudio.com/Seeed-Studio-XIAO-RP2040-Plus-p-6932.html?sensecap_affiliate=Rnxy6Vk&referring_service=link
- XIAO Expansion Board: https://www.seeedstudio.com/Seeeduino-XIAO-Expansion-board-p-4746.html?sensecap_affiliate=Rnxy6Vk&referring_service=link

## Wiring

Connect the display, joystick, buttons, and audio output to the XIAO RP2040 according to the pin definitions in `xiao_rp2040_console.ino`.

| Component | Connection |
|---|---|
| OLED SDA | XIAO D0 / SDA |
| OLED SCL | XIAO D1 / SCL |
| Joystick X | A0 |
| Joystick Y | A1 |
| Joystick Button | D2 |
| Buzzer / Speaker | A3 |
| GND | Common ground |
| 3V3 / 5V | Power as required by your display/module |

> The exact pin mapping may vary depending on your wiring and hardware layout. Confirm the assignments in the sketch before uploading.

## Source

Open [`xiao_rp2040_console.ino`](./xiao_rp2040_console.ino) in the Arduino IDE, select the correct board and port for your XIAO RP2040, install any required libraries, and upload the sketch.

Source code: https://github.com/MiniBuildsLabZA/retro-games-arduino-esp32

## Follow / Support

- X: https://x.com/MiniBuildsLabZA
- Instagram: https://instagram.com/MiniBuildsLabZA
- YouTube: https://www.youtube.com/@MiniBuildsLabZA
- TikTok: https://www.tiktok.com/@MiniBuildsLabZA

## Notes

This project is designed for a DIY portable handheld setup and is intended for educational and hobby experimentation. It demonstrates how to fit multiple simple retro-game mechanics onto a compact embedded board while keeping the build affordable, portable, and easy to customize.
