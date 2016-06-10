#pragma once
#include "color.h"

namespace cirno_say {

const wchar_t WCHAR_UPPER_HALF_BLOCK = 0x2580;
const wchar_t WCHAR_LOWER_HALF_BLOCK = 0x2584;
const wchar_t WCHAR_FULL_BLOCK = 0x2588;

struct Char
{
	wchar_t c;
	Color fg;
	Color bg;
	bool bold;
	bool underline;

	Char(wchar_t c = ' ', Color fg = color::DEFAULT, Color bg = color::DEFAULT,
	     bool bold = false, bool underline = false);
	static Char half_blocks(int t, int b);
};

}
