#ifndef SP_STRING_HEADER
#define SP_STRING_HEADER

#include "SpectrumFoundation.h"
#include "SpArray.h"

namespace NAMESPACE_FOUNDATION
{
#define SP_DEFAULT_STRING_LENGTH 255
#define SP_DEFAULT_STRING_SIZE   256
	
	class SpArrayOfString;

	class SpString
		: public Object
	{
	private:
		sp_uint _allocatedLength;
		sp_uint _length;
		sp_char* _data;

		friend class SpText;
		friend class SpArrayOfString;

	public:
		
		API_INTERFACE SpString() 
		{
			_length = SP_DEFAULT_STRING_LENGTH;
			_allocatedLength = SP_DEFAULT_STRING_SIZE;
			_data = (sp_char*)sp_mem_alloc(SP_DEFAULT_STRING_SIZE);
		}

		API_INTERFACE SpString(const sp_uint length, const sp_uint reserved = ZERO_UINT) 
		{
			assert(length >= reserved);

			_length = reserved;
			_allocatedLength = length + ONE_UINT;
			_data = (sp_char*) sp_mem_alloc(_allocatedLength);
			_data[length] = END_OF_STRING;
		}

		API_INTERFACE SpString(const sp_char* str) // implicit conversion
		{
			_length = std::strlen(str);
			_allocatedLength = _length + ONE_UINT;
			_data = (sp_char*)sp_mem_alloc(_allocatedLength);
			std::memcpy(_data, str, _allocatedLength);
		}

		API_INTERFACE SpString(const SpString& source)
		{
			_length = source._length;
			_allocatedLength = source._allocatedLength;
			_data = (sp_char*)sp_mem_alloc(_allocatedLength);
			std::memcpy(_data, source._data, _allocatedLength * SIZEOF_CHAR);
		}

		API_INTERFACE SpString& operator=(sp_char* source)
		{
			if (this->_data != source) //self assignment
			{
				_length = std::strlen(source);
				_allocatedLength = _length + ONE_UINT;
				_data = source;
			}

			return *this;
		}

		API_INTERFACE SpString& operator=(const SpString& source)
		{
			if (this != &source) //self assignment
			{
				_length = source._length;
				_allocatedLength = source._allocatedLength;
				_data = source._data;
			}

			return *this;
		}

		API_INTERFACE inline void reserve(const sp_uint value)
		{
			assert(value <= _allocatedLength);
			_length = value;
		}

		API_INTERFACE inline sp_uint length() const
		{
			return _length;
		}

		API_INTERFACE inline sp_uint allocatedLength()
		{
			return _allocatedLength;
		}

		API_INTERFACE inline sp_uint count(const sp_char character)
		{
			sp_uint counter = ZERO_UINT;

			for (sp_uint i = ZERO_SIZE; i < _length; i++)
				if (_data[i] == character)
					counter++;

			return counter;
		}

		API_INTERFACE inline sp_uint indexOf(const sp_char character)
		{
			for (sp_uint i = ZERO_SIZE; i < _length; i++)
				if (_data[i] == character)
					return i;

			return ZERO_UINT;
		}

		API_INTERFACE inline void add(const sp_char character) noexcept
		{
			_data[_length++] = character;
		}

		API_INTERFACE inline void clear() noexcept
		{
			std::memset(_data, ' ', _allocatedLength);
			_length = ZERO_SIZE;
		}

		API_INTERFACE SpArrayOfString* split(const sp_char separator);

		API_INTERFACE inline sp_bool startWith(const sp_char character) const
		{
			return _data[ZERO_UINT] == character;
		}
		API_INTERFACE inline sp_bool startWith(const sp_char* characteres) const
		{
			sp_uint charLength = std::strlen(characteres);

			for (sp_uint j = 0; j < charLength; j++)
				if (_data[j] != characteres[j])
					return false;

			return true;
		}

		API_INTERFACE inline sp_char operator[](const sp_int index) const
		{
			assert(index >= ZERO_INT && (sp_uint)index < _length);
			return _data[index];
		}
		API_INTERFACE inline sp_char& operator[](const sp_int index)
		{
			assert(index >= ZERO_INT && (sp_uint)index < _length);
			return _data[index];
		}

		API_INTERFACE inline sp_char operator[](const sp_uint index) const
		{
			assert(index >= ZERO_UINT && index < _length);
			return _data[index];
		}
		API_INTERFACE inline sp_char& operator[](const sp_uint index)
		{
			assert(index >= ZERO_UINT && index < _length);
			return _data[index];
		}

#ifdef ENV_64BITS
		API_INTERFACE inline sp_char operator[](const sp_size index) const
		{
			assert(index >= ZERO_SIZE && (sp_uint)index < _length);
			return _data[index];
		}
		API_INTERFACE inline sp_char& operator[](const sp_size index)
		{
			assert(index >= ZERO_SIZE && (sp_uint)index < _length);
			return _data[index];
		}
#endif
		
		template <typename T>
		API_INTERFACE inline T to()
		{
			return (T)_data;
		}
		template <>
		API_INTERFACE inline sp_double to()
		{
			return std::atof(_data);
		}
		template <>
		API_INTERFACE inline sp_float to<>()
		{
			return (sp_float)std::atof(_data);
		}
		template <>
		API_INTERFACE inline sp_int to()
		{
			return std::atoi(_data);
		}
		template <>
		API_INTERFACE inline sp_long to()
		{
			return std::atol(_data);
		}
#ifdef  ENV_64BITS
		template <>
		API_INTERFACE inline sp_longlong to()
		{
			return std::atoll(_data);
		}
#endif

		API_INTERFACE operator sp_char*() const
		{ 
			return _data; 
		}

		API_INTERFACE virtual const sp_char* toString() override
		{
			return _data;
		}

		API_INTERFACE virtual void dispose() override
		{
			if (_data != NULL)
			{
				sp_mem_release(_data);
				_data = NULL;
				//std::memset(_data, ZERO_INT, _allocatedLength + nextDivisorOf_(_allocatedLength,SIZEOF_WORD));
				//_length = ZERO_UINT;
				//_allocatedLength = ZERO_UINT;
			}
		}

		~SpString()
		{
			dispose();
		}

		friend void swap(SpString& string1, SpString& string2) noexcept
		{
			std::swap(string1._data, string2._data);
			std::swap(string1._length, string2._length);
			std::swap(string1._allocatedLength, string2._allocatedLength);
		}
	};
}

#endif // SP_STRING_HEADER
