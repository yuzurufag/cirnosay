#include "char.h"

namespace cirno_say
{
	Char::Char(wchar_t c, int fg, int bg, bool bold, bool underline)
	{
		this->c = c;
		this->fg = fg;
		this->bg = bg;
		this->bold = bold;
		this->underline = underline;
	}

	Char Char::half_blocks(int t, int b)
	{
		switch(t)
		{
			case DEFAULT: switch(b)
			{
				case DEFAULT:     return Char(WCHAR_FULL_BLOCK,       -1, -1);
				case TRANSPARENT: return Char(WCHAR_UPPER_HALF_BLOCK, -1, -1);
				default:          return Char(WCHAR_UPPER_HALF_BLOCK, -1, b );
			}
			case TRANSPARENT: switch(b)
			{
				case DEFAULT:     return Char(WCHAR_LOWER_HALF_BLOCK, -1, -1);
				case TRANSPARENT: return Char(L' ',                   -1, -1);
				default:          return Char(WCHAR_LOWER_HALF_BLOCK,  b, -1);
			}
			default: switch(b)
			{
				case DEFAULT:     return Char(WCHAR_LOWER_HALF_BLOCK, -1, t );
				case TRANSPARENT: return Char(WCHAR_UPPER_HALF_BLOCK, t,  -1);
				default:          return Char(WCHAR_LOWER_HALF_BLOCK, b,  t );
			}
		}
	}
}
