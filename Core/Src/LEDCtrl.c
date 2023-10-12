#include <LEDCtrl.h>
#include "stm32f4xx_hal.h"
#include "pattern.h"
#include <math.h>
#include <utils.h>

uint8_t LED_Data[MAX_LED][4];



uint16_t pwmData[(24*MAX_LED)+50];
uint8_t datasentflag = 0;

void Set_LED (int LEDnum, rgb in){
	uint8_t redBits   = round(255.0 * cap(in.r));
	uint8_t greenBits = round(255.0 * cap(in.g));
	uint8_t blueBits  = round(255.0 * cap(in.b));

    LED_Data[LEDnum][0] = LEDnum;
    LED_Data[LEDnum][1] = greenBits;
    LED_Data[LEDnum][2] = redBits;
    LED_Data[LEDnum][3] = blueBits;
}

void Clear_LED(){
    for(int i = 0; i < MAX_LED; i++){
        Set_LED(i, off);
    }
}


void WS2812_Send (){
    uint32_t indx=0;
    uint32_t color;


    for (int i= 0; i<MAX_LED; i++)
    {

        color = ((LED_Data[i][1]<<16) | (LED_Data[i][2]<<8) | (LED_Data[i][3]));

        for (int i=23; i>=0; i--)
        {
            if (color&(1<<i))
            {
                pwmData[indx] = 60;  // 2/3 of 90
            }

            else pwmData[indx] = 30;  // 1/3 of 90

            indx++;
        }

    }

    for (int i=0; i<50; i++)
    {
        pwmData[indx] = 0;
        indx++;
    }

    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData, indx);
    while (!datasentflag){};
    datasentflag = 0;
}
