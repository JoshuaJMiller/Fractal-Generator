#pragma once

class RGB
{
public:
	RGB(double p_r, double p_g, double p_b);
	friend RGB operator-(const RGB& first, const RGB& last);
	double r;
	double g;
	double b;
};