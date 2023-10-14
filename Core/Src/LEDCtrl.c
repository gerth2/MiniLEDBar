#include <colorSpace.h>
#include <LEDCtrl.h>
#include "stm32f4xx_hal.h"
#include <math.h>
#include <utils.h>

//See https://datasheet.lcsc.com/lcsc/2211021800_XINGLIGHT-XL-3535RGBC-WS2812B_C2843786.pdf for timings

uint8_t LED_Data[MAX_LED][4];

#define LOW_TIME_CYCLES 70

uint16_t pwmData[(3 * 8 * MAX_LED) + LOW_TIME_CYCLES];
uint8_t datasentflag = 0;

void Set_LED(int LEDnum, rgb_t in) {
	uint8_t redBits = round(255.0 * cap(in.r));
	uint8_t greenBits = round(255.0 * cap(in.g));
	uint8_t blueBits = round(255.0 * cap(in.b));

	Set_LED_Hex(LEDnum, redBits, greenBits, blueBits);
}

void Set_LED_Hex(int LEDnum, uint8_t r, uint8_t g, uint8_t b) {

	LED_Data[LEDnum][0] = LEDnum;
	LED_Data[LEDnum][1] = g;
	LED_Data[LEDnum][2] = r;
	LED_Data[LEDnum][3] = b;
}

void Clear_LED() {
	for (int i = 0; i < MAX_LED; i++) {
		Set_LED_Hex(i, 0, 0, 0);
	}
}

void WS2812_Send() {
	uint32_t indx = 0;
	uint32_t color;

	for (int i = 0; i < MAX_LED; i++) {

		color = ((LED_Data[i][1] << 16) | (LED_Data[i][2] << 8)
				| (LED_Data[i][3]));

		for (int i = 23; i >= 0; i--) {
			// 84 MHZ clock * 1.2 us per bit period = 101 ABP1 clock cycles per period

			if (color & (1 << i)) {
				pwmData[indx] = (uint16_t) round(101.0 / 1.2 * 0.64); // bit 1 = 0.64us nominal high period
			} else {
				pwmData[indx] = (uint16_t) round(101.0 / 1.2 * 0.3); // bit 0 = 0.3us nominal high period
			}

			indx++;
		}

	}

	for (int i = 0; i < LOW_TIME_CYCLES; i++) {
		pwmData[indx] = 0;
		indx++;
	}

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*) pwmData, indx);
	while (!datasentflag) {
	};
	datasentflag = 0;
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
	HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
	datasentflag = 1;
}
