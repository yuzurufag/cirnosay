#pragma once

namespace cirno_say
{
	const wchar_t WCHAR_LOWER_HALF_BLOCK = 132;
	const wchar_t WCHAR_UPPER_HALF_BLOCK = 128;
	const wchar_t WCHAR_FULL_BLOCK = 136;

	struct Char
	{
		int fg;
		int bg;

		wchar_t c;

		static Char half_blocks(int t, int b);
		static Char empty();
	};
}
