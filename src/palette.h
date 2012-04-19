#pragma once

#include <stdint.h>

#include <map>
#include <string>

namespace cirno_say
{
	class Palette
	{
		uint8_t pal_r[256];
		uint8_t pal_g[256];
		uint8_t pal_b[256];
		std::map<uint32_t, int> cache;
	
		public:
		Palette(const std::string &file_name);
		int color(int r, int g, int b, int a) const;
	};
}
