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
			bool mirror;
			cirno_say::Picture picture;
			int x_, y_;
			public:
			Picture(std::string file_name, const Palette &palette, bool mirror);
			Char getChar(int x, int y);
			int x();
			int y();
			void setMaxX(int x);
			void setMaxY(int y);
		};
	}
}
