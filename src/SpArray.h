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
		
		API_INTERFACE explicit SpArray(T* data, const sp_size length)
		{
			this->_data = data;
			this->_length = ZERO_UINT;
			this->_allocatedLength = length;
		}
		API_INTERFACE explicit SpArray(const sp_uint length)
			: SpArray((T*)sp_mem_alloc(length * sizeof(T)), length)
		{
		}

		API_INTERFACE SpArray(const SpArray& source) // copy-constructor
		{
			_data = sp_mem_new(T);
			std::memcpy(_data, source._data, source._allocatedLength * sizeof(T));

			_length = source._length;
			_allocatedLength = source._allocatedLength;
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

		API_INTERFACE inline T& data() noexcept
		{
			return _data;
		}

		API_INTERFACE inline void add(const T& value)
		{
			assert(_length < _allocatedLength);

			_data[_length++] = value;
		}

		API_INTERFACE inline void set(const sp_uint index, T value)
		{
			assert(index < _length);

			_data[index] = value;
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

		API_INTERFACE inline virtual void dispose() override
		{
			if (_data != NULL)
			{
				if (std::is_pointer<T>::value)
					for (sp_uint i = _length; i != ZERO_UINT; i--)
						//sp_mem_release(&_data + i - ONE_UINT);
						sp_mem_delete(_data, T);

				sp_mem_release(_data);
			}
		}

		API_INTERFACE ~SpArray()
		{
			dispose();
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
