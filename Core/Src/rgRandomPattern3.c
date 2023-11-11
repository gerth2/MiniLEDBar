#include <math.h>
#include <timerEvents.h>
#include <stdbool.h>
#include <colorSpace.h>
#include <LEDCtrl.h>
#include <stdlib.h>


void getRgRandomPatternColors3(rgb_t * outColors){
	for(int i = 0; i < MAX_LED; i++){

		// Adjust these parameters to control the appearance of the effect
		float frequency1 = 0.28;  // Adjust the frequency of the red color component
		float frequency2 = 0.37;  // Adjust the frequency of the green color component

		float phaseShift1 = 0.3;  // Adjust the phase shift of the red color component
		float phaseShift2 = 0.37;  // Adjust the phase shift of the green color component

		// Calculate color components using sine functions
		float time = timer_getCurTimeSec();
		float hue = HUE_MAX * fabs(sinf(frequency1 * time + phaseShift1 * i));
		float sat = 1.0 - (0.5 * fabs(sinf(frequency2 * time + phaseShift2 * i * -1.0)));

		// Return the generated color
		hsv_t tmp1 = {hue, sat, ON*0.5};
		rgb_t tmp2 = hsv2rgb(tmp1);
		copyColors(&tmp2, &outColors[i], 1);
	}


}