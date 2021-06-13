#pragma once

#include "Bitmap.h"
#include "ZoomList.h"
#include "RGB.h"
#include <string>
#include <vector>

class FractalCreator
{
public:
	//member variables
	bool success;

	//member funtions
	FractalCreator(int p_width, int p_height);
	void run(std::string p_filename);
	void addRange(double p_range, const RGB& p_rgb);
private:
	//memeber variables
	const int WIDTH;
	const int HEIGHT;
	int totalIterations;
	Bitmap bitmap;
	ZoomList zoomList;
	std::unique_ptr<int[]> histogram;
	std::unique_ptr<int[]> fractal;
	std::vector<int> ranges;
	std::vector<RGB> colors;
	std::vector<int> rangeTotals;
	bool gotFirstRange{ false };

	//member functions
	void calculateIterations();
	void drawFractal();
	void calculateRangeTotals();
	void addZoom(double p_scale);
	void addZoom(int p_x, int p_y, double p_scale);
	void writeBitmap(std::string p_name);
};

