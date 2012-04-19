#include <locale.h>
#include <errno.h>

#include <sstream>
#include <iterator>
#include <iostream>

#include "text.h"

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
			std::vector<std::vector<Char> > result;
			std::vector<Char> line;
			for(auto c = s.begin(); c < s.end(); c++)
			{
				if(*c == L'\n')
				{
					result.push_back(line);
					line.clear();
				}
				else if(*c == L'\e')
				{
					c++;
					if(*c == L'[')
					{
						int i = 0;
						int xterm_mode = 0;
						do
						{
							c++;
							if(*c == L'm' || *c == L';')
							{
								if(xterm_mode == 0)
								{
									if(i == 0)
									{
										bg = -1;
										fg = -1;
									}
									else if(i >= 30 && i <= 37)
										fg = i-30;
									else if(i >= 90 && i <= 97)
										fg = i-90+3;
									else if(i >= 40 && i <= 47)
										fg = i-40;
									else if(i == 38)
										xterm_mode = 1;
									else if(i == 48)
										xterm_mode = 2;
								}
								else
								{
									if(xterm_mode == 1 && i == 5)
										xterm_mode = 3;
									else if(xterm_mode == 2 && i == 5)
										xterm_mode = 4;
									else if(xterm_mode == 3)
									{
										fg = i; xterm_mode = 0;
									}
									else if(xterm_mode == 4)
									{
										bg = i; xterm_mode = 0;
									}
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
					line.push_back({fg, bg, *c});
				}
			}
			if(line.size() != 0)
			{
				//line.push_back({7, 0, L'%'});
				result.push_back(line);
			}
			return Text(result);
		}
		Char Text::operator[](const std::pair<int, int> &c)
		{
			int x = c.first;
			int y = c.second;
			if((y < 0) || ((size_t)y >= s.size()))
				return Char::empty();
			if((x < 0) || ((size_t)x >= s[y].size()))
				return Char::empty();
			return s[y][x];
		}
		int Text::x(){ return x_; }
		int Text::y(){ return s.size(); }
	}
}
