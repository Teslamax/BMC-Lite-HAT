# 📌 BMC-Lite HAT Pin Mapping

## 🔌 XIAO RP2040 GPIO Assignments

| GPIO | Pin | Function           | Direction     | Connected To         | Notes                              |
|------|-----|--------------------|---------------|----------------------|------------------------------------|
| 0    | 1   | UART TX            | XIAO → Pi     | Pi GPIO15 (Pin 10)   | UART console                       |
| 1    | 2   | UART RX            | Pi → XIAO     | Pi GPIO14 (Pin 8)    | UART console                       |
| 4    | 10  | I²C SDA            | Bidirectional | OLED, GPIO Expander  | Addr `0x3C` (OLED), `0x20` (MCP)   |
| 5    | 5   | I²C SCL            | Bidirectional | OLED, GPIO Expander  | Shared I²C bus                     |
| 6    | 6   | Shutdown to Pi     | Output        | Pi GPIO17 (Pin 11)   | Debounced output                   |
| 7    | 7   | Reboot to Pi       | Output        | Pi GPIO27 (Pin 13)   | Debounced output                   |
| 8    | 8   | User-defined to Pi | Output        | Pi GPIO22 (Pin 15)   | Debounced output                   |
| 9    | 9   | Poweroff-Ready     | Input         | Pi GPIO5 (Pin 29)    | Level signal                       |
| 10   | 10  | Heartbeat          | Input         | Pi GPIO6 (Pin 31)    | dtoverlay-driven 1Hz pulse         |
| 26   | 1   | INT from Expander  | Input         | MCP23017 INT Pin     | INT fires on button state changes  |
| 27   | 2   | Free               | —             | —                    | General-purpose                    |
| 28   | 3   | Free (ADC)         | —             | —                    | ADC-capable input                  |
| 29   | 4   | Free (ADC)         | —             | —                    | ADC-capable input                  |

> ⚠️ Note: According to Seeed Studio's schematic, the XIAO RP2040 includes a Schottky diode between USB 5V (VBUS) and the 5V input rail to its internal DC-DC converter. This is intended to **protect against backfeeding** when 5V is applied to Pin 14 while the USB-C is also connected. While this hardware protection exists, official documentation warns:
> “XIAO RP2040 currently only supports battery power supply and cannot connect to Type-C while a battery is connected, as it may pose a safety risk.”
>
> This likely serves as a **conservative safety/lawyer notice**, but in practice, with correct use of **power source selection via Schottky diodes or a switch**, simultaneous connections can be made **safely** for debug/dev use. Proceed cautiously and avoid having multiple 5V sources active without proper current-direction control.

---

## 🔌 MCP23017 GPIO Expander (Prototyping Phase)

| Bank  | Pin      | Function             | Direction | Connected To | Notes                  |
|-------|----------|----------------------|-----------|---------------|------------------------|
| GPA0  | Button 1 | Input                | Input     | Button 1      | Debounced in software  |
| GPA1  | Button 2 | Input                | Input     | Button 2      |                        |
| GPA2  | Button 3 | Input                | Input     | Button 3      |                        |
| GPB0  | Shutdown | Output to Pi        | Output    | Pi GPIO17     | Debounced logic state  |
| GPB1  | Reboot   | Output to Pi        | Output    | Pi GPIO27     |                        |
| GPB2  | User     | Output to Pi        | Output    | Pi GPIO22     |                        |
| GPx3–7| —        | Unused               | —         | —             | Reserved for expansion |

---

## 🔌 Raspberry Pi GPIO Assignments

| Pi GPIO | Pin | Function           | Direction   | Connected To     | Notes                           |
|---------|-----|--------------------|-------------|------------------|---------------------------------|
| 5       | 29  | Poweroff-Ready     | Output      | XIAO GPIO9       | High when safe to power off     |
| 6       | 31  | Heartbeat          | Output      | XIAO GPIO10      | dtoverlay: gpio-led trigger     |
| 17      | 11  | Shutdown Trigger   | Input       | XIAO or Expander | dtoverlay=gpio-shutdown         |
| 27      | 13  | Reboot Trigger     | Input       | XIAO or Expander | dtoverlay=gpio-restart          |
| 22      | 15  | User-defined Input | Input       | XIAO or Expander | Optional override or trigger    |
| 14      | 8   | UART TX            | Output      | XIAO RX (GPIO1)  | Serial console                  |
| 15      | 10  | UART RX            | Input       | XIAO TX (GPIO0)  | Serial console                  |
| 2/4     | 3/5 | I²C SDA/SCL        | (Unused)    | —                | Not shared with XIAO I²C        |
| 2       | 4   | 5V Power           | Output      | XIAO VBUS via diode | Used only in RUN mode      |

---

## 🔋 Power & Ground

| Signal | Pi Pin(s) | XIAO Pin | Notes                         |
|--------|-----------|----------|-------------------------------|
| 5V     | 2 or 4    | 14 (VBUS) | Via Schottky, controlled by switch |
| GND    | 6, 9, etc | 13       | Shared ground reference        |

---

> This pinout reflects the current working configuration. If any changes are made to wiring or GPIO assignment, update this document as the single source of truth.
> Link this file from all project documentation (`README.md`, `OVERVIEW.md`, etc.).

