#include "utils.h"

#include <iostream>
#include <iterator>

namespace cirno_say
{
	std::wstring concat_cstrings(char **c)
	{
		std::string s = *c++;
		while(*c != NULL)
			s += std::string(" ") + *c++;
		wchar_t buf[s.size()];
		size_t num_chars = mbstowcs(buf, s.c_str(), s.size() );
		return std::wstring(buf, num_chars);
	}

	std::wstring read_stdin()
	{
		std::wcin >> std::noskipws;
		std::istream_iterator<wchar_t, wchar_t> it(std::wcin);
		std::istream_iterator<wchar_t, wchar_t> end;
		return std::wstring(it, end);
	}
}
