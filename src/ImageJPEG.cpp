#include "ImageJPEG.h"

ColorRGBc ImageJPEG::getPixelRGB(sp_int x, sp_int y)
{
	sp_int width = getWidth();

	ColorRGBc color(
		data[y * width + x],
		data[y * width + x + 1],
		data[y * width + x + 2]
	);
	//The color of pixel (x, y) is stored at data[y * width + x], data[y * width + x + 1] and data[y * width + x + 2].

	return color;
}
