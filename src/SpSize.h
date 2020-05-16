#ifndef SP_POINT_HEADER
#define SP_POINT_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	template<typename T>
	class SpPoint
	{
	public:
		T x, y;

		API_INTERFACE SpPoint()
		{
			x = T(0);
			y = T(0);
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

#endif // SP_POINT_HEADER