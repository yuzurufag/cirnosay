#include "picture.h"

#include "../palette.h"

namespace cirno_say
{
	namespace canvas
	{
		Picture::Picture(std::string file_name, const Palette &palette, bool mirror):picture(file_name, palette)
		{
			this->mirror = mirror;
		}
		Char Picture::getChar(int x, int y)
		{
			if(mirror)
				x = picture.x() - 1 - x;
			int c1 = picture.getPixel(x, y*2);
			int c2 = picture.getPixel(x, y*2+1);
			return Char::half_blocks(c1!=-1? c1: Char::TRANSPARENT, c2!=-1? c2: Char::TRANSPARENT);
		}
		int Picture::x()
		{
			return picture.x();
		}
		int Picture::y()
		{
			return (picture.y()+1)/2;
		}
		void Picture::setMaxX(int x)
		{
		}
		void Picture::setMaxY(int y)
		{
		}
	}
}
