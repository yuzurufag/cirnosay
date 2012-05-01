#pragma once

#include <stdlib.h>
#include <string>

#include "palette.h"

namespace cirno_say
{
	class Picture
	{
		int x_, y_;
		int *i;
		public:
		Picture(std::string file_name, const Palette &palette);
		~Picture();
		int getPixel(int x, int y);
		int x();
		int y();
	};
}
