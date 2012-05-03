#pragma once

#include <sstream>
#include <string>

#include "canvas/canvas.h"
#include "char.h"

namespace cirno_say
{
	class Out
	{
		std::stringstream out;
		int bg_, fg_;
		bool bold_, underline_;
		public:
		Out(canvas::Canvas &i);
		std::string to_s();
		private:
		void put_raw(int bg, int fg, int bold, int underline, wchar_t c);
		void put(Char &c);
		void nl();
	};
}
