#ifndef _TIMER_EVENTS_H
#define _TIMER_EVENTS_H

#include <stdbool.h>
#include <stdint.h>

void timer_SysTick_Handler(void);

bool timer_20msTimerTriggered(void);
void timer_reset20msTimer(void);
float timer_getCurTimeSec(void);

#endif
