#include "Bitmap.h"
#include "BitmapFile.h"
#include "BitmapInfo.h"
#include <fstream>

#pragma pack(2)

Bitmap::Bitmap(int32_t p_width, int32_t p_height)
	: width(p_width), height(p_height), pPixel(new uint8_t[p_width * p_height * 3]{})
{

}

Bitmap::~Bitmap()
{

}

bool Bitmap::write(std::string p_filname)
{
	BitmapFileHeader fileHeader;
	BitmapInfoHeader infoHeader;

	fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + (width * height * 3);
	fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

	infoHeader.width = width;
	infoHeader.height = height;

	std::ofstream outFile(p_filname, std::ios::binary);

	if (!outFile)
	{
		return false;
	}

	outFile.write((char *)&fileHeader, sizeof(fileHeader));
	outFile.write((char *)&infoHeader, sizeof(infoHeader));
	outFile.write((char *)pPixel.get(), (width * height * 3));

	/*size_t numOfPixels = infoHeader.width * infoHeader.height;
	for (int i{ 0 }; i < numOfPixels; ++i)
	{
		outFile.write((char *)&pPixel, 3);
	}*/

	outFile.close();

	if (!outFile)
	{
		return false;
	}

	return true;
}

void Bitmap::setPixel(int p_x, int p_y, uint8_t p_red, uint8_t p_green, uint8_t p_blue)
{
	uint8_t* pixel = pPixel.get();

	pixel += (p_y * 3) * width + (p_x * 3);

	pixel[0] = p_blue;
	pixel[1] = p_green;
	pixel[2] = p_red;
}

void Bitmap::fillBitmap(std::array<uint8_t, 3> rgb)
{
	
	for (size_t y{ 0 }; y < height; ++y)
	{
		for (size_t x{ 0 }; x < width; ++x)
		{
			setPixel(x, y, rgb.at(0), rgb.at(1), rgb.at(2));
		}
	}	
}

void Bitmap::fillBitmap(uint8_t p_red, uint8_t p_green, uint8_t p_blue)
{
	for (size_t y{ 0 }; y < height; ++y)
	{
		for (size_t x{ 0 }; x < width; ++x)
		{
			setPixel(x, y, p_red, p_green, p_blue);
		}
	}
}