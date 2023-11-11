#include <math.h>
#include <timerEvents.h>
#include <colorSpace.h>
#include <LEDCtrl.h>
#include <utils.h>


float sparkleVals[MAX_LED] = {0.0};


void getRgSparkleColors(rgb_t * outColors){
	for(int i = 0; i < MAX_LED; i++){

		if(getRandBool(0.0005)){
			//bump sparkle value
			sparkleVals[i] = 0.2;
		} 
		

		//alternate red/green
		outColors[i].r = (i % 2) ? ON : 0.0 + sparkleVals[i];
		outColors[i].g = (i % 2) ? 0.0 : ON + sparkleVals[i];
		outColors[i].b = sparkleVals[i]; 

		//decay the sparkle value
		sparkleVals[i] *= 0.85;

	}


}