# BMC-Lite HAT – Power Architecture & Safety

This document describes how power flows through the BMC-Lite HAT system and explains the use of diodes to safely support both Raspberry Pi and USB power sources.

---

## 🔋 Overview

The system is designed to allow the Raspberry Pi and USB-C to be connected at the same time without risk of damaging backfeed.

### Power Sources:
- **USB-C** → XIAO RP2040 (internal Schottky protection)
- **Raspberry Pi 5V GPIO (Pin 2 or 4)** → external Schottky diode → XIAO VIN

Both sources feed into a common `V_SYS` rail safely.

---

## 🔌 Diode-Based Protection

### XIAO RP2040 (Built-in):
- Includes a **Schottky diode** from USB-C to VBUS (Pin 14)
- Prevents backfeed from Pi into USB host

### Raspberry Pi to XIAO (External):
- A **1N5819** or similar diode is placed between the Pi’s 5V rail and the XIAO’s VBUS
- Prevents USB power from backfeeding into the Pi

---

## 🔄 Power Flow Diagram (Textual)

```
[Pi 5V GPIO] --|>|--+
               D1   |
                   [ V_SYS Rail ] --- XIAO VBUS (Pin 14)
[USB-C] --------|>|--+
               (internal)
```

> **D1**: External Schottky diode (e.g., 1N5817, SS14, BAT54)

---

## ✅ Safe Use Cases

| Power Scenario             | Safe? | Notes                                        |
|----------------------------|-------|----------------------------------------------|
| Only Pi connected (no USB) | ✅    | Pi powers XIAO through D1                    |
| Only USB connected         | ✅    | USB powers XIAO via internal diode           |
| Both connected             | ✅    | Each input is isolated; no current conflict  |

---

## ⚠️ Best Practices

- Use **low forward-voltage Schottky diodes** for efficient power transfer
- Place a **47–100 µF capacitor** near VIN and GND to smooth transitions
- No need for a physical switch — diode logic handles source selection

---

## 🧪 Development Notes

- If powering from USB only, the Pi can be safely unplugged or powered off
- For final deployment, USB can be used for data/firmware only, not power

---

## 📚 See Also

- [`WIRING.md`](WIRING.md) for breadboard wiring
- [`PINOUT.md`](PINOUT.md) for power pin locations
