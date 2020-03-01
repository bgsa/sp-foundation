#ifndef COLOR_RGB_HEADER
#define COLOR_RGB_HEADER

#include "SpectrumFoundation.h"

template<typename T>
class ColorRGB
{
public:
	T Red;
	T Green;
	T Blue;

	API_INTERFACE ColorRGB(T red, T green, T blue)
	{
		Red = red;
		Green = green;
		Blue = blue;
	}

	API_INTERFACE ColorRGB<sp_float> normalizeColor()
	{
		return ColorRGB<sp_float>(
			Red / 255.0f,
			Green / 255.0f,
			Blue / 255.0f);
	}
};

typedef ColorRGB<sp_float> ColorRGBf;
typedef ColorRGB<sp_uchar> ColorRGBc;

#endif // !COLOR_RGB+HEADER