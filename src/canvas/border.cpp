#include "border.h"

namespace cirno_say
{
	namespace canvas
	{
		int Border::cr(int x, int y, int r)
		{
			return ((x)*(x) + (y)*(y) <= r*r);
		}
		int Border::col(int x, int y)
		{
			if(x > x_/2+sr)
				return col(x_ + 2*sr - x - 1, y);
			if(y > y_ + sr)
				return col(x, y_*2 + 2*sr - y - 1);
			if ((x <= r) && (y <= r))
			{
				if (cr(x-r-2, y-r-2, r))
					return color2;
				if (cr(x-r-1, y-r-1, r))
					return color1;
				if (cr(x-r, y-r, r))
					return color2;
				return -1;
			}
			if((x == 1) || (y == 1))
				return color1;
			return color2;
		}
		Border::Border(Canvas *canvas, int r, int sr, int color1, int color2): canvas(*canvas)
		{
			x_ = canvas->x();
			y_ = canvas->y();
			this->r = r;
			this->color1 = color1;
			this->color2 = color2;
			this->sr = sr;
		}
		Char Border::operator[](const std::pair<int, int> &c)
		{
			int x = c.first;
			int y = c.second;
			if ( (x >= sr) && (x < x_+sr) && (y >= sr/2) && (y < y_+sr/2))
			{
				Char result = canvas[std::pair<int, int>(x-sr, y-sr/2)];
				if(result.fg == -1)
					result.fg = color1;
				if(result.bg == -1)
					result.bg = color2;
				return result;
			}
			if((x < 0) || (y < 0) || (x >= x_ + 2*sr) || (y >= y_ + sr))
				return Char::empty();
			return Char::half_blocks(col(x, y*2), col(x, y*2+1));
		}
		int Border::x(){ return x_ + 2*sr; }
		int Border::y(){ return y_ + sr; }
	}
}
