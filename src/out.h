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
		int b_;
		int f_;
		public:
		Out(canvas::Canvas &i);
		std::string to_s();
		private:
		void color(int b, int f);
		void put_pixels(int a, int b);
		void put_wchar_t(const wchar_t &c);
		void nl();
	};
}
