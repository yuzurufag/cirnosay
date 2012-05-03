#include "compose.h"

namespace cirno_say
{
	namespace canvas
	{
		Compose::Compose()
		{
		}
		Char Compose::getChar(int x, int y)
		{
			int t = Char::TRANSPARENT, b = Char::TRANSPARENT;
			for (auto i: canvas)
			{
				Char c = i.c->getChar(x - i.x, y - i.y);
				if(t != Char::TRANSPARENT && b == Char::TRANSPARENT)
				{
					if(c.c == WCHAR_LOWER_HALF_BLOCK || c.c == WCHAR_FULL_BLOCK)
						return Char::half_blocks(t, c.fg);
					if(c.bg != -1)
						return Char::half_blocks(t, c.bg);
				}
				else if(t == Char::TRANSPARENT && b != Char::TRANSPARENT)
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
				if(t != Char::TRANSPARENT && b != Char::TRANSPARENT)
					return Char::half_blocks(t, b);
			}
			return Char::half_blocks(t, b);
		}
		void Compose::setMaxX(int x)
		{
			x_ = x;
			for (auto i: canvas)
				if(x - i.x > 0)
					i.c->setMaxX(x - i.x);
		}
		void Compose::setMaxY(int y)
		{
			y_ = y;
			//for (auto i: canvas)
			//	if(y - i.y > 0)
			//		i.c->setMaxY(y - i.y);
		}
		int Compose::x()
		{
			int x = 0;
			for (auto i: canvas)
			{
				int n = i.x + i.c->x();
				if(n > x_ && x_ != -1)
					return x_;
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
				if(n > y_ && y_ != -1)
					return y_;
				if(n > y)
					y = n;
			}
			return y;
		}
	}
}
