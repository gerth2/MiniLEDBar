#include <math.h>
#include <timerEvents.h>
#include <stdbool.h>
#include <colorSpace.h>
#include <LEDCtrl.h>
#include <stdlib.h>

bool isUsingRed[MAX_LED] = {true};


void getRgRandomPatternColors2(rgb_t * outColors){
	for(int i = 0; i < MAX_LED; i++){

		// Adjust these parameters to control the appearance of the effect
		float frequency1 = 0.48;  // Adjust the frequency of the red color component
		float frequency2 = 0.57;  // Adjust the frequency of the green color component

		float phaseShift1 = 0.3;  // Adjust the phase shift of the red color component
		float phaseShift2 = 0.37;  // Adjust the phase shift of the green color component

		float amplitude = ON;  // Adjust the amplitude of the color components

		// Calculate color components using sine functions
		float time = timer_getCurTimeSec();
		float red = amplitude * fmax(sinf(frequency1 * time + phaseShift1 * i) + 0.75, 0.0);
		float green = amplitude * fmax(sinf(frequency2 * time + phaseShift2 * i * -1.0) + 0.75, 0.0);

		// If both colors have faded enough we can switch without it looking yellow, do so
		if(red < 0.00001 && green < 0.00001){
			isUsingRed[i] = !isUsingRed[i];
		}

		// Return the generated color
		outColors[i].r = isUsingRed[i] ? red : 0.0;
		outColors[i].g = isUsingRed[i] ? 0.0 : green;
		outColors[i].b = 0.0;  // Blue component is set to 0 for a Christmas-like effect
	}


}