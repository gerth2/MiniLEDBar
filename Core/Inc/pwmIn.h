#ifndef _PWMIN_H
#define _PWMIN_H

#include <stdbool.h>

#define PWM_TIMEOUT_MILLIS 250

#define PWM_CTRL_MIN -1.0
#define PWM_CTRL_CENTER 0.0
#define PWM_CTRL_MAX 1.0
#define PWM_CTRL_DEADZONE 0.05

// Public API
void pwm_init();
float pwm_getCtrlVal();
bool pwm_isActive();

#endif
