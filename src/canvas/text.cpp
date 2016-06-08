#include <locale.h>
#include <errno.h>

#include <sstream>
#include <iterator>
#include <iostream>

#include "text.h"

struct XtermMode {
	enum What {
		bg,
		fg
	} what;
	enum Mode {
		none,
		start,
		color256,
		color24_r,
		color24_g,
		color24_b,
	} mode;

	XtermMode(What what = bg, Mode mode = none) : what(what), mode(mode)
	{}
};

namespace cirno_say
{
	namespace canvas
	{
		Text::Text()
		{
			x_ = 0;
		}
		Text::Text(const std::vector<std::vector<Char> > s)
		{
			this->s = s;
			x_ = 0;
			for(auto l: s)
				if ((size_t)x_ < l.size())
					x_ = l.size();
		}
		Text Text::from_wstring(const std::wstring &s)
		{
			setlocale(LC_ALL, "");
			int bg = -1;
			int fg = -1;
			int color = 0;
			bool bold = false;
			bool underline = false;
			std::vector<std::vector<Char> > result;
			std::vector<Char> line;
			for(auto c = s.begin(); c < s.end(); c++)
			{
				if(*c == L'\n')
				{
					result.push_back(line);
					line.clear();
				}
				else if(*c == L'\t')
				{
					line.push_back(Char(L' ', fg, bg));
					while(line.size() % 8 != 0)
						line.push_back(Char(L' ', fg, bg));
				}
				else if(*c == L'\e')
				{
					c++;
					if(*c == L'[')
					{
						int i = 0;
						XtermMode xterm_mode;
						do
						{
							c++;
							if(*c == L'm' || *c == L';')
							{
								switch (xterm_mode.mode) {
								case XtermMode::none:
									if(i == 0)
									{
										bg = fg = -1;
										bold = underline = false;
									}
									else if(i == 1)
										bold = true;
									else if(i == 4)
										underline = true;
									else if(i == 22)
										bold = false;
									else if(i == 24)
										underline = false;
									else if(i >= 30 && i <= 37)
										fg = i-30;
									else if(i >= 90 && i <= 97)
										fg = i-90+8;
									else if(i >= 40 && i <= 47)
										bg = i-40;
									else if(i >= 100 && i <= 107)
										bg = i-100+8;
									else if(i == 38)
										xterm_mode = XtermMode(
												XtermMode::fg,
												XtermMode::start);
									else if(i == 48)
										xterm_mode = XtermMode(
												XtermMode::bg,
												XtermMode::start);
									break;
								case XtermMode::start:
									if(i == 5)
										xterm_mode.mode = XtermMode::color256;
									else if(i == 2)
										xterm_mode.mode = XtermMode::color24_r;
									break;
								case XtermMode::color256:
									if (xterm_mode.what == XtermMode::fg)
										fg = i;
									else
										bg = i;
									xterm_mode = XtermMode();
									break;
								case XtermMode::color24_r:
									color = i & 0xff;
									xterm_mode.mode = XtermMode::color24_g;
									break;
								case XtermMode::color24_g:
									color = color*256 | (i&0xff);
									xterm_mode.mode = XtermMode::color24_b;
									break;
								case XtermMode::color24_b:
									color = color*256 | (i&0xff);
									xterm_mode.mode = XtermMode::none;
									if (xterm_mode.what == XtermMode::fg)
										fg = color;
									else
										bg = color;
									break;
								}
								i = 0;
							}
							else if(*c >= L'0' || *c <= L'9')
							{
								i = i*10 + (int)(*c - L'0');
							}
						} while(*c != L'm' && c != s.end());
					}
				}
				else
				{
					line.push_back(Char(*c, fg, bg, bold, underline));
				}
			}
			if(line.size() != 0)
			{
				//line.push_back({7, 0, L'%'});
				result.push_back(line);
			}
			return Text(result);
		}
		Char Text::getChar(int x, int y)
		{
			if((y < 0) || ((size_t)y >= s.size()))
				return Char();
			if((x < 0) || ((size_t)x >= s[y].size()))
				return Char();
			return s[y][x];
		}
		int Text::x(){ return x_; }
		int Text::y(){ return s.size(); }
		void Text::setMaxX(int x)
		{
			if(x == -1)
				return;
			auto s_ = s;
			s.clear();
			for(auto line : s_)
			{
				for(auto c = line.begin(); c <= line.end(); c += x)
					if(c + x < line.end())
						s.push_back(std::vector<Char>(c, c + x));
					else
						s.push_back(std::vector<Char>(c, line.end()));
			}
		}
	}
}
