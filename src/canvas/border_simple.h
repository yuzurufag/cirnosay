#pragma once

#include <vector>

#include "canvas.h"

namespace cirno_say
{
	namespace canvas
	{
		class BorderSimple:public Canvas
		{
			Canvas &canvas;
			int fg, bg;
			int max_width = -1;
			int width, height;
			int pad_x, pad_y;
			int arrow_size, arrow_position;
			bool mirror;
			int col(int x, int y);
			public:
			BorderSimple(Canvas *canvas, int fg, int bg, bool mirror);
			Char getChar(int x, int y);
			int x();
			int y();
			void setMaxX(int x);
		};
	}
}
