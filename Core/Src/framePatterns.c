#include <framePatterns.h>
#include <math.h>
#include <timerEvents.h>
#include <stdbool.h>

//Global State
frame_t * prevFrame = NULL;
frame_t * curFrame = NULL;
float frameStartTime;
bool inTransition = false;
rgb_t transitionColor;
uint16_t curFrameIdx = 0;
framePattern_t *curPattern;

void startFrame(void){
	curFrame = &curPattern->frames[curFrameIdx];
	inTransition = true;
	frameStartTime = timer_getCurTimeSec();
}

void startPattern(framePattern_t *newPattern){
	curPattern = newPattern;
	if(curPattern->numFrames > 0){
		curFrameIdx = 0;
		startFrame();

		if(prevFrame == NULL){
			//First-time init of prev frame
			prevFrame = curFrame;
		}
	}
}

void restartPattern(){
	if(curPattern->numFrames > 0){
		curFrameIdx = 0;
		startFrame();
		prevFrame = curFrame;
	}
}

void getCurColors(rgb_t * outColors){

	float timeInFrame = timer_getCurTimeSec() - frameStartTime;

	if(inTransition){
		//transitioning
		if(timeInFrame < curFrame->transitionInSec){
			// calculate the weighted transitional average
			float frac = timeInFrame /  (curFrame->transitionInSec);
			getInterpolatedColors(prevFrame->colors, curFrame->colors, frac, outColors, MAX_LED);

		} else{
			// Display full frame and transition to dwell
			inTransition = false;
		    prevFrame = curFrame;
		    copyColors(curFrame->colors, outColors, MAX_LED);
		}

	} else {
		// dwelling
	    copyColors(curFrame->colors, outColors, MAX_LED);

		float dwellEnd = curFrame->transitionInSec + curFrame->dwellSec;
		if(timeInFrame >= dwellEnd){
			//Done dwelling, advance to next frame
			curFrameIdx = (curFrameIdx + 1) % curPattern->numFrames;
			startFrame();
		}
	}

}
