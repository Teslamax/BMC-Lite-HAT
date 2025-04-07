#pragma once

enum SystemState {
  STATE_OFF,
  STATE_BOOTING,
  STATE_RUNNING,
  STATE_SHUTTING_DOWN,
  STATE_HALTED,
  STATE_CRASH,
  STATE_UNRESPONSIVE
};

void initStatusLED();
void setSystemState(SystemState state);
void updateStatusLED();
