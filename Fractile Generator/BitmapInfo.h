#pragma once
#include <cstdint>

#pragma pack(2)

struct BitmapInfoHeader
{
	uint32_t headerSize{ 40 };
	int32_t width;
	int32_t height;
	uint16_t planes{ 1 };
	uint16_t bitsPerPixel{ 24 };
	uint32_t compression{ 0 };
	uint32_t dataSize{ 0 };
	uint32_t horizontalResolution{ 3780 };
	uint32_t verticleResolution{ 3780 };
	uint32_t colors{ 0 };
	uint32_t importantColors{ 0 };
};