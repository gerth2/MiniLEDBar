#ifndef _LEDCTRL_H
#define _LEDCTRL_H

#include <colorSpace.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

#define MAX_LED 10


extern uint16_t pwmData[];
extern uint8_t datasentflag;

extern TIM_HandleTypeDef htim1; //STM32Cube makes this private, but I want it public



void Set_LED (int LEDnum, rgb in);
void Set_LED_Hex (int LEDnum, uint8_t r, uint8_t g, uint8_t b);
void Clear_LED();
void WS2812_Send (void);


#endif
