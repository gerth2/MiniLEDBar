#ifndef _FRAME_PATTERN_H
#define _FRAME_PATTERN_H

#include <stdint.h>
#include <LEDCtrl.h>

typedef struct {
	float transitionInSec;
	float dwellSec;
	rgb_t colors[MAX_LED];
} frame_t;

typedef struct {
	uint16_t numFrames;
	frame_t * frames;
} framePattern_t;

typedef struct {
	uint16_t numPatterns;
	framePattern_t *patterns;
	float *ctrlValThresholds;
} patternSet;

// Global set of patterns loaded into the board
extern patternSet patterns;

framePattern_t* getCurPattern(float ctrlVal);

void getCurColors(rgb_t * outColors);
void startPattern(framePattern_t *newPattern);
void restartPattern();

#endif

