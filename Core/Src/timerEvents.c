#include <timerEvents.h>

static volatile uint32_t ms_ticks = 0;
static volatile bool tick_1ms_elapsed = false;
static volatile bool tick_20ms_elapsed = false;

// The interrupt handler
// This must be called inside SysTick_Handler() which is in stm32f4xx_it.c
void timer_SysTick_Handler(void) {
	ms_ticks++;

	tick_1ms_elapsed = true;

	if (ms_ticks % 20 == 0) {
		//Trigger a new 20ms event
		tick_20ms_elapsed = true;
	}

	//TODO fix the day-49 bug here where ms_ticks rolls over after 49.7 days of operation
}


bool timer_20msTimerTriggered(){
	return tick_20ms_elapsed;
}

void timer_reset20msTimer(){
	tick_20ms_elapsed = false;
}

float timer_getCurTimeSec(){
	return ((float)ms_ticks) / 1000.0;
}
