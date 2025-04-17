#pragma once

#define FIRMWARE_VERSION "testing: build 1"

// ———————————————————————————————
// User‑echo compile‑time defaults
#define ECHO_USER_INITIAL  true
#define ECHO_USER_PREFIX   "➡️ "
#define PI_ECHO_PREFIX     "🐧 "

// ————— CDC Log‑Level Prefixes —————
#define CDC_INFO_PREFIX    "ℹ️  "   // informational
#define CDC_WARN_PREFIX    "⚠️  "   // warnings
#define CDC_ERROR_PREFIX   "❌ "    // errors
#define CDC_VERBOSE_PREFIX "🔍 "   // verbose/debug

// Set your runtime verbosity (0=errors only, 1=warnings+errors, 2=info+warn+err, 3=all)
static uint8_t cdcLogLevel = 2;
// ———————————————————————————————