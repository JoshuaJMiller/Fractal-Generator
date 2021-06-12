#pragma once
#include "Zoom.h"
#include "Bitmap.h"
#include "ZoomList.h"
#include <string>

class FractalCreator
{
public:
	bool success;

	FractalCreator(int p_width, int p_height);
	void calculateIterations();
	void drawFractal();
	void addZoom(double p_scale);
	void addZoom(int p_x, int p_y, double p_scale);
	void writeBitmap(std::string p_name);
private:
	const int WIDTH;
	const int HEIGHT;
	int totalIterations;
	Bitmap bitmap;
	ZoomList zoomList;
	std::unique_ptr<int[]> histogram;
	std::unique_ptr<int[]> fractal;
};

