#include "out.h"

namespace cirno_say
{
	Out::Out(canvas::Canvas &i)
	{
		b_ = f_ = -1;
		for(int y = 0; y < i.y(); y++)
		{
			std::vector<Char> line;
			int spaces = 0;
			for(int x = 0; x < i.x(); x++)
			{
				Char c = i.getChar(x,y);
				if(c.c == L' ' && c.bg == -1)
					spaces++;
				else
				{
					for(int i = 0; i < spaces; i++)
						line.push_back(Char::empty());
					spaces = 0;
					line.push_back(c);
				}
			}
			for(auto c : line)
			{
				if(c.c == L' ')
					put_pixels(c.bg, c.bg);
				else if(c.c == WCHAR_LOWER_HALF_BLOCK)
					put_pixels(c.bg, c.fg);
				else if(c.c == WCHAR_UPPER_HALF_BLOCK)
					put_pixels(c.fg, c.bg);
				else if(c.c == WCHAR_FULL_BLOCK)
					put_pixels(c.fg, c.fg);
				else
				{
					color(c.bg, c.fg);
					put_wchar_t(c.c);
				}
			}
			nl();
		}
	}

	std::string Out::to_s()
	{
		return out.str();
	}

	void Out::color(int b, int f)
	{
		if(f == -1 && b == -1)
		{
			if(b_ != f_ || b_ != -1)
				out << "\e[m";
		}
		else if(b == -1)
		{
			if(b_ == -1)
			{
				if(f_ != f)
					out << "\e[" << color_fg(f) << "m";
			}
			else
				out << "\e[0;" << color_fg(f) << "m";
		}
		else if(f == -1)
		{
			if(f_ == -1)
			{
				if(b_ != b)
					out << "\e[" << color_bg(b) << "m";
			}
			else
				out << "\e[0;" << color_bg(b) << "m";
		}
		else
		{
			if(f_ == f && b_ == b);
			else if(b_ == b)
				out << "\e[" << color_fg(f) << "m";
			else if(f_ == f)
				out << "\e[" << color_bg(b) << "m";
			else
				out << "\e[" << color_bg(b) << ";" << color_fg(f) << "m";
		}
		b_ = b;
		f_ = f;
	}

	std::string Out::color_fg(int f)
	{
		std::stringstream result;
		if(f < 8)
			result << 30+f;
		else if(f < 16)
			result << 90-8+f;
		else
			result << "38;5;" << f;
		return result.str();
	}

	std::string Out::color_bg(int b)
	{
		std::stringstream result;
		if(b < 8)
			result << 40+b;
		else if(b < 16)
			result << 100-8+b;
		else
			result << "48;5;" << b;
		return result.str();
	}

	void Out::put_pixels(int a, int b)
	{
		if(a == -1 && b == -1)
		{
			color(a, f_);
			put_wchar_t(L' ');
		}
		else if(a == -1)
		{
			color(a, b);
			put_wchar_t(WCHAR_LOWER_HALF_BLOCK);
		}
		else if(b == -1)
		{
			color(b, a);
			put_wchar_t(WCHAR_UPPER_HALF_BLOCK);
		}
		else
		{
			if(a == b)
			{
				if(a == f_)
					put_wchar_t(WCHAR_FULL_BLOCK);
				else
				{
					color(a, f_);
					put_wchar_t(L' ');
				}
			}
			else if(a == f_ && b == b_)
				put_wchar_t(WCHAR_UPPER_HALF_BLOCK);
			else if(a == b_ && b == f_)
				put_wchar_t(WCHAR_LOWER_HALF_BLOCK);
			else
			{
				color(a, b);
				put_wchar_t(WCHAR_LOWER_HALF_BLOCK);
			}
		}
	}

	void Out::put_wchar_t(const wchar_t &c)
	{
		char c_[5] = {0};
		wchar_t wc[2] = {c, 0};
		wcstombs(c_, wc, 4);
		out << c_;
	}

	void Out::nl()
	{
		color(-1, -1);
		out << "\n";
	}
}
