#pragma once

#include <vector>
#include <string>

#include "canvas.h"

namespace cirno_say
{
	namespace canvas
	{
		class Text : public Canvas
		{
			std::vector<std::vector<Char> > s;
			int x_;
			public:
			Text();
			Text(std::vector<std::vector<Char> > s);
			static Text from_wstring(const std::wstring &s);
			Char operator[](const std::pair<int, int> &c);
			int x();
			int y();
		};
	}
}
