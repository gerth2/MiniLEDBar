#ifndef _PATTERN_H
#define _PATTERN_H

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
} pattern_t;

typedef struct {
	uint16_t numPatterns;
	pattern_t *patterns;
	float *ctrlValThresholds;
} patternSet;

// Global set of patterns loaded into the board
extern patternSet patterns;

pattern_t* getCurPattern(float ctrlVal);

void getCurColors(rgb_t * outColors);
void startPattern(pattern_t *newPattern);
void restartPattern();

#endif

