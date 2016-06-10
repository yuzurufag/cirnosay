#include "palette.h"

#include <cstring>

#include <Imlib2.h>
#include <assert.h>

namespace cirno_say {

Palette::Palette()
{
	_24bit = false;
	pal_size = 0;
	pal_r = pal_g = pal_b = nullptr;
}
Palette::Palette(const std::string &file_name, bool _24bit)
: Palette()
{
	this->_24bit = _24bit;
	if (!file_name.size())
		return;
	Imlib_Image image = imlib_load_image(file_name.c_str());
	assert(image);
	imlib_context_set_image(image);
	pal_size = imlib_image_get_width() * imlib_image_get_height();
	// assert(pal_size == 256);
	uint8_t *img_data = (uint8_t *)imlib_image_get_data();
	pal_r = new uint8_t[pal_size];
	pal_g = new uint8_t[pal_size];
	pal_b = new uint8_t[pal_size];
	for (size_t i = 0; i < pal_size; i++)
	{
		pal_r[i] = img_data[i * 4 + 2];
		pal_g[i] = img_data[i * 4 + 1];
		pal_b[i] = img_data[i * 4 + 0];
	}
	imlib_free_image();
}
Palette &Palette::operator=(const Palette &p)
{
	_24bit = p._24bit;
	pal_size = p.pal_size;
	pal_r = new uint8_t[pal_size];
	pal_g = new uint8_t[pal_size];
	pal_b = new uint8_t[pal_size];
	std::memcpy(pal_r, p.pal_r, pal_size);
	std::memcpy(pal_g, p.pal_g, pal_size);
	std::memcpy(pal_b, p.pal_b, pal_size);
	return *this;
}
Palette::~Palette()
{
	delete[] pal_r;
	delete[] pal_g;
	delete[] pal_b;
}
Color Palette::color(int r, int g, int b, int a) const
{
	if (a < 127)
		return -1;

	if (_24bit)
		return (r * 256 * 256 | g * 256 | b) + 256;

	int best = 0;
	int best_result = 256 * 256 * 3;
	for (size_t i = 0; i < pal_size; i++)
	{
		int result = (pal_r[i] - r) * (pal_r[i] - r) +
		             (pal_g[i] - g) * (pal_g[i] - g) +
		             (pal_b[i] - b) * (pal_b[i] - b);
		if (result < best_result)
		{
			best_result = result;
			best = i;
		}
	}

	return best;
}

}
