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
		switch(((t == DEFAULT)?0:(t == TRANSPARENT)?3:6) + ((b == DEFAULT)?0:(b == TRANSPARENT)?1:2))
		{
			case 0: return Char(WCHAR_FULL_BLOCK,       -1, -1);
			case 1: return Char(WCHAR_UPPER_HALF_BLOCK, -1, -1);
			case 2: return Char(WCHAR_UPPER_HALF_BLOCK, -1, b );

			case 3: return Char(WCHAR_LOWER_HALF_BLOCK, -1, -1);
			case 4: return Char(L' ',                   -1, -1);
			case 5: return Char(WCHAR_LOWER_HALF_BLOCK, b,  -1);

			case 6: return Char(WCHAR_LOWER_HALF_BLOCK, -1, t );
			case 7: return Char(WCHAR_UPPER_HALF_BLOCK, t,  -1);
			case 8: return Char(WCHAR_UPPER_HALF_BLOCK, t,  b );
		}
	}
}
