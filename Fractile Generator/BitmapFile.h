#pragma once
#include <cstdint>

#pragma pack(2)

struct BitmapFileHeader
{
	char header[2] = { 'B', 'M' };
	uint32_t fileSize;
	uint32_t reserved{ 0 };
	uint32_t dataOffset;
};
