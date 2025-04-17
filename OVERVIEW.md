# BMC-Lite HAT – System Overview

BMC-Lite HAT is a compact Raspberry Pi companion board designed to provide basic BMC-like functionality such as controlled shutdown, reboot, user input, and visual feedback for headless systems.

Built around the Seeed XIAO RP2040, it integrates clean power handling, GPIO signaling, and serial monitoring in a Pi Zero-sized footprint.

## ✅ Key Capabilities

- Clean shutdown, reboot, and user interaction via physical buttons
- Visual feedback through onboard RGB LED (NeoPixel)
- Safe power sharing between Pi and USB using Schottky diodes
- DEV vs RUN mode switch for debugging vs deployment
- UART-based serial monitoring
- Optional I²C OLED and GPIO expander (MCP23017)

## 🔋 Power Notes

The XIAO RP2040 can be safely powered from either:

- The Raspberry Pi's 5V rail via an **external Schottky diode**
- Its onboard USB-C connection (protected by a built-in Schottky diode)

This allows safe simultaneous connection of both USB and Pi power without a physical DEV/RUN switch.
## 🔋 Power Architecture

- `V_SYS` rail is shared between Pi 5V (via diode) and USB-C
- XIAO VBUS (Pin 14) connects to V_SYS in RUN mode
- Schottky diodes prevent reverse current into Pi or USB host
## 🫀 Heartbeat Monitoring

To indicate the Pi is alive:

Add to `/boot/config.txt`:
```ini
dtoverlay=gpio-led,gpio=6,trigger=heartbeat
```

- Uses **GPIO6 (Pin 31)** to pulse at ~1Hz
- Connect to **XIAO GPIO10** or MCP23017 GPIO for monitoring
## 📦 Physical & Logical Summary

- Board form factor: pHAT (fits Pi Zero footprint)
- GPIO header: stacking or through-hole
- Optional 4-pin OLED header (`0x3C`)
- Optional MCP23017 I/O expander (`0x20`)

For detailed wiring, see [`docs/PINOUT.md`](docs/PINOUT.md)
