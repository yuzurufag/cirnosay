#pragma once

#include <string>

#include "../picture.h"
#include "canvas.h"

namespace cirno_say {

class Palette;

}

namespace cirno_say { namespace canvas {

class Picture : public Canvas
{
public:
	Picture(std::string file_name, const Palette &palette,
	        bool mirror, bool calc_dominant);
	Char getChar(int x, int y);
	int x();
	int y();
	void setMaxX(int x);
	void setMaxY(int y);
	Color dominant() const;
private:
	bool mirror;
	cirno_say::Picture picture;
	int x_, y_;
};

} }
