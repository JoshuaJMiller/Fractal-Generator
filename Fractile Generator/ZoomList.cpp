#include "ZoomList.h"
#include <iostream>

ZoomList::ZoomList(int p_width, int p_height)
	: width(p_width), height(p_height) {}

void ZoomList::add(const Zoom& p_zoom)
{
	xCenter = (p_zoom.x - width / 2) * scale;
	yCenter = (p_zoom.y - height / 2) * scale;
	scale *= p_zoom.scale;
	zooms.push_back(p_zoom);	

	std::cout << xCenter << ", " << yCenter << ", " << scale << std::endl;
}

std::pair<double, double> ZoomList::doZoom(int p_x, int p_y)
{
	double xFractal = (p_x - width / 2) * scale + xCenter;
	double yFractal = (p_y - height / 2) * scale + yCenter;
	return std::pair<double, double>(xFractal, yFractal);

}