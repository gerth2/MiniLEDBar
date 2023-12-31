#ifndef _UTILS_H
#define _UTILS_H
#include <stdbool.h>

float cap(float in);
float map(float in, const float in_min, const float in_max, const float out_min, const float out_max);
void IIR1(float in, float * out, const float factor );
bool getRandBool(float prob_true);

#endif
