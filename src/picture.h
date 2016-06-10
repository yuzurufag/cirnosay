#pragma once

#include <string>

namespace cirno_say {

struct Palette;

class Picture
{
public:
	Picture(std::string file_name, const Palette &palette);
	~Picture();
	int getPixel(int x, int y);
	int x();
	int y();
private:
	int x_, y_;
	int *i;
};

}
