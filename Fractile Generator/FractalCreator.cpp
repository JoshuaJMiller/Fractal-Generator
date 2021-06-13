#include <memory>
#include <math.h>
#include <iostream>			//debug

#include "FractalCreator.h"
#include "Mandelbrot.h"
#include "Zoom.h"

FractalCreator::FractalCreator(int p_width, int p_height)
	: WIDTH(p_width), HEIGHT(p_height), histogram(new int[Mandelbrot::maxIterations]{}), fractal(new int[WIDTH * HEIGHT]{}), bitmap(WIDTH, HEIGHT), zoomList(WIDTH, HEIGHT)
{

}

void FractalCreator::run(std::string p_filename)
{
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
	RGB startColor(0, 100, 0);
	RGB endColor(100, 200, 100);
	RGB colorDiff = startColor - endColor;

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			uint8_t red{ 0 };
			uint8_t green{ 0 };
			uint8_t blue{ 0 };

			int iterations = fractal[y * WIDTH + x];

			if (iterations != Mandelbrot::maxIterations)
			{

				double hue{ 0 };
				for (int i{ 0 }; i <= iterations; ++i)
				{
					hue += ((double)histogram[i]) / totalIterations;
				}

				red = startColor.r + colorDiff.r * hue;
				green = startColor.g + colorDiff.g * hue;
				blue = startColor.b + colorDiff.b * hue;
			}

			bitmap.setPixel(x, y, red, green, blue);
		}
	}
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
