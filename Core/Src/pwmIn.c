#include <pwmIn.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"

// These variables are calculated in the callback handler for the timer input
volatile uint32_t ICValue = 0;
volatile float Frequency = 0;
volatile float Duty;
volatile uint32_t lastUpdateMillis;

float Fapb2clk_hz;

//Callback handler for when a new PWM period has been read in
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) // If the interrupt is triggered by channel 1
			{
		// Read the IC value
		ICValue = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

		if (ICValue != 0) {
			// calculate the Duty Cycle
			Duty = (float) (HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2))
					/ ((float) (ICValue)) * 100.0;

			Frequency = Fapb2clk_hz / ((float) (ICValue));

			lastUpdateMillis = HAL_GetTick();
		}
	}
}

// Logic Init for PWM input. Must be called after all hardware
// timers are set up, but before interrupts go active
void pwm_init() {
	//Cache the frequency of the underlying clock driving the sampling
	Fapb2clk_hz = (float) (HAL_RCC_GetPCLK2Freq());
}

// Return the FRC-style -1.0 to 1.0 motor output value
float pwm_getCtrlVal() {
	float pulseTime_ms = 1.0 / ((float) (Frequency)) * 1000.0 * (Duty / 100.0);
	return cap((pulseTime_ms - 1.5) / 0.5);
}

// Returns true if there's an active pulse chain coming in
// False if we've missed enough pulses that it's probably not active
bool pwm_isActive() {
	return (HAL_GetTick() - lastUpdateMillis) < PWM_TIMEOUT_MILLIS;
}

