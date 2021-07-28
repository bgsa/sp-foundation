#include "ImageBMP.h"

#ifndef STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
	#define STBI_ONLY_BMP
	#define STB_IMAGE_WRITE_IMPLEMENTATION
	#include <stb/stb_image.h>
	#include <stb/stb_image_write.h>
#endif

namespace NAMESPACE_FOUNDATION
{
	SpColorRGB ImageBMP::getPixelRGB(sp_int x, sp_int y)
	{
		//The color of pixel (x, y) is stored at data[y * width + x], data[y * width + x + 1] and data[y * width + x + 2].
		return SpColorRGB(
			_data[y * _width + x          ],
			_data[y * _width + x + ONE_INT],
			_data[y * _width + x + TWO_INT]
		);
	}

	void ImageBMP::save(const sp_char* filename, sp_uchar* data, SpSize<sp_int> size)
	{
		stbi_write_bmp(filename, size.width, size.height, THREE_INT, data);
	}

	void ImageBMP::save(const sp_char* filename)
	{
		stbi_write_bmp(filename, _width, _height, THREE_INT, _data);
	}
}