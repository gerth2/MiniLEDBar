#include <framePatternDefs.h>
#include <colorSpace.h>


frame_t framePattern1Frames[] = {
		{
				3.0, //transitionInSec
				3.0, //dwellSec
				{    // colors
						RGB_GREEN,
						RGB_GREEN,
						RGB_GREEN,
						RGB_WHITE,
						RGB_GREEN,
						RGB_GREEN,
						RGB_GREEN,
						RGB_GREEN,
						RGB_WHITE,
						RGB_GREEN,
						RGB_GREEN,
						RGB_GREEN,
				}
		},
		{
				3.0, //transitionInSec
				0.0, //dwellSec
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
						RGB_OFF,
						RGB_OFF,
				}
		},
		{
				3.0, //transitionInSec
				3.0, //dwellSec
				{    // colors
						RGB_GREEN,
						RGB_GREEN,
						RGB_RED,
						RGB_RED,
						RGB_RED,
						RGB_GREEN,
						RGB_GREEN,
						RGB_RED,
						RGB_RED,
						RGB_GREEN,
						RGB_WHITE,
						RGB_RED,
				}
		},
		{
				3.0, //transitionInSec
				0.0, //dwellSec
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
						RGB_OFF,
						RGB_OFF,
				}
		},
		{
				3.0, //transitionInSec
				3.0, //dwellSec
				{    // colors
						RGB_WHITE,
						RGB_GREEN,
						RGB_RED,
						RGB_GREEN,
						RGB_RED,
						RGB_GREEN,
						RGB_WHITE,
						RGB_RED,
						RGB_RED,
						RGB_GREEN,
						RGB_RED,
						RGB_GREEN,
				}
		},
		{
				3.0, //transitionInSec
				0.0, //dwellSec
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
						RGB_OFF,
						RGB_OFF,
				}
		},

};

framePattern_t framePattern1 = {
		sizeof(framePattern1Frames)/sizeof(frame_t),// numFrames
		framePattern1Frames  // frames
};
