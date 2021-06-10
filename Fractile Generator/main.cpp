#include <iostream>
#include <string>
#include <memory>
#include <math.h>
#include "Bitmap.h"
#include "Mandelbrot.h"

#pragma pack(2)

void bitmapCreator()
{

	std::cout << "BITMAP creator!" << std::endl;

	bool oversized = 1;
	bool validColor = 0;
	bool validName = 0;
	int width{ 0 };
	int height{ 0 };
	std::array<uint8_t, 3> bitmapColor;
	std::string fileName1;

	while (oversized)
	{
		std::cout << "\nEnter bitmap width (less than 1600) > ";
		std::cin >> width;
		std::cout << "Enter bitmap height (less than 900) > ";
		std::cin >> height;
		if (width > 1600 || height > 900)
		{
			oversized = 1;
			std::cout << "oversized bitmap! (max W x H is 1600 x 900)" << std::endl;
		}
		else
		{
			break;
		}
	}

	while (!validColor)
	{
		std::cout << "enter color RED value (0 - 255) > ";
		int r;
		std::cin >> r;
		bitmapColor.at(0) = r;
		std::cout << "enter color BLUE value (0 - 255) > ";
		int g;
		std::cin >> g;
		bitmapColor.at(1) = g;
		std::cout << "enter color GREEN value (0 - 255) > ";
		int b;
		std::cin >> b;
		bitmapColor.at(2) = b;

		if (bitmapColor.at(0) > 255 || bitmapColor.at(0) < 1 || bitmapColor.at(1) > 255 || bitmapColor.at(1) < 1 || bitmapColor.at(2) > 255 || bitmapColor.at(2) < 1)
		{
			validColor = 0;
			std::cout << "invalid color values! (0 - 255)" << std::endl;
		}
		else
		{
			break;
		}
	}

	while (!validName)
	{
		std::cout << "enter file name (including .bmp extension) > ";
		std::cin >> fileName1;
		//getline(std::cin, fileName1);
		//if (/*logic to find bad file name*/)
		//{
		//	validName = 0;
		//}
		//else
		//{
		//	break;
		//}
		break;
	}

	bool created = 0;

	Bitmap bitmap1(width, height);
	bitmap1.fillBitmap(bitmapColor);
	created = bitmap1.write(fileName1);

	std::cout << "finished" << std::endl;
}

int main()
{
	const int WIDTH{ 800 };
	const int HEIGHT{ 600 };

	std::cout << std::boolalpha;
	std::string filename{ "test6debug.bmp" };

	Bitmap bitmap(WIDTH, HEIGHT);

	//std::array<uint8_t, 3> blue = { 0, 255, 0 };

	//bitmap.fillBitmap(0, 0, 255);

	double max = 99999;
	double min = -99999;

	std::unique_ptr<int[]> histogram (new int[Mandelbrot::maxIterations]{  });
	std::unique_ptr<int[]> fractal(new int[WIDTH * HEIGHT]{  });

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			double xFractile = (x - WIDTH / 2 - 200) * 2.0 / HEIGHT;
			double yFractile = (y - HEIGHT / 2) * 2.0 / HEIGHT;
			int iterations = Mandelbrot::getIterations(xFractile, yFractile);

			fractal[y * WIDTH + x] = iterations;

			if (iterations != Mandelbrot::maxIterations)
			{
				histogram[iterations]++;
			}
		}
	}

	int totalIterations{ 0 };
	for (int i{ 0 }; i < Mandelbrot::maxIterations; ++i)
	{
		totalIterations += histogram[i];
	}

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

	bool success = bitmap.write(filename);

	std::cout << success << "\nfinished." << std::endl;


	return 0;
}