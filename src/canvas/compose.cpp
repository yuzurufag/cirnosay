#include "compose.h"

namespace cirno_say
{
	namespace canvas
	{
		Compose::Compose()
		{
		}
		Char Compose::operator[](const std::pair<int, int> &c)
		{
			int x = c.first;
			int y = c.second;
			int t = -1, b = -1;
			for (auto i: canvas)
			{
				Char c = (*i.c)[std::pair<int, int>(x - i.x, y - i.y)];
				if(t != -1 && b == -1)
				{
					if(c.c == WCHAR_LOWER_HALF_BLOCK || c.c == WCHAR_FULL_BLOCK)
						return Char::half_blocks(t, c.fg);
					if(c.bg != -1)
						return Char::half_blocks(t, c.bg);
				}
				else if(t == -1 && b != -1)
				{
					if(c.c == WCHAR_UPPER_HALF_BLOCK || c.c == WCHAR_FULL_BLOCK)
						return Char::half_blocks(c.fg, b);
					if(c.bg != -1)
						return Char::half_blocks(c.bg, b);
				}
				else if(c.c == WCHAR_UPPER_HALF_BLOCK && c.bg == -1)
					t = c.fg;
				else if(c.c == WCHAR_LOWER_HALF_BLOCK && c.bg == -1)
					b = c.fg;
				else if(c.c == L' ' && c.bg == -1)
					;
				else
					return c;
				if(t != -1 && b != -1)
					return Char::half_blocks(t, b);
			}
			return Char::half_blocks(t, b);
		}
		int Compose::x()
		{
			int x = 0;
			for (auto i: canvas)
			{
				int n = i.x + i.c->x();
				if(n > x)
					x = n;
			}
			return x;
		}
		int Compose::y()
		{
			int y = 0;
			for (auto i: canvas)
			{
				int n = i.y + i.c->y();
				if(n > y)
					y = n;
			}
			return y;
		}
	}
}
