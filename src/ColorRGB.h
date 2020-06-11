#ifndef COLOR_RGB_HEADER
#define COLOR_RGB_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	class ColorRGB
	{
	public:
		sp_float Red;
		sp_float Green;
		sp_float Blue;

		API_INTERFACE ColorRGB()
		{
			Red = ZERO_FLOAT;
			Green = ZERO_FLOAT;
			Blue = ZERO_FLOAT;
		}

		API_INTERFACE ColorRGB(sp_float red, sp_float green, sp_float blue)
		{
			Red = red;
			Green = green;
			Blue = blue;
		}

		API_INTERFACE inline ColorRGB normalizeColor()
		{
			SP_CONSTEXPR sp_float inverse = 1.0f / 255.0f;
			return ColorRGB(Red * inverse, Green * inverse, Blue * inverse);
		}

		API_INTERFACE inline operator sp_float*()
		{
			return (sp_float*)this;
		}

	};
}

#endif // !COLOR_RGB_HEADER