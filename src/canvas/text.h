#pragma once

#include <string>
#include <vector>

#include "canvas.h"

namespace cirno_say { namespace canvas {

class Text : public Canvas
{
public:
	Text();
	Text(std::vector<std::vector<Char>> s);
	static Text from_wstring(const std::wstring &s);
	Char getChar(int x, int y);
	int x();
	int y();
	void setMaxX(int x);
	// void setMaxY(int y);
private:
	std::vector<std::vector<Char>> s;
	int x_;
};

} }
