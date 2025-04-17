#pragma once

#include <Arduino.h>

// ─────────────────────────────────────────────
// XIAO RP2040 Physical Pinout (Castellated I/O)
// ─────────────────────────────────────────────

// I2C Bus
#define PIN_I2C_SDA            6   // GPIO 6 (D6)
#define PIN_I2C_SCL            7   // GPIO 7 (D7)

// UART to Pi
#define PIN_UART_TX            0   // GPIO 0 (D0)
#define PIN_UART_RX            1   // GPIO 1 (D1)

// NeoPixel (onboard)
#define NEOPIXEL_DATA_PIN      12  // GPIO 12 (D12)
#define NEOPIXEL_POWER_PIN     11  // GPIO 11 (D11)

// Built-in RGB LED indicators
#define LED_RED_PIN            17  // GPIO 17 — USB→Pi TX activity
#define LED_GREEN_PIN          16  // GPIO 16 — Pi→USB RX activity
#define LED_BLUE_PIN           25  // GPIO 25 — CDC activity/idle

// HEARTBEAT signal input from Pi (fast pulse)
#define PIN_HEARTBEAT_INPUT    10  // GPIO 10 — direct input from Pi (no debounce)

// Optional test/debug pins
#define DEBUG_PIN_0            2   // GPIO 2 (D2)
#define DEBUG_PIN_1            3   // GPIO 3 (D3)
#define DEBUG_PIN_2            4   // GPIO 4 (D4)
#define DEBUG_PIN_3            5   // GPIO 5 (D5)
#define DEBUG_PIN_4            8   // GPIO 8 (D8)
#define DEBUG_PIN_5            9   // GPIO 9 (D9)

// ─────────────────────────────────────────────
// I/O Function Mapping Summary
// ─────────────────────────────────────────────
// | Signal Name           | Direction | Source         | Description
// |------------------------|-----------|----------------|-----------------------------
// | PIN_I2C_SDA            | I/O       | XIAO GPIO 6    | I²C Data line
// | PIN_I2C_SCL            | O         | XIAO GPIO 7    | I²C Clock line
// | PIN_UART_TX            | O         | XIAO GPIO 0    | UART TX → Pi RX
// | PIN_UART_RX            | I         | XIAO GPIO 1    | UART RX ← Pi TX
// | NEOPIXEL_DATA_PIN      | O         | XIAO GPIO 12   | WS2812 NeoPixel data
// | NEOPIXEL_POWER_PIN     | O         | XIAO GPIO 11   | Power enable for NeoPixel
// | LED_RED_PIN            | O         | XIAO GPIO 17   | TX activity indicator
// | LED_GREEN_PIN          | O         | XIAO GPIO 16   | RX activity indicator
// | LED_BLUE_PIN           | O         | XIAO GPIO 25   | USB/CDC activity indicator
// | PIN_HEARTBEAT_INPUT    | I         | XIAO GPIO 10   | Pulse from Pi (fast)
// | DEBUG_PIN_*            | I/O       | XIAO GPIO 2–9  | Debug/expansion testpoints
// | EXP_BUTTON_RAW_*       | I         | MCP23017       | Raw expander button inputs
// | EXP_SIGNAL_*           | Logic     | Firmware       | Debounced button states
// | EXP_LED_POWEROFF       | O         | MCP23017       | Power-off status LED

// ─────────────────────────────────────────────
// MCP23017 I/O Expander Virtual GPIO Mapping
// ─────────────────────────────────────────────

// Raw button input pins (un-debounced)
#define EXP_BUTTON_RAW_SHUTDOWN   0
#define EXP_BUTTON_RAW_REBOOT     1
#define EXP_BUTTON_RAW_USER1      2

// LEDs controlled via expander
#define EXP_LED_POWEROFF       3  // RED: safe to remove power

// Debounced logical state (used by firmware)
#define EXP_SIGNAL_SHUTDOWN    4
#define EXP_SIGNAL_REBOOT      5
#define EXP_SIGNAL_USER1       6

//#define EXP_LED_USER_MODE      9  // Optional user-defined status LED

// ─────────────────────────────────────────────
// I2C Device Addresses
// ─────────────────────────────────────────────
#define MCP23017_I2C_ADDR      0x20
#define OLED_I2C_ADDR          0x3C
