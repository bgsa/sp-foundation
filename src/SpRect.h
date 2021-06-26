#ifndef SP_RECT_HEADER
#define SP_RECT_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	template<typename T>
	class SpRect
	{
	public:
		T x, y, width, height;

		API_INTERFACE inline SpRect()
		{
		}

		API_INTERFACE inline SpRect(const T x, const T y, const T width, const T height)
		{
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
		}

		/// <summary>
		/// Get the aspect ratio
		/// </summary>
		API_INTERFACE inline sp_float aspectRatio() const
		{
			return (sp_float)(width / height);
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T operator[](const sp_int index) const
		{
			sp_assert(index >= 0 && index < TWO_INT, "IndexOutOfRangeException");
			return *(this)[index];
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T& operator[](const sp_int index)
		{
			sp_assert(index >= ZERO_INT && index < TWO_INT, "IndexOutOfRangeException");
			return *(this)[index];
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T operator[](const sp_uint index) const
		{
			sp_assert(index >= ZERO_UINT && index < TWO_UINT, "IndexOutOfRangeException");
			return *(this)[index];
		}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T& operator[](const sp_uint index)
		{
			sp_assert(index >= ZERO_UINT && index < TWO_UINT, "IndexOutOfRangeException");
			return *(this)[index];
		}

#ifdef ENV_64BITS
		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T operator[](const sp_size index) const
		{
			sp_assert(index >= ZERO_SIZE && index < TWO_SIZE, "IndexOutOfRangeException");
			return *(this)[index];
	}

		/// <summary>
		/// Get a index of component
		/// </summary>
		API_INTERFACE T& operator[](const sp_size index)
		{
			sp_assert(index >= ZERO_SIZE && index < TWO_SIZE, "IndexOutOfRangeException");
			return *(this)[index];
		}
#endif

	};

}

#endif // SP_RECT_HEADER