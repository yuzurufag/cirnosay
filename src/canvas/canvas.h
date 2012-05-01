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
			virtual Char getChar(int x, int y) = 0;
			virtual void setMaxX(int x) = 0;
			//virtual void setMaxY(int y) = 0;
			virtual int x() = 0;
			virtual int y() = 0;
		};
	}
}
