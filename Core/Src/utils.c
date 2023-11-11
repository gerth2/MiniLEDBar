#include <utils.h>
#include <stdbool.h>
#include <stdlib.h>

float cap(float in) {
	if (in > 1.0)
		return 1.0;
	if (in < -1.0)
		return -1.0;
	return in;
}

float map(float in, const float in_min, const float in_max, const float out_min, const float out_max){
	float ret_val = out_min + ( (out_max - out_min) * ( (in - in_min)/(in_max - in_min) ) );

	if(ret_val > out_max){
		ret_val = out_max;
	} else if (ret_val < out_min){
		ret_val = out_min;
	}

	return ret_val;
}

void IIR1(float in, float * out, const float factor ){
	//since this is first order, we cheat.
	// Before this is called, out is assumed to point to the previous output
	// After it is called, out will have the current output
	float prevOut = *out;
	*out = (1.0 - factor)*prevOut + factor * in;
}

bool getRandBool(float prob_true){
	int thresh = (prob_true) * RAND_MAX;
	return rand() < thresh;
}
