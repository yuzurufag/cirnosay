#pragma once

#include <string>

#include "canvas.h"
#include "../palette.h"
#include "../picture.h"

namespace cirno_say
{
	namespace canvas
	{
		class Picture : public Canvas
		{
			cirno_say::Picture picture;
			public:
			Picture(std::string file_name, const Palette &palette);
			Char operator[](const std::pair<int, int> &c);
			int x();
			int y();
			void setMaxX(int x);
			void setMaxY(int y);
		};
	}
}
