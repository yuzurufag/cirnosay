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
		int operator[](const std::pair<int, int> &c);
		int x();
		int y();
	};
}
