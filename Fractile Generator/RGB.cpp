#include "RGB.h"

RGB::RGB(double p_r, double p_g, double p_b)
	: r(p_r), g(p_g), b(p_b)
{
}

RGB operator-(const RGB& first, const RGB& second)
{
	return RGB(first.r - second.r, first.g - second.g, first.b - second.b);
}