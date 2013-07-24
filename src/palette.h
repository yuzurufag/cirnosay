#pragma once

#include <stdint.h>

#include <map>
#include <string>

namespace cirno_say
{
	class Palette
	{
		size_t pal_size;
		uint8_t *pal_r;
		uint8_t *pal_g;
		uint8_t *pal_b;
	
		public:
		Palette(const std::string &file_name);
		~Palette();
		int color(int r, int g, int b, int a) const;
	};
}
