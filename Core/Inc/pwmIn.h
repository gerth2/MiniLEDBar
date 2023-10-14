#ifndef _PWMIN_H
#define _PWMIN_H

#include <stdbool.h>

#define PWM_TIMEOUT_MILLIS 250

// Public API
void pwm_init();
float pwm_getCtrlVal();
bool pwm_isActive();

#endif
