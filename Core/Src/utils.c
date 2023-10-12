#include <utils.h>

float cap(float in){
	if(in > 1.0) return 1.0;
	if(in < -1.0) return -1.0;
	return in;
}
