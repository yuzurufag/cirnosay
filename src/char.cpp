#include "char.h"

namespace cirno_say
{
	Char Char::half_blocks(int t, int b)
	{
		if(t == -1)
		{
			if(b == -1)
				return {-1, -1, L' '};
			else
				return {b, -1, WCHAR_LOWER_HALF_BLOCK};
		}
		return {t, b, WCHAR_UPPER_HALF_BLOCK};
	}
	Char Char::empty()
	{
		return {-1, -1, L' '};
	}
}
