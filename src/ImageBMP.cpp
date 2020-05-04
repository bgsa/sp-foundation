#include "ImageBMP.h"

namespace NAMESPACE_FOUNDATION
{
	ColorRGB ImageBMP::getPixelRGB(sp_int x, sp_int y)
	{
		//The color of pixel (x, y) is stored at data[y * width + x], data[y * width + x + 1] and data[y * width + x + 2].
		return ColorRGB(
			_data[y * _width + x],
			_data[y * _width + x + 1],
			_data[y * _width + x + 2]
		);
	}
}