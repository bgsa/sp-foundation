#ifndef SP_ARRAY_HEADER
#define SP_ARRAY_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	template <typename T>
	class SpArray
		: public Object
	{
	protected:
		sp_uint _length;
		sp_uint _allocatedLength;
		T* _data;

		API_INTERFACE SpArray() { }

	public:
		
		API_INTERFACE SpArray(T* data, const sp_uint length, const sp_uint reserved = ZERO_UINT)
		{
			this->_data = data;
			this->_length = reserved;
			this->_allocatedLength = length;
		}
		API_INTERFACE SpArray(const sp_uint length, const sp_uint reserved = ZERO_UINT)
			: SpArray((T*)sp_mem_new_array(T,length), length, reserved)
		{
		}

		API_INTERFACE SpArray(const SpArray& source) // copy-constructor
			: SpArray((T*)sp_mem_new_array(T, source._length), source._length, source._allocatedLength)
		{
			std::memcpy(_data, source._data, source._allocatedLength * sizeof(T));
		}

		API_INTERFACE inline sp_uint length() const noexcept
		{
			return _length;
		}

		API_INTERFACE inline sp_bool isEmpty() const noexcept
		{
			return _length == ZERO_UINT;
		}

		API_INTERFACE inline sp_uint allocatedLength() const noexcept
		{
			return _allocatedLength;
		}

		API_INTERFACE inline T* data() noexcept
		{
			return _data;
		}

		API_INTERFACE inline void reserve(const sp_uint value)
		{
			sp_assert(value <= _allocatedLength, "IndexOutOfRangeException");
			_length = value;
		}

		API_INTERFACE inline void add(const T& value)
		{
			sp_assert(_length < _allocatedLength, "IndexOutOfRangeException");

			_data[_length++] = value;
		}

		API_INTERFACE inline T operator[](const sp_int index) const
		{
			sp_assert(index >= ZERO_INT && (sp_uint)index < _length, "IndexOutOfRangeException");
			return _data[index];
		}
		API_INTERFACE inline T& operator[](const sp_int index)
		{
			sp_assert(index >= ZERO_INT && (sp_uint)index < _length, "IndexOutOfRangeException");
			return _data[index];
		}

		API_INTERFACE inline T operator[](const sp_uint index) const
		{
			sp_assert(index >= ZERO_UINT && index < _length, "IndexOutOfRangeException");
			return _data[index];
		}
		API_INTERFACE inline T& operator[](const sp_uint index)
		{
			sp_assert(index >= ZERO_UINT && index < _length, "IndexOutOfRangeException");
			return _data[index];
		}

		API_INTERFACE inline T& get(const sp_uint index)
		{
			sp_assert(index >= ZERO_UINT && index < _length, "IndexOutOfRangeException");
			return _data[index];
		}

#ifdef ENV_64BITS
		API_INTERFACE inline T operator[](const sp_size index) const
		{
			sp_assert(index >= ZERO_SIZE && (sp_uint)index < _length, "IndexOutOfRangeException");
			return _data[index];
		}
		API_INTERFACE inline T& operator[](const sp_size index)
		{
			sp_assert(index >= ZERO_SIZE && (sp_uint)index < _length, "IndexOutOfRangeException");
			return _data[index];
		}
#endif

		API_INTERFACE inline virtual const sp_char* toString() override
		{
			return "SpArray";
		}

		friend void swap(SpArray& array1, SpArray& array2) noexcept
		{
			std::swap(array1._data, array2._data);
			std::swap(array1._length, array2._length);
			std::swap(array1._allocatedLength, array2._allocatedLength);
			std::swap(array1._firstPointer, array2._firstPointer);
		}

	};

	/// <summary>
	/// Check if the value parameter contains on list
	/// </summary>
	/// <param name="list">List of uint</param>
	/// <param name="listLength">Length of list</param>
	/// <param name="value">Value to be looked up</param>
	/// <returns>True if contains in list or else False</returns>
	API_INTERFACE inline sp_bool contains(sp_uint* list, sp_uint listLength, sp_uint value)
	{
		for (sp_uint i = 0; i < listLength; i++)
			if (list[i] == value)
				return true;

		return false;
	}

}

#endif // SP_ARRAY_HEADER
