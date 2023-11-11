#include <patternSwitcher.h>

#include <framePatterns.h>
#include <framePatternDefs.h>
#include <rgRandomPattern1.h>
#include <rgRandomPattern2.h>
#include <rgRandomPattern3.h>
#include <rgSparkle.h>
#include <colorSpace.h>
#include <timerEvents.h>

uint16_t patternIdx = 0;

typedef enum {
  FADE_IN,
  RUN,
  FADE_OUT
} switcherState_t; 

static float stateStartTime = 0;
static switcherState_t curState = FADE_IN;

#define RUN_TIME_SEC 60.0
#define FADE_TIME_SEC 4.0

#define NUM_PATTERNS 4

rgb_t curPatternOutput[MAX_LED];

void patternSwitcherInit(){

    // Init all patterns
    seedRGPatterns1();

    // Set up switcher state machine
    curState = FADE_IN;
    stateStartTime = timer_getCurTimeSec();

}


void patternSwitcherUpdate20ms(rgb_t * outColors){

    float timeInState = timer_getCurTimeSec() - stateStartTime;

    //First, step forward whatever pattern is running
    switch(patternIdx){
        case 0:
            getRgSparkleColors(curPatternOutput);
        break;
        case 1:
            getRgRandomPatternColors1(curPatternOutput);
        break;
        case 2:
            getRgRandomPatternColors2(curPatternOutput);
        break;
        case 3:
            getRgRandomPatternColors3(curPatternOutput);
        break;
    }

    // Next, apply transitions between pattrns if applicable
    switch(curState){
        case FADE_IN:
            if(timeInState >= FADE_TIME_SEC){
                //Transition states
                stateStartTime = timer_getCurTimeSec();
                curState = RUN;
            } else {
                //Fading from off to colors
                rgb_t tmp[MAX_LED] = {RGB_OFF};
                getInterpolatedColors(tmp, curPatternOutput, timeInState/FADE_TIME_SEC, outColors, MAX_LED);
            }
        break;

        case RUN:

            if(timeInState >= RUN_TIME_SEC){
                //Transition states
                stateStartTime = timer_getCurTimeSec();
                curState = FADE_OUT;
            } else {
                //Running normal, just copy
                copyColors(curPatternOutput, outColors, MAX_LED);
            }
        break;

        case FADE_OUT:
            if(timeInState >= FADE_TIME_SEC){
                //Transition states
                stateStartTime = timer_getCurTimeSec();
                curState = FADE_IN;
                patternIdx = (patternIdx + 1) % NUM_PATTERNS;
            } else {
                //Fading from colors to off
                rgb_t tmp[MAX_LED] = {RGB_OFF};
                getInterpolatedColors(curPatternOutput, tmp, timeInState/FADE_TIME_SEC, outColors, MAX_LED);
            }
        break;

    }

}