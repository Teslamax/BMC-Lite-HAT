# BMC-Lite-HAT System Wiring & Schematic (XIAO RP2040)

## 📦 Components

- 1x **Seeed Studio XIAO RP2040** (USB-C, onboard RGB LED — used)
- 1x **2×7 low-profile SMD female header** (for socketing XIAO)
- 3x Momentary Pushbuttons (`SHUTDOWN`,`REBOOT`,`USER1`)
- 1x 1N5819 Schottky Diode (Pi 5V → XIAO VIN, backfeed prevention)
- 1x 100 µF electrolytic capacitor (power smoothing)
- I²C expander (MCP23017 while breadboard prototyping)
- Jumper wires / headers / breadboard
- (Optional) I²C OLED
- **Bidirectional UART** between Pi and XIAO (GPIO14 TX and GPIO15 RX)

---

## 📦 Phase 2 Considerations (Planned BMC Features)

In future firmware and hardware expansions, BMC-Lite will evolve beyond passive monitoring to support **active Pi control** and additional diagnostics. The following features are targeted for Phase 2:

- **USB CDC** used exclusively for XIAO debug, control, and programming
- **Optional I²C OLED display** for UI output

---

## 🔌 Power Wiring

- **Pi 5V GPIO** → 1N5819 diode → XIAO VIN
- **XIAO GND** ↔ **Pi GND** (shared ground)
- 47-100 µF electrolytic capacitor across VIN and GND on XIAO

---

## 🔘 Button Wiring

### Button 1: Shutdown
- Between GPIO0 and GND
- Internal pull-up or 10kΩ to 3.3V
- 0.1 µF capacitor across GPIO0 and GND

### Button 2: Reboot
- Between GPIO1 and GND
- Same resistor and debounce setup as above

### Button 3: User-defined / gpio-key
- Between GPIO2 and GND
- Optional `gpio-key` or manual override/test

### Button 4: Optional second user button (analog read or I²C expander required)

---

## 🔁 Pi GPIO Overlay Config

In `/boot/config.txt`:

```ini
dtoverlay=gpio-shutdown,gpio_pin=22,active_low=1,gpio_pull=up
dtoverlay=gpio-poweroff,gpiopin=26,active_low=0
dtoverlay=gpio-restart,gpio_pin=27,active_low=1
dtoverlay=gpio-key,gpio=23,keycode=103,label="userbtn"
enable_uart=1
```

Also:
- GPIO14 = Pi TX → XIAO RX (UART debug stream)
- GPIO15 = XIAO TX → Pi RX (future BMC interaction)
- GPIO17 = Heartbeat pulse from systemd script

---

## 🧪 Debugging

USB-C is used on all versions of this project for:
- Power during programming
- CDC Serial debug logs
- Optional CLI interface over USB serial
- Firmware upload, runtime state control

---

## 💡 LED Status

### Silkscreen Info
This board should include the following on the silkscreen:
- **"BMC-Lite HAT"** as the board name (or stylized variant)
- **"Teslamax"** as the author or GitHub handle
- **Version identifier space** such as `Rev: ___` to be manually filled or incremented


- Onboard RGB LED (GPIO3/4/5)
- PWM-controlled with software blending and animation
- Fully used for state indication (booting, running, halted, crash, etc.)
- May be replaced in Phase 2 if GPIOs are needed

---

Let me know if you’d like this visualized in Fritzing or converted to KiCad for schematic + PCB layout!

