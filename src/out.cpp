#include "out.h"

namespace cirno_say
{
	Out::Out(canvas::Canvas &i)
	{
		b_ = -1;
		f_ = -1;
		for(int y = 0; y < i.y(); y++)
		{
			for(int x = 0; x < i.x(); x++)
			{
				Char c = i[std::pair<int, int>(x,y)];
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
					char c_[5] = {0};
					wchar_t wc[2] = {c.c, 0};
					wcstombs(c_, wc, 4);
					out << c_;
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
		if ((f == -1) && (b == -1))
		{
			if((b_ != f_) || (b_ != -1))
				out << "\e[m";
		}
		else if (b == -1)
		{
			if (b_ == -1)
			{
				if (f_ != f)
					out << "\e[38;5;" << f << "m";
			}
			else
				out << "\e[0;38;5;" << f << "m";
		}
		else if(f == -1)
		{
			if (f_ == -1)
			{
				if (b_ != b)
					out << "\e[48;5;" << b << "m";
			}
			else
				out << "\e[0;48;5;" << b << "m";
		}
		else
		{
			if ((f_ == f) && (b_ == b));
			else if (b_ == b)
				out << "\e[38;5;" << f << "m";
			else if (f_ == f)
				out << "\e[48;5;" << b << "m";
			else
				out << "\e[48;5;" << b << ";38;5;" << f <<  "m";
		}
		b_ = b;
		f_ = f;
	}
	void Out::put_pixels(int a, int b)
	{
		if ((a == -1) && (b == -1))
		{
			color(a, b);
			out << " ";
		}
		else if (b == -1)
		{
			color(b, a);
			out << "▀";
		}
		else
		{
			color(a, b);
			out << "▄";
		}
	}
	void Out::nl()
	{
		color(-1, -1);
		out << "\n";
	}
}
