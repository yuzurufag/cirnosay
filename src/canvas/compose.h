#pragma once

#include <vector>

#include "canvas.h"

namespace cirno_say
{
	namespace canvas
	{
		class Compose:public Canvas
		{
			int x_ = -1;
			int y_ = -1;
			public:
			struct Element
			{
				int x, y;
				Canvas *c;
			};
			std::vector<Element> canvas;
			Compose();
			Char operator[](const std::pair<int, int> &c);
			void setMaxX(int x);
			void setMaxY(int y);
			int x();
			int y();
		};
	}
}
