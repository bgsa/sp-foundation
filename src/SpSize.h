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
			width = T(0);
			height = T(0);
		}

		API_INTERFACE SpSize(T width, T height)
		{
			this->width = width;
			this->height = height;
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
		API_INTERFACE T operator[](sp_int index) const
		{
			sp_assert(index >= 0 && index < TWO_INT, "IndexOutOfRangeException");
			return *(this)[index];
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T& operator[](sp_int index)
		{
			sp_assert(index >= ZERO_INT && index < TWO_INT, "IndexOutOfRangeException");
			return *(this)[index];
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T operator[](sp_uint index) const
		{
			sp_assert(index >= ZERO_UINT && index < TWO_UINT, "IndexOutOfRangeException");
			return *(this)[index];
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T& operator[](sp_uint index)
		{
			sp_assert(index >= ZERO_UINT && index < TWO_UINT, "IndexOutOfRangeException");
			return *(this)[index];
		}

#ifdef ENV_64BITS
		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T operator[](sp_size index) const
		{
			sp_assert(index >= ZERO_SIZE && index < TWO_SIZE, "IndexOutOfRangeException");
			return *(this)[index];
	}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T& operator[](sp_size index)
		{
			sp_assert(index >= ZERO_SIZE && index < TWO_SIZE, "IndexOutOfRangeException");
			return *(this)[index];
		}
#endif

	};

}

#endif // SP_SIZE_HEADER