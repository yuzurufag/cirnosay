#pragma once

#include <vector>

#include "canvas.h"

namespace cirno_say
{
	namespace canvas
	{
		class Compose:public Canvas
		{
			public:
			struct Element
			{
				int x, y;
				Canvas *c;
			};
			std::vector<Element> canvas;
			Compose();
			Char operator[](const std::pair<int, int> &c);
			int x();
			int y();
		};
	}
}
