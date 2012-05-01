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
			Char getChar(int x, int y);
			void setMaxX(int x);
			void setMaxY(int y);
			int x();
			int y();
		};
	}
}
