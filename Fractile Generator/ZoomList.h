#pragma once
#include <vector>
#include "Zoom.h"

class ZoomList
{
public:

	ZoomList() {}
	ZoomList(int p_width, int p_height);
	void add(const Zoom& zoom);
	std::pair<double, double> doZoom(int p_x, int p_y);


private:
	
	int height{ 0 };
	int width{ 0 };
	double xCenter{ 0.0 };
	double yCenter{ 0.0 };
	double scale{ 1.0 };

	std::vector<Zoom> zooms;

};

