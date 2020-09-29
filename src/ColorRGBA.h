#ifndef COLOR_RGBA_HEADER
#define COLOR_RGBA_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	class ColorRGBA
	{
	public:
		sp_float red;
		sp_float green;
		sp_float blue;
		sp_float alpha;

		API_INTERFACE ColorRGBA()
		{
			this->red = ZERO_FLOAT;
			this->green = ZERO_FLOAT;
			this->blue = ZERO_FLOAT;
			this->alpha = ZERO_FLOAT;
		}

		API_INTERFACE ColorRGBA(sp_float red, sp_float green, sp_float blue, sp_float alpha)
		{
			this->red = red;
			this->green = green;
			this->blue = blue;
			this->alpha = alpha;
		}

		API_INTERFACE ColorRGBA normalize() 
		{
			const sp_float factor = 1.0f / 255.0f;

			return ColorRGBA(
				this->red * factor,
				this->green * factor,
				this->blue * factor,
				this->alpha * factor);
		}

		/// <summary>
		/// Get a index component color from the color
		/// </summary>
		API_INTERFACE sp_float operator[](const sp_int index)
		{
			sp_assert(index >= 0 && index < 4, "IndexOutOfRangeException");
			return ((sp_float*)this)[index];
		}

		/// <summary>
		/// Get a index component color from the color
		/// </summary>
		API_INTERFACE sp_float operator[](const sp_int index) const
		{
			sp_assert(index >= 0 && index < 4, "IndexOutOfRangeException");
			return ((sp_float*)this)[index];
		}

		/// <summary>
		/// Get a index component color from the color
		/// </summary>
		API_INTERFACE sp_float operator[](const sp_uint index)
		{
			sp_assert(index >= 0 && index < 4, "IndexOutOfRangeException");
			return ((sp_float*)this)[index];
		}

		/// <summary>
		/// Get a index component color from the color
		/// </summary>
		API_INTERFACE sp_float operator[](const sp_uint index) const
		{
			sp_assert(index >= 0 && index < 4, "IndexOutOfRangeException");
			return ((sp_float*)this)[index];
		}
	};
}

#endif // !COLOR_RGBA_HEADER