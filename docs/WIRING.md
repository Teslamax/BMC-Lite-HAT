# BMC-Lite HAT – Breadboard Wiring Guide

This guide describes the practical breadboard and prototyping wiring for the BMC-Lite HAT system using the Seeed XIAO RP2040 and a Raspberry Pi.

---

## 🧰 Components

- 1× **Seeed Studio XIAO RP2040** (with onboard RGB NeoPixel)
- 3× Momentary pushbuttons: `SHUTDOWN`, `REBOOT`, `USER1`
- 1× **1N5819** (or similar Schottky diode) for Pi 5V → XIAO VIN
- 1× **100 µF electrolytic capacitor** (power smoothing)
- Jumper wires, breadboard, headers
- *(Optional)* I²C OLED (addr `0x3C`)
- *(Optional)* MCP23017 GPIO expander (addr `0x20`)

---

## 🔌 Power Wiring

- **Pi 5V GPIO** → 1N5819 diode → **XIAO VIN (Pin 14)**
- **XIAO GND** ↔ **Pi GND** (any shared ground pin)
- Place 47–100 µF capacitor across **VIN and GND** on the XIAO

> USB-C can be connected at the same time for programming/debug — both USB and Pi 5V lines are protected via Schottky diodes.

---

## 🔘 Button Wiring (Direct to XIAO GPIOs)

Use internal pull-ups or 10kΩ external pull-ups to 3.3V.  
Place a 0.1 µF capacitor across each button for basic hardware debounce.

| Button   | XIAO GPIO | Pin  |
|----------|-----------|-------|
| Shutdown | GPIO0     | 7     |
| Reboot   | GPIO1     | 8     |
| User     | GPIO2     | 9     |

---

## 🔁 UART Wiring

- **Pi TX (GPIO14, Pin 8)** → **XIAO RX (GPIO1, Pin 8)**
- **XIAO TX (GPIO0, Pin 7)** → **Pi RX (GPIO15, Pin 10)**

---

## 🫀 Heartbeat Wiring

- Pi GPIO6 (Pin 31) is configured with `dtoverlay=gpio-led`
- Wire this to XIAO GPIO4 (Pin 10)

---

## ⚙️ Pi Configuration Snippet

In `/boot/config.txt`:

```ini
enable_uart=1

dtoverlay=gpio-shutdown,gpio_pin=22,active_low=1,gpio_pull=up
dtoverlay=gpio-poweroff,gpiopin=26,active_low=0
dtoverlay=gpio-restart,gpio_pin=27,active_low=1
dtoverlay=gpio-led,gpio=6,trigger=heartbeat
```

---

## 💡 RGB LED Behavior

The onboard NeoPixel is used for state feedback.

| State            | Color     | Pattern      | Meaning                          |
|------------------|-----------|--------------|----------------------------------|
| Booting          | 🟠 Orange  | Breathing    | Serial output detected           |
| Running          | 🟢 Green   | Solid        | Heartbeat received               |
| Shutting Down    | 🟡 Yellow  | Slow Blink   | Shutdown in progress             |
| Halted           | 🔴 Red     | Solid        | Poweroff signal detected         |
| Crash / Panic    | 🟣 Magenta | Fast Blink   | Kernel panic via UART            |
| Unresponsive     | 🟤 Amber   | 2s Blink     | Heartbeat lost                   |

---

## 📌 Notes

- For more advanced I/O (buttons via expander), see [`docs/PINOUT.md`](PINOUT.md)
- For board-level wiring or KiCad files, see the main project files or future releases
