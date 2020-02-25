#pragma once

#include "apollo.h"

template<typename T>
class ColorRGBA
{
public:
	T Red;
	T Green;
	T Blue;
	T Alpha;

	API_INTERFACE ColorRGBA()
	{
		Red = T(0);
		Green = T(0);
		Blue = T(0);
		Alpha = T(1);
	}

	API_INTERFACE ColorRGBA(T red, T green, T blue, T alpha) 
	{
		Red = red;
		Green = green;
		Blue = blue;
		Alpha = alpha;
	}

	API_INTERFACE ColorRGBA<sp_float> normalizeColor() 
	{
		return ColorRGBA<sp_float>(
			Red / 255.0f,
			Green / 255.0f,
			Blue / 255.0f,
			Alpha / 255.0f);
	}

	/// <summary>
	/// Get a index from the vector
	/// </summary>
	API_INTERFACE Vec4<T> toVec4()
	{
		return Vec4<T>{ Red, Green, Blue, Alpha };
	}

	/// <summary>
	/// Get a index component color from the color
	/// </summary>
	API_INTERFACE T& operator[](int index)
	{
		assert(index >= 0 && index < 4);

		return toVec4()[index];
	}

};

typedef ColorRGBA<sp_float> ColorRGBAf;
typedef ColorRGBA<sp_uchar> ColorRGBAc;