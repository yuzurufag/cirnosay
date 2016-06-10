#include "rgba.h"

#include <iostream>
#include <algorithm>
#include <Imlib2.h>

namespace cirno_say {

static uint32_t diff(uint8_t a, uint8_t b)
{
	uint8_t d = a > b ? a-b : b-a;
	return d*d;
}

uint32_t rgbaDifference(Rgba a, Rgba b)
{
	return diff(a.r, b.r) + diff(a.g, b.g) + diff(a.b, b.b);
}

namespace {

struct Bucket
{
	Rgba base;
	uint32_t r, g, b, count;
	bool enabled;
};

struct Dominant
{
	Dominant(const uint32_t *img_data, size_t img_size);
	void step();
	Rgba result();

	static constexpr size_t count = 27;
	Bucket buckets[count];
	const uint32_t *img_data;
	size_t img_size;
};

}

Dominant::Dominant(const uint32_t *img_data, size_t img_size)
: img_data(img_data), img_size(img_size)
{
	for (auto &b : buckets)
	{
		b.r = b.g = b.b = b.count = 0;
		b.enabled = true;
	}
	uint8_t col[] = {0x40, 0x80, 0xc0};
	size_t i = 0;
	for (auto r : col)
	for (auto g : col)
	for (auto b : col)
		buckets[i++].base = {r, g, b, 0xff};
}

void Dominant::step()
{
	for (auto &b : buckets)
		b.r = b.g = b.b = b.count = 0;
	
	for (size_t i = 0; i < img_size; i++)
	{
		uint32_t c_raw = img_data[i];
		Rgba c =
		{
			(uint8_t)(c_raw >> 16),
			(uint8_t)(c_raw >>  8),
			(uint8_t)(c_raw >>  0),
			(uint8_t)(c_raw >> 24),
		};

		if (c.a <= 127)
			continue;

		Bucket *best = nullptr;
		uint32_t best_diff = 0;
		for (auto &b : buckets)
		{
			if (!b.enabled)
				continue;
			uint32_t diff = rgbaDifference(c, b.base);
			if (best == nullptr || diff < best_diff)
			{
				best = &b;
				best_diff = diff;
			}
		}

		best->r += c.r;
		best->g += c.g;
		best->b += c.b;
		best->count++;
	}

	for (auto &b : buckets)
	{
		if (b.count == 0)
			b.enabled = false;
		if (!b.enabled)
			continue;
		b.base.r = b.r / b.count;
		b.base.g = b.g / b.count;
		b.base.b = b.b / b.count;
	}
}

static uint16_t color_score(Rgba c)
{
	uint8_t min = std::min({c.r, c.g, c.b});
	return (uint16_t)c.r + c.g + c.b - min*3;
}

Rgba Dominant::result()
{
	Bucket *best = nullptr;
	uint32_t best_score = 0;
	for (auto &b : buckets) {
		if (!b.enabled)
			continue;
		uint32_t score = b.count * color_score(b.base);
		if (!best || score > best_score)
		{
			best = &b;
			best_score = score;
		}
	}
	if (!best)
		return {0, 0, 0, 0};
	return best->base;
}

Rgba rgbaDominant(const uint32_t *data, size_t size)
{
	Dominant d(data, size);
	for (int i = 0; i < 100; i++)
		d.step();
	return d.result();
}

}

#if 0
static void print_color(cirno_say::Rgba c) {
	std::cout
		<< "\e[48;2;"
		<< (unsigned)c.r << ';'
		<< (unsigned)c.g << ';'
		<< (unsigned)c.b << "m  \e[m";
}

int main(int argc, char **argv)
{
	using namespace cirno_say;
	for (int i = 1; i < argc; i++)
	{
		Imlib_Image image = imlib_load_image(argv[i]);
		imlib_context_set_image(image);
		auto size = imlib_image_get_width()
	        * imlib_image_get_height();
		auto c = rgbaDominant(imlib_image_get_data(), size);
		print_color(c);
		std::cout << " " << argv[i] << "\n";
	}
}
#endif
