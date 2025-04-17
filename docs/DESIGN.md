# BMC-Lite HAT – Design Overview

**BMC-Lite HAT** is a compact, low-cost control and status interface board for headless Raspberry Pi systems.  
It provides **safe shutdown and reboot control**, **user input**, **status indication**, and **power protection**, while enabling easy prototyping and future expandability.

---

## 🎯 Project Goals

- Allow clean shutdown and reboot of headless Raspberry Pi devices
- Support up to 3 debounced physical buttons (shutdown, reboot, user)
- Monitor Pi health via UART and a heartbeat GPIO
- Provide visual feedback using the XIAO's onboard RGB LED and optional I²C OLED
- Maintain power separation and protection between the Pi and USB
- Fit entirely on a solderless breadboard for early prototyping

---

## 🧱 Hardware Overview

### MCU: **Seeed XIAO RP2040**

- Handles button input with debouncing
- Sends shutdown and reboot signals to the Pi
- Receives Pi "ready for poweroff" and "heartbeat" signals
- Optionally monitors UART output from Pi
- Drives an optional I²C OLED
- Uses all **12 GPIOs** on the XIAO

### Raspberry Pi

- Uses `dtoverlay`-based GPIO triggers
- Powered independently (no USB power sharing)
- Communicates with XIAO via GPIO and UART
- Provides power to XIAO (with diode protection)

---

## ⚡ Dual-Power Protection: Discrete Schottky Diodes

### Purpose:
Prevent power contention between **USB (VBUS)** and **Pi 3.3V rail** by OR-ing both into a common `V_SYS` rail.

### Materials:
- 1x discrete Schottky diodes (e.g., 1N5817, BAT85) (one is already protecting the USB-C 5v source on the XIAO-RP2040)
- 1x 10–47µF ceramic capacitor (0805/1206, X5R or X7R)

### Diagram:

```text
Pi 3.3V ───┬────|<|──┐
           │         │
           │         ├───► V_SYS ──► XIAO 3.3V (Pin 13)
USB 3.3V ──┴────|<|──┘
                 │
              [Capacitor]
                 │
                GND
