#include <patternDefs.h>
#include <colorSpace.h>

// Disabled Pattern
frame_t disabledFrames[] = {
		{
				0.01, //transitionInSec
				0.01, //dwellSec
				{    // colors
						RGB_OFF,
						RGB_OFF,
						RGB_OFF,
						RGB_OFF,
						RGB_OFF,
						RGB_OFF,
						RGB_OFF,
						RGB_OFF,
						RGB_OFF,
						RGB_OFF,
				}
		},
		{
				1.0, //transitionInSec
				0.5, //dwellSec
				{    // colors
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
				}
		},
		{
				0.05, //transitionInSec
				0.0, //dwellSec
				{    // colors
						RGB_WHITE,
						RGB_WHITE,
						RGB_WHITE,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
				}
		},
		{
				0.05, //transitionInSec
				0.0, //dwellSec
				{    // colors
						RGB_RED,
						RGB_RED,
						RGB_WHITE,
						RGB_WHITE,
						RGB_WHITE,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
				}
		},
		{
				0.05, //transitionInSec
				0.0, //dwellSec
				{    // colors
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_WHITE,
						RGB_WHITE,
						RGB_WHITE,
				}
		},
		{
				0.05, //transitionInSec
				0.0, //dwellSec
				{    // colors
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_WHITE,
						RGB_WHITE,
						RGB_WHITE,
						RGB_RED,
						RGB_RED,
				}
		},
		{
				0.05, //transitionInSec
				1.0, //dwellSec
				{    // colors
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_RED,
				}
		},
		{
				1.0, //transitionInSec
				2.0, //dwellSec
				{    // colors
						RGB_OFF,
						RGB_OFF,
						RGB_OFF,
						RGB_OFF,
						RGB_OFF,
						RGB_OFF,
						RGB_OFF,
						RGB_OFF,
						RGB_OFF,
						RGB_OFF,
				}
		},

};

pattern_t disabledPattern = {
		sizeof(disabledFrames)/sizeof(frame_t),// numFrames
		disabledFrames  // frames
};
