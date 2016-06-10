#include "out.h"

namespace cirno_say {

Out::Out(canvas::Canvas &i)
{
	bg_ = fg_ = -1;
	bold_ = underline_ = false;
	for (int y = 0; y < i.y(); y++)
	{
		std::vector<Char> line;
		int spaces = 0;
		for (int x = 0; x < i.x(); x++)
		{
			Char c = i.getChar(x, y);
			if (c.c == L' ' && c.bg == -1)
				spaces++;
			else
			{
				for (int i = 0; i < spaces; i++)
					line.push_back(Char());
				spaces = 0;
				line.push_back(c);
			}
		}
		for (auto c : line)
			put(c);
		nl();
	}
}

std::string Out::to_s()
{
	return out.str();
}

void Out::put_raw(int bg, int fg, int bold, int underline, wchar_t c)
{
	std::vector<int> result;
	if ((fg == -1 && fg_ != -1) || (bg == -1 && bg_ != -1))
	{
		result.push_back(0);
		fg_ = bg_ = -1;
		bold_ = underline_ = false;
	}

	if (bg != -2 && bg != bg_)
	{
		if (bg < 8)
			result.push_back(40 + bg);
		else if (bg < 16)
			result.push_back(100 - 8 + bg);
		else if (bg < 256)
		{
			result.push_back(48);
			result.push_back(5);
			result.push_back(bg);
		}
		else
		{
			result.push_back(48);
			result.push_back(2);
			result.push_back((bg - 256) >> 16 & 0xFF);
			result.push_back((bg - 256) >> 8 & 0xFF);
			result.push_back((bg - 256) >> 0 & 0xFF);
		}
	}

	if (fg != -2 && fg != fg_)
	{
		if (fg < 8)
			result.push_back(30 + fg);
		else if (fg < 16)
			result.push_back(90 - 8 + fg);
		else if (fg < 256)
		{
			result.push_back(38);
			result.push_back(5);
			result.push_back(fg);
		}
		else
		{
			result.push_back(38);
			result.push_back(2);
			result.push_back((fg - 256) >> 16 & 0xFF);
			result.push_back((fg - 256) >> 8 & 0xFF);
			result.push_back((fg - 256) >> 0 & 0xFF);
		}
	}

	if (bold != -2 && bold != bold_)
		result.push_back(bold ? 1 : 22);

	if (underline != -2 && underline != underline_)
		result.push_back(underline ? 4 : 24);

	if (!result.empty())
	{
		out << "\e[";
		bool first = true;
		for (int i : result)
		{
			if (!first)
				out << ";";
			if (i != 0)
				out << i;
			first = false;
		}
		out << "m";
	}

	char c_[5] = {0};
	wchar_t wc[2] = {c, 0};
	wcstombs(c_, wc, 4);
	out << c_;

	if (bg != -2)
		bg_ = bg;
	if (fg != -2)
		fg_ = fg;
	if (bold != -2)
		bold_ = bold == 1;
	if (underline != -2)
		underline_ = underline == 1;
}

void Out::put(Char &c)
{
	if (c.c == WCHAR_LOWER_HALF_BLOCK || c.c == WCHAR_UPPER_HALF_BLOCK)
	{
		c.bg = c.bg == -1 ? color::TRANSPARENT : c.bg;
		c.fg = c.fg == -1 ? color::DEFAULT : c.fg;
		int t = c.c == WCHAR_LOWER_HALF_BLOCK ? c.bg : c.fg;
		int b = c.c == WCHAR_LOWER_HALF_BLOCK ? c.fg : c.bg;
		int td = t >= 0 ? t : -1;
		int bd = b >= 0 ? b : -1;
		if (t == color::TRANSPARENT)
			put_raw(-1, bd, c.bold, c.underline, WCHAR_LOWER_HALF_BLOCK);
		else if (b == color::TRANSPARENT)
			put_raw(-1, td, c.bold, c.underline, WCHAR_UPPER_HALF_BLOCK);
		else if (t == color::DEFAULT)
			put_raw(bd, -1, c.bold, c.underline, WCHAR_UPPER_HALF_BLOCK);
		else if (b == color::DEFAULT)
			put_raw(td, -1, c.bold, c.underline, WCHAR_LOWER_HALF_BLOCK);

		else if (b == t && bg_ == b)
			put_raw(-2, -2, c.bold, c.underline, L' ');
		else if (b == t && fg_ == b)
			put_raw(-2, -2, c.bold, c.underline, WCHAR_FULL_BLOCK);
		else if (b == t)
			put_raw(b, -2, c.bold, c.underline, L' ');
		else if (bg_ == b || fg_ == t)
			put_raw(b, t, c.bold, c.underline, WCHAR_UPPER_HALF_BLOCK);
		else if (fg_ == b || bg_ == t)
			put_raw(t, b, c.bold, c.underline, WCHAR_LOWER_HALF_BLOCK);
		else
			put_raw(t, b, c.bold, c.underline, WCHAR_LOWER_HALF_BLOCK);
	}
	else if (c.c == WCHAR_FULL_BLOCK)
	{
		if (c.fg != -1)
			put_raw(c.fg, -2, c.bold, c.underline, L' ');
		else
			put_raw(-2, -1, c.bold, c.underline, WCHAR_FULL_BLOCK);
	}
	else
	{
		bool space = c.c == L' ';
		put_raw(c.bg, space ? -2 : c.fg, space ? -2 : c.bold, c.underline, c.c);
	}
}

void Out::nl()
{
	fg_ = bg_ = -1;
	bold_ = false;
	out << "\e[m\n";
}

}
