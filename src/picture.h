#pragma once

#include <string>

#include "color.h"

namespace cirno_say {

struct Palette;

class Picture
{
public:
	Picture(std::string file_name, const Palette &palette, bool calc_dominant);
	~Picture();
	int getPixel(int x, int y);
	int x();
	int y();
    Color dominant;
private:
	int x_, y_;
	Color *i;
};

}
