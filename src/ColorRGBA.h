#ifndef COLOR_RGBA_HEADER
#define COLOR_RGBA_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	class ColorRGBA
	{
	public:
		sp_float Red;
		sp_float Green;
		sp_float Blue;
		sp_float Alpha;

		API_INTERFACE ColorRGBA()
		{
			Red = ZERO_FLOAT;
			Green = ZERO_FLOAT;
			Blue = ZERO_FLOAT;
			Alpha = ZERO_FLOAT;
		}

		API_INTERFACE ColorRGBA(sp_float red, sp_float green, sp_float blue, sp_float alpha)
		{
			Red = red;
			Green = green;
			Blue = blue;
			Alpha = alpha;
		}

		API_INTERFACE ColorRGBA normalize() 
		{
			const sp_float factor = 1.0f / 255.0f;

			return ColorRGBA(
				Red * factor,
				Green * factor,
				Blue * factor,
				Alpha * factor);
		}

		/// <summary>
		/// Get a index from the vector
		/// </summary>
		API_INTERFACE Vec4 toVec4()
		{
			return Vec4(Red, Green, Blue, Alpha);
		}

		/// <summary>
		/// Get a index component color from the color
		/// </summary>
		API_INTERFACE sp_float operator[](const sp_int index)
		{
			sp_assert(index >= 0 && index < 4, "IndexOutOfRangeException");
			return toVec4()[index];
		}

	};
}

#endif // !COLOR_RGBA_HEADER