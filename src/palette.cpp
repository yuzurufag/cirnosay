#include "palette.h"

#include <assert.h>
#include <Imlib2.h>

namespace cirno_say
{
	Palette::Palette(const std::string &file_name)
	{
		Imlib_Image image = imlib_load_image(file_name.c_str());
		assert(image);
		imlib_context_set_image(image);
		pal_size = imlib_image_get_width() * imlib_image_get_height();
		//assert(pal_size == 256);
		uint8_t* img_data = (uint8_t*)imlib_image_get_data();
		pal_r = new uint8_t[pal_size];
		pal_g = new uint8_t[pal_size];
		pal_b = new uint8_t[pal_size];
		for(size_t i = 0; i < pal_size; i++)
		{
			pal_r[i] = img_data[i*4+2];
			pal_g[i] = img_data[i*4+1];
			pal_b[i] = img_data[i*4+0];
		}
		imlib_free_image();
	}
	Palette::~Palette() {
		delete[] pal_r;
		delete[] pal_g;
		delete[] pal_b;
	}
	int Palette::color(int r, int g, int b, int a) const
	{
		if(a < 127)
			return -1;

		int best = 0;
		int best_result = 256*256*3;
		for(size_t i = 0; i < pal_size; i++)
		{
			int result =
				(pal_r[i] - r)*(pal_r[i] - r) +
				(pal_g[i] - g)*(pal_g[i] - g) +
				(pal_b[i] - b)*(pal_b[i] - b)
			;
			if(result < best_result)
			{
				best_result = result;
				best = i;
			}
		}

		return best;
	}
}
