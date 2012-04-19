#pragma once

#include <vector>
#include <wchar.h>

#include "canvas.h"

namespace cirno_say
{
	namespace canvas
	{
		class Border:public Canvas
		{
			int r, sr;
			int color1;
			int color2;
			int x_, y_;
			Canvas &canvas;
			int cr(int x, int y, int r);
			int col(int x, int y);
			public:
			Border(Canvas *canvas, int r, int sr, int color1, int color2);
			Char operator[](const std::pair<int, int> &c);
			int x();
			int y();
		};
	}
}
