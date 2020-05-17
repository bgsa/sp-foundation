#ifndef SP_POINT_HEADER
#define SP_POINT_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	template<typename T>
	class SpPoint3
	{
	public:
		T x, y, z;

		API_INTERFACE SpPoint3()
		{
			x = T(0);
			y = T(0);
			z = T(0);
		}

		API_INTERFACE SpPoint3(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T operator[](sp_int index) const
		{
			sp_assert(index >= ZERO_INT && index < THREE_UINT);
			return reinterpret_cast<const T*>(this)[index];
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T& operator[](sp_int index)
		{
			sp_assert(index >= ZERO_INT && index < THREE_UINT);
			return *(this)[index];
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T operator[](sp_uint index) const
		{
			sp_assert(index >= ZERO_UINT && index < THREE_UINT);
			return reinterpret_cast<const T*>(this)[index];
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T& operator[](sp_uint index)
		{
			sp_assert(index >= ZERO_UINT && index < THREE_UINT);
			return *(this)[index];
		}

#ifdef ENV_64BITS
		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T operator[](sp_size index) const
		{
			sp_assert(index >= ZERO_SIZE && index < THREE_UINT);
			return *(this)[index];
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T& operator[](sp_size index)
		{
			sp_assert(index >= ZERO_SIZE && index < THREE_UINT);
			return *(this)[index];
		}
#endif

	};

}

#endif // SP_POINT_HEADER