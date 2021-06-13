#include <iostream>
#include <string>

#include "FractalCreator.h"
#include "RGB.h"

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
	/*RGB rgb1(4, 5, 6);
	RGB rgb2(1, 2, 3);
	RGB rgb3 = rgb1 - rgb2;

	std::cout << rgb3.r << rgb3.g << rgb3.b << std::endl;*/

	std::cout << std::boolalpha;
	std::string filename{ "fractal1.bmp" };
	FractalCreator fractalCreator(800, 600);

	fractalCreator.addRange(0.0, RGB(0, 0, 0));
	fractalCreator.addRange(0.3, RGB(255, 0, 0));
	fractalCreator.addRange(0.5, RGB(255, 255, 0));
	fractalCreator.addRange(1.0, RGB(255, 255, 255));

	fractalCreator.run(filename);

	std::cout << fractalCreator.success << "\nfinished." << std::endl;

	return 0;
}