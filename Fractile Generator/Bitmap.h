#pragma once
#include <string>
#include <cstdint>
#include <array>

#pragma pack(2)

class Bitmap
{
public:

	Bitmap(int32_t p_width, int32_t p_height);
	~Bitmap();
	bool write(std::string p_filname);
	void setPixel(int p_x, int p_y, uint8_t p_red, uint8_t p_green, uint8_t p_blue);
	void fillBitmap(std::array<uint8_t, 3>p_color);

private:

	int32_t width;
	int32_t height;
	std::unique_ptr<uint8_t[]> pPixel{ nullptr };

};
