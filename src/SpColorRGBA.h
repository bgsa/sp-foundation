#ifndef SP_COLOR_RGBA_HEADER
#define SP_COLOR_RGBA_HEADER

#include "SpectrumFoundation.h"

#define SP_COLOR_NORMALIZE_FACTOR (0.00392156f)

namespace NAMESPACE_FOUNDATION
{
	class SpColorRGBA
	{
	public:
		sp_float red, green, blue, alpha;

		/// <summary>
		/// Default constructor
		/// </summary>
		/// <returns></returns>
		API_INTERFACE inline SpColorRGBA()
		{
		}

		/// <summary>
		/// Constructor with parameters
		/// </summary>
		/// <param name="red"></param>
		/// <param name="green"></param>
		/// <param name="blue"></param>
		/// <param name="alpha"></param>
		/// <returns></returns>
		API_INTERFACE inline SpColorRGBA(const sp_float red, const sp_float green, const sp_float blue, const sp_float alpha)
		{
			this->red = red;
			this->green = green;
			this->blue = blue;
			this->alpha = alpha;
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

#ifdef ENV_64BITS

		/// <summary>
		/// Get a index component color from the color
		/// </summary>
		API_INTERFACE sp_float operator[](const sp_size index)
		{
			sp_assert(index >= 0 && index < 4, "IndexOutOfRangeException");
			return ((sp_float*)this)[index];
		}

		/// <summary>
		/// Get a index component color from the color
		/// </summary>
		API_INTERFACE sp_float operator[](const sp_size index) const
		{
			sp_assert(index >= 0 && index < 4, "IndexOutOfRangeException");
			return ((sp_float*)this)[index];
		}

#endif

	};

	const SpColorRGBA SpColorRGBAWhite(1.0f, 1.0f, 1.0f, 1.0f);
	const SpColorRGBA SpColorRGBABlack(0.0f, 0.0f, 0.0f, 1.0f);
	const SpColorRGBA SpColorRGBARed(1.0f, 0.0f, 0.0f, 1.0f);
	const SpColorRGBA SpColorRGBAGreen(0.0f, 1.0f, 0.0f, 1.0f);
	const SpColorRGBA SpColorRGBABlue(0.0f, 0.0f, 1.0f, 1.0f);

	/// <summary>
	/// Normalize the color in decimal to unit
	/// </summary>
	/// <param name="color">Color</param>
	/// <returns>color parameter</returns>
	API_INTERFACE inline void normalize(SpColorRGBA& color)
	{
		const sp_float factor = NAMESPACE_FOUNDATION::div(1.0f, 255.0f);

		color.red *= factor;
		color.green *= factor;
		color.blue *= factor;
		color.alpha *= factor;
	}

	/// <summary>
	/// Normalize the color in decimal to unit
	/// </summary>
	/// <param name="color">Color</param>
	/// <returns>color parameter</returns>
	API_INTERFACE inline void normalize(const SpColorRGBA& input, SpColorRGBA& output)
	{
		output.red = input.red * SP_COLOR_NORMALIZE_FACTOR;
		output.green = input.green * SP_COLOR_NORMALIZE_FACTOR;
		output.blue = input.blue * SP_COLOR_NORMALIZE_FACTOR;
		output.alpha = input.alpha * SP_COLOR_NORMALIZE_FACTOR;
	}

	/// <summary>
	/// Convert the color in unit to decimal
	/// </summary>
	/// <param name="input">Input Color</param>
	/// <param name="output">Output Color</param>
	/// <returns>output parameter</returns>
	API_INTERFACE inline void decimal(SpColorRGBA& color)
	{
		color.red *= 255.0f;
		color.green *= 255.0f;
		color.blue *= 255.0f;
		color.alpha *= 255.0f;
	}

	/// <summary>
	/// Convert the color in unit to decimal
	/// </summary>
	/// <param name="input">Input Color</param>
	/// <param name="output">Output Color</param>
	/// <returns>output parameter</returns>
	API_INTERFACE inline void decimal(const SpColorRGBA& input, SpColorRGBA& output)
	{
		output.red = input.red * 255.0f;
		output.green = input.green * 255.0f;
		output.blue = input.blue * 255.0f;
		output.alpha = input.alpha * 255.0f;
	}

}

#endif // SP_COLOR_RGBA_HEADER