#pragma once

extern bool EXP_SIGNAL_SHUTDOWN;
extern bool EXP_SIGNAL_REBOOT;
extern bool EXP_SIGNAL_USER1;

void initButtons();
void checkButtons();
