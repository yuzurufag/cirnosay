#include "color.h"

#include <cstring>

namespace cirno_say {

Color parseColor(const char *s)
{
	#define KEYWORD(kw, result) \
		if (!std::strcmp(s, kw) || (s[0] == kw[0] && s[1] == 0)) \
			return result
	KEYWORD("auto", color::AUTO);
	KEYWORD("default", color::DEFAULT);
	KEYWORD("transparent", color::TRANSPARENT);
	#undef KEYWORD

	auto len = std::strlen(s);

	if (len == 0)
		return color::INVALID;

	Color result = 0;

	if (len == 7 && *s == '#')
	{
		for (auto *c = s+1; *c; c++)
		{
			int d = *c;
			if (d >= '0' && d <= '9')
				d = d - '0';
			else if (d >= 'A' && d <= 'F')
				d = d - 'A' + 10;
			else if (d >= 'a' && d <= 'f')
				d = d - 'a' + 10;
			else
				return color::INVALID;
			result = result * 16 + d;
		}
		return result + 256;
	}

	for (auto *c = s; *c; c++)
		if (*c >= '0' && *c <= '9')
		{
			result = result*10 + *c - '0';
			if (result >= 256)
				return color::INVALID;
		}
		else
			return color::INVALID;

	return result;
}

}
