#ifndef _PATTERN_H
#define _PATTERN_H

#include <stdint.h>
#include <LEDCtrl.h>

typedef struct {
	float fadeInSec;
	float fadeOutSec;
	float dwellSec;
	rgb colors[MAX_LED];
} frame;

typedef struct {
	uint16_t numFrames;
	frame *frames;
	float curPatternTimeSec;
} pattern;

typedef struct {
	uint16_t numPatterns;
	pattern *patterns;
	float *ctrlValThresholds;
} patternSet;

// Global set of patterns loaded into the board
extern patternSet patterns;

pattern* getCurPattern(float ctrlVal);

float getTotalPatternTime(pattern *in);

rgb* getCurColors(pattern *curPattern);

#endif

