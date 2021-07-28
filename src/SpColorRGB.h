#ifndef SP_COLOR_RGB_HEADER
#define SP_COLOR_RGB_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	class SpColorRGB
	{
	public:
		sp_float red, green, blue;

		/// <summary>
		/// Default constructor
		/// </summary>
		/// <returns></returns>
		API_INTERFACE inline SpColorRGB()
		{
		}

		/// <summary>
		/// Parametrized constructor
		/// </summary>
		/// <param name="red"></param>
		/// <param name="green"></param>
		/// <param name="blue"></param>
		/// <returns></returns>
		API_INTERFACE SpColorRGB(const sp_float red, const sp_float green, const sp_float blue)
		{
			this->red = red;
			this->green = green;
			this->blue = blue;
		}

		API_INTERFACE inline SpColorRGB normalize()
		{
			SP_CONSTEXPR sp_float inverse = 1.0f / 255.0f;
			return SpColorRGB(red * inverse, green * inverse, blue * inverse);
		}

		API_INTERFACE inline operator sp_float*()
		{
			return (sp_float*)this;
		}

	};

	const SpColorRGB SpColorRGBWhite(1.0f, 1.0f, 1.0f);
	const SpColorRGB SpColorRGBBlack(0.0f, 0.0f, 0.0f);
}

#endif // SP_COLOR_RGB_HEADER