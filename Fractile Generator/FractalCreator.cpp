#include "FractalCreator.h"
#include "Mandelbrot.h"
#include "Zoom.h"

FractalCreator::FractalCreator(int p_width, int p_height)
	: WIDTH(p_width), HEIGHT(p_height), histogram(new int[Mandelbrot::maxIterations]{}), fractal(new int[WIDTH * HEIGHT]{}), bitmap(WIDTH, HEIGHT), zoomList(WIDTH, HEIGHT)
{

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

				green = pow(255, hue);
			}

			bitmap.setPixel(x, y, red, green, blue);
		}
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
