# BMC-Lite HAT Pin Mapping

## 🔌 XIAO RP2040 GPIO Assignments

| GPIO | Pin | Function            | Direction     | Connected To         | Notes                              |
|------|-----|---------------------|---------------|----------------------|------------------------------------|
| 26   | 1   | `INT` from Expander | Input         | MCP23017 `INT` Pin   | INT fires on button state changes  |
| 27   | 2   | Free (`ADC1`)       | —             | —                    | General-purpose                    |
| 28   | 3   | Free (`ADC2`)       | —             | —                    | ADC-capable input                  |
| 29   | 4   | Free (`ADC3`)       | —             | —                    | ADC-capable input                  |
| 6    | 5   | I²C `SDA`           | Bidirectional | OLED, GPIO Expander  | Addr `0x3C` (OLED), `0x20` (MCP)   |
| 7    | 6   | I²C `SCL`           | Bidirectional | OLED, GPIO Expander  | Shared I²C bus                     |
| 0    | 7   | UART `TX`           | XIAO → Pi     | Pi `GPIO15` (Pin 10) | UART console                       |
| 1    | 8   | UART `RX`           | Pi → XIAO     | Pi `GPIO14` (Pin 8)  | UART console                       |
| 2    | 9   | Free (`SPI`-`SCK`)  | —             | —                    | —                                  |
| 4    | 10  | `HEARTBEAT`         | Input         | Pi `GPIO6` (Pin 31)  | `dtoverlay`-driven 1Hz pulse       |
| 3    | 11  | Free (`SPI`-`MOSI`) | —             | —                    | —                                  |
| —    | 12  | `3V3`               | —             | —                    | —                                  |
| —    | 13  | `GND`               | —             | —                    | —                                  |
| —    | 14  | `VBUS`              | —             | —                    | —                                  |

---

## 🔌 MCP23017 GPIO Expander (Prototyping Phase) (I²C addr `0x20`)

| Bank  | Pin             | Function             | Direction | Connected To    | Notes                  |
|-------|-----------------|----------------------|-----------|-----------------|------------------------|
| GPA0  | Shutdown button | Input                | Input     | Shutdown button | Debounced in software  |
| GPA1  | Reboot button   | Input                | Input     | Reboot button   | Debounced in software  |
| GPA2  | User button     | Input                | Input     | User button     | Debounced in software  |
| GPA6  | Poweroff-Ready  | Input                | Input     |                 |                        |
| GPA4  | Shutdown        | Signal safe halt     | XIAO → Pi | Pi GPIO17       | Debounced logic state  |
| GPA5  | Reboot          | Signal safe reboot   | XIAO → Pi | Pi GPIO27       | Debounced logic state  |
| GPA6  | User            | Signal user-defined  | XIAO → Pi | Pi GPIO22       | Debounced logic state  |
| GPA7  | —               | Unused               | —         | —               | Reserved for expansion |
| GPB*  | —               | Unused               | —         | —               | Reserved for expansion |

---

## 🔌 Raspberry Pi GPIO Assignments

| Pi GPIO | Pin | Function           | Direction   | Connected To        | Notes                           |
|---------|-----|--------------------|-------------|---------------------|---------------------------------|
| 2       | 4   | 5V Power           | Output      | XIAO VBUS via diode | —                               |
| 5       | 29  | Poweroff-Ready     | Output      | Expander            | High when safe to power off     |
| 6       | 31  | Heartbeat          | Output      | XIAO GPIO10         | dtoverlay: gpio-led trigger     |
| 17      | 11  | Shutdown Trigger   | Input       | Expander            | `dtoverlay=gpio-shutdown`       |
| 27      | 13  | Reboot Trigger     | Input       | Expander            | `dtoverlay=gpio-restart`        |
| 22      | 15  | User-defined Input | Input       | Expander            | Optional override or trigger    |
| 14      | 8   | UART TX            | Output      | XIAO RX (GPIO1)     | Serial console                  |
| 15      | 10  | UART RX            | Input       | XIAO TX (GPIO0)     | Serial console                  |

---

## 🔋 Power & Ground

| Signal | Pi Pin(s) | XIAO Pin | Notes                         |
|--------|-----------|----------|-------------------------------|
| 5V     | 2 or 4    | 14 (VBUS) | Via Schottky, dual-source capable — see note below |
| GND    | 6, 9, etc | 13       | Shared ground reference        |

> ⚠️ **Note on VBUS and Power Safety:**
>
> The XIAO RP2040 includes an internal Schottky diode between its USB-C VBUS input and Pin 14 (VBUS). This prevents backfeed from external 5V sources (like the Pi) into the USB port. When combined with an external Schottky diode protecting the Pi's 5V rail, this configuration allows safe, simultaneous connection of both USB-C and Pi 5V power. Seeed Studio's documentation includes a generalized warning about battery safety that applies to other XIAO boards with LiPo support — the RP2040 variant has no VBAT or battery charging circuitry. Therefore, powering VBUS (Pin 14) from the Pi while USB-C is also connected is safe **when both power sources are isolated via diodes.**

