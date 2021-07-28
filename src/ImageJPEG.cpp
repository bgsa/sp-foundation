#include "ImageJPEG.h"

namespace NAMESPACE_FOUNDATION
{
	SpColorRGB ImageJPEG::getPixelRGB(sp_int x, sp_int y)
	{
		//The color of pixel (x, y) is stored at data[y * width + x], data[y * width + x + 1] and data[y * width + x + 2].

		return SpColorRGB(
			_data[y * _width + x],
			_data[y * _width + x + 1],
			_data[y * _width + x + 2]
		);
		
	}
}