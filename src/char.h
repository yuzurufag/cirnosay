#pragma once

namespace cirno_say
{
	const wchar_t WCHAR_UPPER_HALF_BLOCK = 0x2580;
	const wchar_t WCHAR_LOWER_HALF_BLOCK = 0x2584;
	const wchar_t WCHAR_FULL_BLOCK       = 0x2588;

	struct Char
	{
		static const int DEFAULT = -1;
		static const int TRANSPARENT = -2;

		wchar_t c;
		int fg;
		int bg;
		bool bold;
		bool underline;

		Char(wchar_t c = ' ', int fg = DEFAULT, int bg = DEFAULT, bool bold = false, bool underline = false);
		static Char half_blocks(int t, int b);
	};
}
