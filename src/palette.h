#pragma once

#include <stdint.h>

#include <string>

#include "color.h"

namespace cirno_say {

class Palette
{
public:
	Palette();
	Palette(const std::string &file_name, bool _24bit);
	Palette &operator=(const Palette &);
	~Palette();
	Color color(int r, int g, int b, int a) const;
private:
	bool _24bit;
	size_t pal_size;
	uint8_t *pal_r;
	uint8_t *pal_g;
	uint8_t *pal_b;
};

}
