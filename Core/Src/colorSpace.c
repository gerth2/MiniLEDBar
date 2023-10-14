#include <colorSpace.h>
#include <math.h>



rgb_t hsv2rgb(hsv_t HSV) {
	rgb_t RGB;
	double H = HSV.h, S = HSV.s, V = HSV.v, P, Q, T, fract;

	(H == 360.) ? (H = 0.) : (H /= 60.);
	fract = H - floor(H);

	P = V * (1. - S);
	Q = V * (1. - S * fract);
	T = V * (1. - S * (1. - fract));

	if (0. <= H && H < 1.)
		RGB = (rgb_t ) { .r = V, .g = T, .b = P };
	else if (1. <= H && H < 2.)
		RGB = (rgb_t ) { .r = Q, .g = V, .b = P };
	else if (2. <= H && H < 3.)
		RGB = (rgb_t ) { .r = P, .g = V, .b = T };
	else if (3. <= H && H < 4.)
		RGB = (rgb_t ) { .r = P, .g = Q, .b = V };
	else if (4. <= H && H < 5.)
		RGB = (rgb_t ) { .r = T, .g = P, .b = V };
	else if (5. <= H && H < 6.)
		RGB = (rgb_t ) { .r = V, .g = P, .b = Q };
	else
		RGB = (rgb_t ) { .r = 0., .g = 0., .b = 0. };

	return RGB;
}
