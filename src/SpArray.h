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
			: SpArray((T*) sp_mem_calloc(length, sizeof(T)), length, reserved)
		{
		}

		API_INTERFACE SpArray(const SpArray& source) // copy-constructor
			: SpArray((T*)sp_mem_calloc(source._length, sizeof(T)), source._length, source._allocatedLength)
		{
			std::memcpy(_data, source._data, source._allocatedLength * sizeof(T));
		}

		API_INTERFACE inline sp_uint length() noexcept
		{
			return _length;
		}

		API_INTERFACE inline sp_bool isEmpty() noexcept
		{
			return _length == ZERO_UINT;
		}

		API_INTERFACE inline sp_uint allocatedLength() noexcept
		{
			return _allocatedLength;
		}

		API_INTERFACE inline T* data() const noexcept
		{
			return _data;
		}

		API_INTERFACE inline void reserve(const sp_uint value)
		{
			assert(value <= _allocatedLength);
			_length = value;
		}

		API_INTERFACE inline virtual void add(const T& value)
		{
			assert(_length < _allocatedLength);

			_data[_length++] = value;
		}

		API_INTERFACE inline T operator[](const sp_int index) const
		{
			assert(index >= ZERO_INT && (sp_uint)index < _length);
			return _data[index];
		}
		API_INTERFACE inline T& operator[](const sp_int index)
		{
			assert(index >= ZERO_INT && (sp_uint)index < _length);
			return _data[index];
		}

		API_INTERFACE inline T operator[](const sp_uint index) const
		{
			assert(index >= ZERO_UINT && index < _length);
			return _data[index];
		}
		API_INTERFACE inline T& operator[](const sp_uint index)
		{
			assert(index >= ZERO_UINT && index < _length);
			return _data[index];
		}

#ifdef ENV_64BITS
		API_INTERFACE inline T operator[](const sp_size index) const
		{
			assert(index >= ZERO_SIZE && (sp_uint)index < _length);
			return _data[index];
		}
		API_INTERFACE inline T& operator[](const sp_size index)
		{
			assert(index >= ZERO_SIZE && (sp_uint)index < _length);
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

}

#endif // SP_ARRAY_HEADER
