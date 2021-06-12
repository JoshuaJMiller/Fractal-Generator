#pragma once
#include "Zoom.h"
#include <string>

class FractalCreator
{
public:
	FractalCreator(int p_width, int p_height);
	void calculateIterations();
	void drawFractal();
	void addZoom(const Zoom& p_zoom);
	void writeBitmap(std::string p_name);
private:
	const int WIDTH;
	const int HEIGHT;
};

