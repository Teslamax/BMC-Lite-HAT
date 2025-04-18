# BMC-Lite HAT Pin Mapping

## 🔌 XIAO RP2040 GPIO Assignments

| GPIO | Pin | Function            | Direction     | Connected To          | Notes                              |
|------|-----|---------------------|---------------|-----------------------|------------------------------------|
| 26   | 1   | `INT` from Expander | Input         | *MCP23017* `INTA` Pin | INT fires on button state changes  |
| 27   | 2   | Free (`ADC1`)       | —             | —                     | General-purpose                    |
| 28   | 3   | Free (`ADC2`)       | —             | —                     | ADC-capable input                  |
| 29   | 4   | Free (`ADC3`)       | —             | —                     | ADC-capable input                  |
| 6    | 5   | I²C `SDA`           | Bidirectional | OLED, GPIO Expander   | Addr `0x3C` (OLED), `0x20` (MCP)   |
| 7    | 6   | I²C `SCL`           | Bidirectional | OLED, GPIO Expander   | Shared I²C bus                     |
| 0    | 7   | UART `TX`           | XIAO → Pi     | Pi `GPIO15` (Pin 10)  | UART console                       |
| 1    | 8   | UART `RX`           | Pi → XIAO     | Pi `GPIO14` (Pin 8)   | UART console                       |
| 2    | 9   | Free (`SPI`-`SCK`)  | —             | —                     | —                                  |
| 4    | 10  | `HEARTBEAT`         | Input         | Pi `GPIO6` (Pin 31)   | `dtoverlay`-driven 1Hz pulse       |
| 3    | 11  | Free (`SPI`-`MOSI`) | —             | —                     | —                                  |
| —    | 12  | `3V3`               | —             | —                     | —                                  |
| —    | 13  | `GND`               | —             | —                     | —                                  |
| —    | 14  | `VBUS`              | —             | —                     | —                                  |

---

## 🔌 MCP23017 GPIO Expander (Prototyping Phase) (I²C addr `0x20`)

| Bank   | Pin| Function             | Direction | Connected To    | Notes                  |
|--------|----|----------------------|-----------|-----------------|------------------------|
| `GPB0` | 1  |  |  |  |  |
| `GPB1` | 2  |  |  |  |  |
| `GPB2` | 3  |  |  |  |  |
| `GPB3` | 4  |  |  |  |  |
| `GPB4` | 5  |  |  |  |  |
| `GPB5` | 6  |  |  |  |  |
| `GPB6` | 7  |  |  |  |  |
| `GPB7` | 8  |  |  |  |  |
| `VDD`  | 9  |  |  |  |  |
| `VSS`  | 10 |  |  |  |  |
| —      | 11 |  |  |  |  |
| `SCL`  | 12 | I²C `SCL` | Bidirectional  |  XIAO `SCL` | Shared I²C bus |
| `SDA`  | 13 | I²C `SDA` | Bidirectional  |  XIAO `SDA` | Shared I²C bus |
| —      | 14 |  |  |  |  |
| `A0`   | 15 |  |  |  |  |
| `A1`   | 16 |  |  |  |  |
| `A2`   | 17 |  |  |  |  |
| `RST`  | 18 |  |  |  |  |
| `INTB` | 19 |  |  |  |  |
| `INTA` | 20 | Interrupt | Output | XIAO `GPIO26` (Pin 1) |  |
| `GPA0` | 21 | Shutdown button   | Input     | Shutdown button | Debounced in software  |
| `GPA1` | 22 | Reboot button                | Input     | Reboot button   | Debounced in software  |
| `GPA2` | 23 | User button                | Input     | User button     | Debounced in software  |
| `GPA3` | 24 | Poweroff-Ready                | Input     |                 |                        |
| `GPA4` | 25 | Signal safe halt     | XIAO → Pi | Pi `GPIO17`     | Logic state  |
| `GPA5` | 26 | Signal safe reboot   | XIAO → Pi | Pi `GPIO27`     | Logic state  |
| `GPA6` | 27 | Signal user-defined  | XIAO → Pi | Pi `GPIO22`     | Logic state  |
| `GPA7` | 28 | Unused               | —         | —               | Reserved for expansion |
| `GPB*` | —  | Unused               | —         | —               | Reserved for expansion |

---

## 🔌 Raspberry Pi GPIO Assignments

| Pi GPIO | Pin | Function           | Direction   | Connected To          | Notes                           |
|---------|-----|--------------------|-------------|-----------------------|---------------------------------|
| 2       | 4   | 5V Power           | Output      | XIAO `VBUS` via diode | —                               |
| 14      | 8   | UART `TX`          | Output      | XIAO `RX` (`GPIO1`)   | Serial console                  |
| 15      | 10  | UART `RX`          | Input       | XIAO `TX` (`GPIO0`)   | Serial console                  |
| 17      | 11  | Shutdown Trigger   | Input       | Expander              | `dtoverlay=gpio-shutdown`       |
| 27      | 13  | Reboot Trigger     | Input       | Expander              | `dtoverlay=gpio-restart`        |
| 22      | 15  | User-defined Input | Input       | Expander              | Optional override or trigger    |
| 5       | 29  | Poweroff-Ready     | Output      | Expander              | High when safe to power off     |
| 6       | 31  | `HEARTBEAT`        | Output      | XIAO `GPIO10`         | dtoverlay: gpio-led trigger     |

---

## 🔋 Power & Ground

| Signal | Pi Pin(s) | XIAO Pin    | Notes                                              |
|--------|-----------|-------------|----------------------------------------------------|
| 5V     | 2 or 4    | 14 (`VBUS`) | Via Schottky, dual-source capable — switch isolation no longer required |
| `GND`  | 6, 9, etc | 13 (`GND`)  | Shared ground reference                            |

> ⚠️ **Note on `VBUS` and Power Safety:**
>
> The XIAO RP2040 includes an internal Schottky diode between its USB-C VBUS input and Pin 14 (`VBUS`). This prevents backfeed from external 5V sources (like the Pi) into the USB port. When combined with an external Schottky diode protecting the Pi's 5V rail, this configuration allows safe, simultaneous connection of both USB-C and Pi 5V power **without requiring a physical DEV/RUN switch**. The XIAO RP2040 does not include a VBAT or battery charging circuit, so Seeed Studio's general battery safety warnings do not apply here.

