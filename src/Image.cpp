#include "Image.h"

namespace NAMESPACE_FOUNDATION
{
	Image::Image() {
	}

	sp_int Image::getWidth() 
	{
		return width;
	}

	sp_int Image::getHeight()
	{
		return height;
	}

	sp_uchar* Image::getData() 
	{
		return data;
	}

	sp_uint Image::getColorFormat()
	{
		return colorFormat;
	}

	Image::~Image() 
	{
		if (data != nullptr)
			delete[] data;
	}
}