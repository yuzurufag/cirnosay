#pragma once

#include <cstdint>
#include <cstddef>

namespace cirno_say {

struct Rgba
{
	uint8_t r, g, b, a;
	Rgba()
	: Rgba(0, 0, 0, 0)
	{}
	Rgba(uint32_t x)
	: Rgba(x >> 16, x>>8, x>>0, x>>24)
	{}
	Rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	: r(r), g(g), b(b), a(a)
	{}
};

uint32_t rgbaDifference(Rgba, Rgba);

Rgba rgbaDominant(const uint32_t *data, size_t size);

}
