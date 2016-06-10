#include "picture.h"

#include <Imlib2.h>
#include <assert.h>

#include "rgba.h"
#include "palette.h"

namespace cirno_say {

Picture::Picture(std::string file_name, const Palette &palette,
                 bool calc_dominant)
{
	Imlib_Image image = imlib_load_image(file_name.c_str());
	assert(image);
	imlib_context_set_image(image);
	x_ = imlib_image_get_width();
	y_ = imlib_image_get_height();
	i = new int[x_ * y_];
	uint32_t *img_data = (uint32_t *)imlib_image_get_data();
	for (int y = 0; y < y_; y++)
		for (int x = 0; x < x_; x++)
			i[x + y * x_] = palette.color(img_data[x + y * x_]);
	if (calc_dominant)
		dominant = palette.color(rgbaDominant(img_data, x_*y_));
	imlib_free_image();
}
Picture::~Picture()
{
	delete[] i;
}
int Picture::getPixel(int x, int y)
{
	if (x < 0 || x >= x_ || y < 0 || y >= y_)
		return -1;
	return i[x + y * x_];
}
int Picture::x()
{
	return x_;
}
int Picture::y()
{
	return y_;
}

}
