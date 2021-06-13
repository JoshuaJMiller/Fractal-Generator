#include <memory>
#include <math.h>
#include <iostream>			//debug
#include <assert.h>

#include "FractalCreator.h"
#include "Mandelbrot.h"
#include "Zoom.h"

FractalCreator::FractalCreator(int p_width, int p_height)
	: WIDTH(p_width), HEIGHT(p_height), histogram(new int[Mandelbrot::maxIterations]{}), fractal(new int[WIDTH * HEIGHT]{}), bitmap(WIDTH, HEIGHT), zoomList(WIDTH, HEIGHT)
{
}

void FractalCreator::run(std::string p_filename)
{
	addRange(0.0, RGB(255, 0, 0));
	addRange(0.3, RGB(0, 255, 0));
	addRange(0.5, RGB(0, 255, 255));
	addRange(1.0, RGB(0, 255, 255));
	addZoom(4.0);
	addZoom(120, 150, 0.3);
	addZoom(0, 0, 0.1);
	calculateIterations();
	calculateRangeTotals();
	drawFractal();
	writeBitmap(p_filename);
}

void FractalCreator::calculateIterations()
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			std::pair<double, double> coords = zoomList.doZoom(x, y);

			int iterations = Mandelbrot::getIterations(coords.first, coords.second);

			fractal[y * WIDTH + x] = iterations;

			if (iterations != Mandelbrot::maxIterations)
			{
				histogram[iterations]++;
			}
		}
	}
	for (int i{ 0 }; i < Mandelbrot::maxIterations; ++i)
	{
		totalIterations += histogram[i];
	}
}
void FractalCreator::drawFractal()
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			int iterations = fractal[y * WIDTH + x];

			int range = getRange(iterations);
			int rangeTotal = rangeTotals.at(range);
			int rangeStart = ranges.at(range);

			RGB& startColor = colors.at(range);
			RGB& endColor = colors.at(range + 1);
			RGB colorDiff = endColor - startColor;

			uint8_t red{ 0 };
			uint8_t green{ 0 };
			uint8_t blue{ 0 };

			

			if (iterations != Mandelbrot::maxIterations)
			{
				int totalPixels{ 0 };
				for (int i{ rangeStart }; i <= iterations; ++i)
				{
					totalPixels += histogram[i];
				}

				red = startColor.r + colorDiff.r * (double)totalPixels / rangeTotal;
				green = startColor.g + colorDiff.g * (double)totalPixels / rangeTotal;
				blue = startColor.b + colorDiff.b * (double)totalPixels / rangeTotal;
			}

			bitmap.setPixel(x, y, red, green, blue);
		}
	}
}

int FractalCreator::getRange(int p_iterations) const
{
	int range{ 0 };

	for (int i{ 1 }; i < ranges.size(); ++i)
	{
		range = i;
		if (ranges.at(i) > p_iterations)
		{
			break;
		}
	}
	range--;
	assert(range > -1);
	assert(range < ranges.size());
	return range;
}

void FractalCreator::addRange(double p_range, const RGB& p_rgb)
{
	ranges.push_back(p_range * Mandelbrot::maxIterations);
	colors.push_back(p_rgb);

	if (gotFirstRange)
	{
		rangeTotals.push_back(0);
	}
	gotFirstRange = true;
}

void FractalCreator::calculateRangeTotals()
{
	int rangeIndex{ 0 };

	for (int i{ 0 }; i < Mandelbrot::maxIterations; ++i)
	{
		int pixels = histogram[i];

		if (i >= ranges.at(rangeIndex + 1))
		{
			rangeIndex++;
		}

		rangeTotals.at(rangeIndex) += pixels;
	}

	for (auto value : rangeTotals)
	{
		std::cout << "value : " << value << std::endl;
	}
}

void FractalCreator::addZoom(double p_scale)
{
	zoomList.add(Zoom(WIDTH / 2, HEIGHT / 2, p_scale / WIDTH));
}
void FractalCreator::addZoom(int p_x, int p_y, double p_scale)
{
	zoomList.add(Zoom(p_x, HEIGHT - p_y, p_scale));
}
void FractalCreator::writeBitmap(std::string p_name)
{
	success = bitmap.write(p_name);
}
