#ifndef SP_SIZE_HEADER
#define SP_SIZE_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	template<typename T>
	class SpSize
	{
	public:
		T width, height;

		API_INTERFACE SpSize()
		{
			x = T(0);
			y = T(0);
		}

		/// <summary>
		/// Get the aspect ratio
		/// </summary>
		API_INTERFACE sp_float aspectRatio()
		{
			return (sp_float)(width / height);
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T& operator[](sp_int index)
		{
			sp_assert(index >= 0 && index < 4);

			return toVec4()[index];
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T& operator[](sp_int index)
		{
			sp_assert(index >= ZERO_INT && index < TWO_INT);
			return *(this)[index];
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T& operator[](sp_uint index)
		{
			sp_assert(index >= ZERO_UINT && index < TWO_UINT);
			return *(this)[index];
		}

#ifdef ENV_64BITS
		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T& operator[](sp_size index)
		{
			sp_assert(index >= ZERO_SIZE && index < TWO_SIZE);
			return *(this)[index];
		}
#endif

	};

}

#endif // SP_SIZE_HEADER