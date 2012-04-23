#pragma once

namespace cirno_say
{
	const wchar_t WCHAR_UPPER_HALF_BLOCK = 0x2580;
	const wchar_t WCHAR_LOWER_HALF_BLOCK = 0x2584;
	const wchar_t WCHAR_FULL_BLOCK       = 0x2588;

	struct Char
	{
		int fg, bg;
		wchar_t c;

		static Char half_blocks(int t, int b);
		static Char empty();
	};
}
