# LED Status Scheme

This document describes the color codes and behavior for the RGB LED on the BMC-lite HAT used to indicate Raspberry Pi system states.

## 🌈 LED Status Scheme

| State            | Color       | Behavior     | Meaning                          |
|------------------|-------------|--------------|----------------------------------|
| Off              | ⚫ Off       | Off          | No Pi power                      |
| Booting          | 🟠 Orange    | Breathing    | Parsing serial boot logs         |
| Running          | 🟢 Green     | Solid        | Heartbeat OK                     |
| Shutting Down    | 🟡 Yellow    | Slow Blink   | Shutdown in progress             |
| Halted           | 🔴 Red       | Solid        | GPIO26 high: safe to power off   |
| Crash / Panic    | 🟣 Magenta   | Fast Blink   | Kernel panic, log detected       |
| Unresponsive     | 🟤 Amber     | 2s Blink     | Heartbeat timeout                |

## Notes

- These colors match common status metaphors (e.g., red = stop, green = go).
- Color style and timing are configurable in firmware.
- Breathing, blinking, and pulsing can indicate different transitional states.
