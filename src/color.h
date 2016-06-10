#pragma once
#include <cstdint>

namespace cirno_say {

typedef std::int32_t Color;
namespace color
{
	static constexpr Color DEFAULT     = -1;
	static constexpr Color TRANSPARENT = -2;
	static constexpr Color AUTO        = -3;
	static constexpr Color INVALID     = -4;
}

Color parseColor(const char *s);

}
