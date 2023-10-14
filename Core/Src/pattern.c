#include <pattern.h>
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
pattern_t *curPattern;

void startFrame(void){
	curFrame = &curPattern->frames[curFrameIdx];
	inTransition = true;
	frameStartTime = timer_getCurTimeSec();
}

void startPattern(pattern_t *newPattern){
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

void getInterpolatedColors(rgb_t * first, rgb_t * second, float frac, rgb_t * outColorArr){
	for(uint8_t ledIdx = 0; ledIdx < MAX_LED; ledIdx++){
		// Linearly interpolate in RGB space
		outColorArr[ledIdx].r = (1.0 - frac) * first[ledIdx].r + (frac) * second[ledIdx].r ;
		outColorArr[ledIdx].g = (1.0 - frac) * first[ledIdx].g + (frac) * second[ledIdx].g ;
		outColorArr[ledIdx].b = (1.0 - frac) * first[ledIdx].b + (frac) * second[ledIdx].b ;
	}
}

void copyColors(rgb_t * src, rgb_t * dst){
	for(uint8_t ledIdx = 0; ledIdx < MAX_LED; ledIdx++){
		dst[ledIdx].r = src[ledIdx].r;
		dst[ledIdx].g = src[ledIdx].g;
		dst[ledIdx].b = src[ledIdx].b;
	}
}

void getCurColors(rgb_t * outColors){

	float timeInFrame = timer_getCurTimeSec() - frameStartTime;

	if(inTransition){
		//transitioning
		if(timeInFrame < curFrame->transitionInSec){
			// calculate the weighted transitional average
			float frac = timeInFrame /  (curFrame->transitionInSec);
			getInterpolatedColors(prevFrame->colors, curFrame->colors, frac, outColors);

		} else{
			// Display full frame and transition to dwell
			inTransition = false;
		    prevFrame = curFrame;
		    copyColors(curFrame->colors, outColors);
		}

	} else {
		// dwelling
	    copyColors(curFrame->colors, outColors);

		float dwellEnd = curFrame->transitionInSec + curFrame->dwellSec;
		if(timeInFrame >= dwellEnd){
			//Done dwelling, advance to next frame
			curFrameIdx = (curFrameIdx + 1) % curPattern->numFrames;
			startFrame();
		}
	}





}
