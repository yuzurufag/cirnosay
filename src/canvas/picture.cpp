#include "picture.h"

#include "../palette.h"

namespace cirno_say
{
	namespace canvas
	{
		Picture::Picture(std::string file_name, const Palette &palette):picture(file_name, palette)
		{
		}
		Char Picture::operator[](const std::pair<int, int> &c)
		{
			int c1 = picture[std::pair<int, int>(c.first, c.second*2)];
			int c2 = picture[std::pair<int, int>(c.first, c.second*2+1)];
			return Char::half_blocks(c1, c2);
		}
		int Picture::x()
		{
			return picture.x();
		}
		int Picture::y()
		{
			return (picture.y()+1)/2;
		}
	}
}
