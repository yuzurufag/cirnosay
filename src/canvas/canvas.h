#pragma once

#include <vector>

#include "../char.h"

namespace cirno_say
{
	namespace canvas
	{
		class Canvas
		{
			public:
			virtual Char operator[](const std::pair<int, int> &c) = 0;
			virtual void setMaxX(int x) = 0;
			//virtual void setMaxY(int y) = 0;
			virtual int x() = 0;
			virtual int y() = 0;
		};
	}
}
