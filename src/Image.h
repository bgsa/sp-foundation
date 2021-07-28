#ifndef IMAGE_HEADER
#define IMAGE_HEADER

#include "SpectrumFoundation.h"
#include "SpColorRGB.h"

namespace NAMESPACE_FOUNDATION
{
	class Image 
	{
	protected:
		sp_int _width, _height;
		sp_uchar* _data;
		sp_uint colorFormat;
		
	public:

		API_INTERFACE Image()
		{
			_data = nullptr;
			_width = _height = ZERO_UINT;
			colorFormat = ZERO_UINT;
		}
		
		API_INTERFACE inline sp_int width()
		{
			return _width;
		}

		API_INTERFACE inline sp_int height()
		{
			return _height;
		}

		API_INTERFACE inline sp_uchar* data()
		{
			return _data;
		}

		API_INTERFACE inline sp_uint getColorFormat()
		{
			return colorFormat;
		}

		API_INTERFACE virtual SpColorRGB getPixelRGB(sp_int x, sp_int y) = 0;
	};
}

#endif // !IMAGE_HEADER