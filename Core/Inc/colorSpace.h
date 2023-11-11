#ifndef _COLORSPACE_H
#define _COLORSPACE_H

#include <stdint.h>


#define HUE_MAX 360.0
#define HUE_MIN 0.0

#define ON 0.25

#define RGB_OFF  { 0, 0, 0 }
#define RGB_RED { ON, 0, 0 }
#define RGB_GREEN { 0.0, ON, 0 }
#define RGB_WHITE { ON, ON, ON }

typedef struct {
	float r;       // ∈ [0, 1]
	float g;       // ∈ [0, 1]
	float b;       // ∈ [0, 1]
} rgb_t;

typedef struct {
	float h;       // ∈ [0, 360]
	float s;       // ∈ [0, 1]
	float v;       // ∈ [0, 1]
} hsv_t;

extern rgb_t OFF;
extern rgb_t RED;
extern rgb_t WHITE;

rgb_t hsv2rgb(hsv_t HSV);

void getInterpolatedColors(rgb_t * first, rgb_t * second, float frac, rgb_t * outColorArr, uint8_t count);
void copyColors(rgb_t * src, rgb_t * dst, uint8_t count);

#endif
