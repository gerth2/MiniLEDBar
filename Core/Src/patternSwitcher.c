#include <patternSwitcher.h>

#include <framePatterns.h>
#include <framePatternDefs.h>
#include <rgRandomPattern1.h>
#include <rgRandomPattern2.h>
#include <colorSpace.h>

void patternSwitcherInit(){

	startPattern(&framePattern1);
	seedRGPatterns1();

}


void patternSwitcherUpdate20ms(rgb_t * outColors){

    getCurColors(outColors);
    getRgRandomPatternColors1(outColors);
    getRgRandomPatternColors2(outColors);
}