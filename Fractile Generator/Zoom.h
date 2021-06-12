#pragma once
#include <utility>

struct Zoom
{
	int x{ 0 };
	int y{ 0 };
	double scale{ 0.0 };

	Zoom(int p_x, int p_y, double p_scale)
		: x(p_x), y(p_y), scale(p_scale){}

};
