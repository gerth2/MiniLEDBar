#ifndef _COLORSPACE_H
#define _COLORSPACE_H

#define HUE_MAX 360.0
#define HUE_MIN 0.0

#define RGB_OFF  { 0, 0, 0 }
#define RGB_RED { 0.5, 0, 0 }
#define RGB_WHITE { 0.25, 0.25, 0.25 }

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

#endif
