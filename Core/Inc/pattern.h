#ifndef _PATTERN_H
#define _PATTERN_H

typedef struct {
    float r;       // ∈ [0, 1]
    float g;       // ∈ [0, 1]
    float b;       // ∈ [0, 1]
} rgb;

typedef struct {
	float h;       // ∈ [0, 360]
	float s;       // ∈ [0, 1]
    float v;       // ∈ [0, 1]
} hsv;

extern const rgb off;

rgb hsv2rgb(hsv HSV);

#endif
