#include "picture.h"

#include <assert.h>
#include <Imlib2.h>

namespace cirno_say
{
	Picture::Picture(std::string file_name, const Palette &palette)
	{
		Imlib_Image image = imlib_load_image(file_name.c_str());
		assert(image);
		imlib_context_set_image(image);
		x_ = imlib_image_get_width();
		y_ = imlib_image_get_height();
		i = new int[x_*y_];
		uint8_t* img_data = (uint8_t*)imlib_image_get_data();
		for(int y = 0; y < y_; y++)
			for(int x = 0; x < x_; x++)
			{
				uint8_t r = img_data[(x + y*x_)*4 + 2];
				uint8_t g = img_data[(x + y*x_)*4 + 1];
				uint8_t b = img_data[(x + y*x_)*4 + 0];
				uint8_t a = img_data[(x + y*x_)*4 + 3];
				i[x + y*x_] = palette.color(r, g, b, a);
			}
		imlib_free_image();
	}
	Picture::~Picture()
	{
		delete[] i;
	}
	int Picture::getPixel(int x, int y)
	{
		if(x < 0 || x >= x_ || y < 0 || y >= y_)
			return -1;
		return i[x + y*x_];
	}
	int Picture::x(){ return x_; }
	int Picture::y(){ return y_; }
}
