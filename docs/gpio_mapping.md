# Raspberry Pi to MCU GPIO Mapping

This document defines the GPIO connections between the Raspberry Pi and the microcontroller (Feather ESP32-S3 or XIAO RP2040) for the BMC-lite HAT project.

---

## Raspberry Pi GPIO Assignments

| Function            | Pi Pin # | BCM GPIO | Direction | Description |
|---------------------|----------|----------|-----------|-------------|
| Shutdown Trigger    | 15       | GPIO22   | Input     | Pi shuts down when pulled LOW by MCU |
| Poweroff Indicator  | 37       | GPIO26   | Output    | Pi drives HIGH when safe to power off |
| Reset Trigger       | 13       | GPIO27   | Input     | Pi reboots when pulled LOW by MCU |
| UART TX (Pi → MCU)  | 8        | GPIO14   | Output    | Serial console output from Pi |
| Heartbeat GPIO      | 11       | GPIO17   | Output    | Pi toggles HIGH/LOW to indicate activity |

---

## Feather ESP32-S3 Reverse TFT GPIO Assignments

| Function            | Feather GPIO | Notes |
|---------------------|---------------|-------|
| Shutdown (→ Pi GPIO22) | GPIO5        | Output from Feather |
| Restart (→ Pi GPIO27)  | GPIO6        | Output from Feather |
| UART RX (← Pi GPIO14)  | GPIO7        | Serial2 RX |
| Poweroff (← Pi GPIO26) | GPIO8        | Input to Feather |
| Heartbeat (← Pi GPIO17)| GPIO9        | Input to Feather |

---

## XIAO RP2040 GPIO Assignments

| Function            | XIAO Pin | RP2040 GPIO | Notes |
|---------------------|----------|-------------|-------|
| Shutdown (→ Pi GPIO22) | D1   | GPIO1       | Output |
| Restart (→ Pi GPIO27)  | D2   | GPIO2       | Output |
| UART RX (← Pi GPIO14)  | D3   | GPIO3       | Input |
| Poweroff (← Pi GPIO26) | D4   | GPIO4       | Input |
| Heartbeat (← Pi GPIO17)| D5   | GPIO5       | Input |
