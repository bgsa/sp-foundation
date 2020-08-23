#ifndef SP_POINT2_HEADER
#define SP_POINT2_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	template<typename T>
	class SpPoint2
	{
	public:
		T x, y;

		API_INTERFACE SpPoint2()
		{
			x = T(0);
			y = T(0);
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T& operator[](sp_int index)
		{
			sp_assert(index >= ZERO_INT && index < TWO_INT, "InvalidOperationException");
			return *(this)[index];
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T& operator[](sp_uint index)
		{
			sp_assert(index >= ZERO_UINT && index < TWO_UINT, "InvalidOperationException");
			return *(this)[index];
		}

#ifdef ENV_64BITS
		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T& operator[](sp_size index)
		{
			sp_assert(index >= ZERO_SIZE && index < TWO_SIZE, "InvalidOperationException");
			return *(this)[index];
		}
#endif

	};

}

#endif // SP_POINT2_HEADER