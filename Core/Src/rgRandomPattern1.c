#include <math.h>
#include <timerEvents.h>
#include <stdbool.h>
#include <colorSpace.h>
#include <LEDCtrl.h>
#include <stdlib.h>

typedef enum {
  STATE_OFF,
  STATE_RED,
  STATE_GREEN,
  STATE_TWINKLE,
  STATE_TRANS_RED_TO_OFF,
  STATE_TRANS_OFF_TO_RED,
  STATE_TRANS_GREEN_TO_OFF,
  STATE_TRANS_OFF_TO_GREEN
} ledState_t; 

typedef enum {
  INIT,
  TRANS_1,
  TRANS_2,
  HOLD_1
} patternState_t; 

bool curTransition = true;
bool prevTransition = false;

float transFracs;

ledState_t ledStates[MAX_LED] = {STATE_OFF};

static float stateStartTime = 0;
static patternState_t curPatternState = INIT;

bool getRandBool(float prob_true){
	int thresh = (prob_true) * RAND_MAX;
	return rand() < thresh;
}

void seedRGPatterns1(){
	for(int i = 0; i < MAX_LED; i++){
		ledStates[i] = getRandBool(0.5) ? STATE_TRANS_OFF_TO_RED : STATE_TRANS_OFF_TO_GREEN;
	}
	stateStartTime = timer_getCurTimeSec();
}

#define TRANS_TIME 2.0
#define HOLD_TIME 3.0


void getRgRandomPatternColors1(rgb_t * outColors){

	float timeInState = timer_getCurTimeSec() - stateStartTime;

	//Advance States
	switch(curPatternState){
		case INIT:
			if(timeInState > TRANS_TIME){
				//INIT --> HOLD_1
				curPatternState = HOLD_1;
				stateStartTime = timer_getCurTimeSec();
				timeInState = 0;
				for(int i = 0; i < MAX_LED; i++){
					if(ledStates[i] == STATE_TRANS_OFF_TO_RED){
						ledStates[i] = STATE_RED;
					}
					if(ledStates[i] == STATE_TRANS_OFF_TO_GREEN){
						ledStates[i] = STATE_GREEN;
					}
				}
			}
		break;
		case TRANS_1:
			if(timeInState > TRANS_TIME){
				//TRANS_1 --> TRANS_2
				curPatternState = TRANS_2;
				stateStartTime = timer_getCurTimeSec();
				timeInState = 0;
				for(int i = 0; i < MAX_LED; i++){
					if(ledStates[i] == STATE_RED && getRandBool(0.1)){
						ledStates[i] = STATE_TRANS_RED_TO_OFF;
					}
					if(ledStates[i] == STATE_GREEN && getRandBool(0.1)){
						ledStates[i] = STATE_TRANS_GREEN_TO_OFF;
					}
				}
			}
		break;
		case TRANS_2:
			if(timeInState > TRANS_TIME){
				//TRANS_2 --> HOLD_1
				curPatternState = HOLD_1;
				stateStartTime = timer_getCurTimeSec();
				timeInState = 0;
				for(int i = 0; i < MAX_LED; i++){
					if(ledStates[i] == STATE_TRANS_RED_TO_OFF){
						ledStates[i] = STATE_TRANS_OFF_TO_GREEN;
					}
					if(ledStates[i] == STATE_TRANS_GREEN_TO_OFF){
						ledStates[i] = STATE_TRANS_OFF_TO_RED;
					}
				}
			}
		break;
		case HOLD_1:
			if(timeInState > HOLD_TIME){
				//HOLD_1 --> TRANS_1
				curPatternState = TRANS_1;
				stateStartTime = timer_getCurTimeSec();
				timeInState = 0;
				for(int i = 0; i < MAX_LED; i++){
					if(ledStates[i] == STATE_TRANS_OFF_TO_RED){
						ledStates[i] = STATE_RED;
					}
					if(ledStates[i] == STATE_TRANS_OFF_TO_GREEN){
						ledStates[i] = STATE_GREEN;
					}
				}

			}
		break;
	}

	//Handle each LED state

	for(int i = 0; i < MAX_LED; i++){
		switch(ledStates[i]){
			case STATE_OFF:
			{
				rgb_t tmp = RGB_OFF;
				copyColors(&tmp, &outColors[i], 1);
			}
			break;
			case STATE_RED:
			{
				rgb_t tmp = RGB_RED;
				copyColors(&tmp, &outColors[i], 1);
			}
			break;
			case STATE_GREEN:
			{
				rgb_t tmp = RGB_GREEN;
				copyColors(&tmp, &outColors[i], 1);
			}
			break;
			case STATE_TWINKLE:
			{
				rgb_t tmp = RGB_WHITE;
				copyColors(&tmp, &outColors[i], 1);
			}
			break;
			case STATE_TRANS_RED_TO_OFF:
			{
				rgb_t tmp1 = RGB_RED;
				rgb_t tmp2 = RGB_OFF;
				getInterpolatedColors(&tmp1, &tmp2, timeInState/TRANS_TIME, &outColors[i], 1);
			}
			break;
			case STATE_TRANS_OFF_TO_RED:
			{
				rgb_t tmp1 = RGB_OFF;
				rgb_t tmp2 = RGB_RED;
				getInterpolatedColors(&tmp1, &tmp2, timeInState/TRANS_TIME, &outColors[i], 1);
			}
			break;
			case STATE_TRANS_GREEN_TO_OFF:
			{
				rgb_t tmp1 = RGB_GREEN;
				rgb_t tmp2 = RGB_OFF;
				getInterpolatedColors(&tmp1, &tmp2, timeInState/TRANS_TIME, &outColors[i], 1);
			}
			break;
			case STATE_TRANS_OFF_TO_GREEN:
			{
				rgb_t tmp1 = RGB_OFF;
				rgb_t tmp2 = RGB_GREEN;
				getInterpolatedColors(&tmp1, &tmp2, timeInState/TRANS_TIME, &outColors[i], 1);
			}
			break;
		}
	}

}
