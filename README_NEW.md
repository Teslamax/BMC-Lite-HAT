# BMC-Lite HAT

A minimalist Raspberry Pi companion board that provides **safe power control**, **status indication**, and **serial console monitoring** for headless systems like the Pi Zero and Pi Zero 2.

BMC-Lite behaves like a simplified BMC (Baseboard Management Controller), using a microcontroller (e.g. XIAO RP2040) to coordinate shutdown, reboot, user-defined input, and status feedback — all with minimal Pi-side dependencies.

---

## ✨ Key Features

- 🧠 Clean shutdown, reboot, and optional user-defined buttons
- 🌈 RGB LED for system status (boot, running, halted, panic, etc.)
- 🔁 Bidirectional UART between Pi and MCU for serial console parsing
- 🫀 Heartbeat monitoring via `gpio-led` overlay on Pi GPIO6
- 🔌 Power-safe operation using Schottky diodes (no USB backfeed)
- 📟 Optional I²C OLED display (address `0x3C`)
- 📦 Compact Pi Zero-compatible form factor

---

## 🔩 Hardware Overview

- Microcontroller: **Seeed XIAO RP2040**
- Communication:
  - **UART** (Pi `GPIO14/15`) for console output / command reception
  - **GPIO overlays** for poweroff, shutdown, reboot
  - **I²C** (shared bus for OLED + optional MCP23017 expander)
- RGB LED: onboard XIAO NeoPixel used for state indication
- Buttons: physical momentary buttons (shutdown, reboot, user-defined)
- Power: 5V input from Pi via Schottky diode OR USB-C (dev mode)

> See [`OVERVIEW.md`](OVERVIEW.md) for detailed power modes and deployment strategy.

---

## ⚙️ Raspberry Pi Configuration

Add the following to your `/boot/config.txt`:

```ini
# Enable UART (optional but recommended)
enable_uart=1

# GPIO overlays
dtoverlay=gpio-shutdown,gpio_pin=22,active_low=1,gpio_pull=up
dtoverlay=gpio-poweroff,gpiopin=26,active_low=0
dtoverlay=gpio-restart,gpio_pin=27,active_low=1

# Heartbeat overlay (blinks GPIO6 at ~1Hz)
dtoverlay=gpio-led,gpio=6,trigger=heartbeat
```

> Note: Overlay pins can be adjusted if your board is wired differently — see [`docs/PINOUT.md`](docs/PINOUT.md).

---

## 🌈 RGB LED Status

| State            | Color     | Pattern      | Meaning                          |
|------------------|-----------|--------------|----------------------------------|
| Off              | ⚫ Off     | Off          | No Pi power                      |
| Booting          | 🟠 Orange  | Breathing    | Pi serial console detected       |
| Running          | 🟢 Green   | Solid        | Heartbeat detected               |
| Shutting Down    | 🟡 Yellow  | Slow Blink   | Shutdown in progress             |
| Halted           | 🔴 Red     | Solid        | GPIO26 HIGH — safe to power off  |
| Crash / Panic    | 🟣 Magenta | Fast Blink   | Kernel panic (detected via UART) |
| Unresponsive     | 🟤 Amber   | 2s Blink     | Heartbeat timeout                |

> A copy of this table also exists in the docs, alongside state machine definitions and implementation.

---

## 🧭 Pin Mapping

See [`docs/PINOUT.md`](docs/PINOUT.md) for the authoritative pin allocation between:

- Raspberry Pi GPIO
- XIAO RP2040
- Optional MCP23017 I/O Expander

---

## 📄 License

MIT or CC-BY 4.0 — TBD

---

## 💬 Credits

Designed by [You], with architectural support from ChatGPT.  
Inspired by system BMCs, IPMI, `systemd`, and the belief that small devices deserve great UX too.
