#include "border_simple.h"

#include <algorithm>

namespace cirno_say
{
	namespace canvas
	{
		int BorderSimple::col(int x, int y)
		{
			int width = this->x();
			if(x < arrow_size && y < arrow_position)
				return -1;
			if(x < arrow_size && y == arrow_position)
				return bg;
			if(x < arrow_size+1 && x && y == arrow_position+1)
				return fg;
			if(x < arrow_size+1 && x && x + arrow_position == y)
				return fg;
			if(x < arrow_size && x + arrow_position + 3 > y)
				return bg;
			if(x < arrow_size && x + arrow_position + 3 <= y)
				return -1;
			if((y == 1 || y == height*2-2) && x > arrow_size+1 )
			{
				if(x >= width-2)
					return bg;
				return fg;
			}
			if(y >= 2 && y < height*2-2 && x == arrow_size+1 &&
				(y > arrow_position + arrow_size || y <= arrow_position ))
				return fg;
			if(y >= 2 && y < height*2-2 && x == width-2)
				return fg;
			if((y == 0 || y == height*2-1) && (x == width-1 || x == arrow_size))
				return -1;
			return bg;
		}
		BorderSimple::BorderSimple(Canvas *canvas,int fg, int bg, bool mirror): canvas(*canvas)
		{
			this->fg = fg;
			this->bg = bg;
			this->pad_x = 2;
			this->pad_y = 1;
			this->arrow_size = std::min(6, canvas->y()+2);
			this->arrow_position = std::min(4, canvas->y() + 1);
			this->mirror = mirror;

			this->width = canvas->x() + 2*pad_x + arrow_size + 4;
			this->height = canvas->y() + 2 + 2*pad_y;
		}
		Char BorderSimple::operator[](const std::pair<int, int> &c)
		{
			int width = this->x();
			int x = mirror? width-c.first-1: c.first;
			int y = c.second;
			if(x < 0 || x >= width || y < 0 || y >= height)
				return Char::empty();
			if(x >= arrow_size + pad_x + 2 && x < width - pad_x - 2 &&
				y >= 1 + pad_y && y < height - pad_y - 1)
			{
				if(mirror)
					x = width - x - 1 + arrow_size;	
				Char result = canvas[std::pair<int, int>(x - arrow_size - pad_x - 2, y - pad_y - 1)];
				result.fg = result.fg==-1 ? fg : result.fg;
				result.bg = result.bg==-1 ? bg : result.bg;
				return result;
			}
			return Char::half_blocks(col(x, y*2), col(x, y*2+1));
		}
		int BorderSimple::x(){ return (max_width != -1 && width>max_width)?max_width:width; }
		int BorderSimple::y(){ return height; }
		void BorderSimple::setMaxX(int x)
		{
			max_width = x;
			canvas.setMaxX(x - 2*pad_x - arrow_size + 4);

			this->arrow_size = std::min(6, canvas.y()+2);
			this->arrow_position = std::min(4, canvas.y() + 1);

			this->width = canvas.x() + 2*pad_x + arrow_size + 4;
			this->height = canvas.y() + 2 + 2*pad_y;
		}
	}
}
