#ifndef SP_STRING_HEADER
#define SP_STRING_HEADER

#include "SpectrumFoundation.h"
#include "Object.h"
#include "SpArray.h"
#include <stdlib.h>

namespace NAMESPACE_FOUNDATION
{
#define SP_DEFAULT_STRING_LENGTH 255
#define SP_DEFAULT_STRING_SIZE   256

	enum class EndOfLineType
	{
		LF = 1,
		CRLF = 2
	};
	
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
			sp_assert(length >= reserved, "IndexOutOfRangeException");

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
				_length = (sp_uint) std::strlen(source);
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
			sp_assert(value <= _allocatedLength, "IndexOutOfRange");
			_length = value;
		}

		API_INTERFACE inline void resize(const sp_uint newLength)
		{
			_allocatedLength = newLength;

			sp_char* newChar = (sp_char*) sp_mem_alloc(SIZEOF_CHAR * newLength);
			std::memcpy(newChar, _data, SIZEOF_CHAR * _length);
			newChar[_length] = END_OF_STRING;

			sp_mem_release(_data);
			_data = newChar;
		}

		API_INTERFACE inline void append(const sp_char* content, const sp_uint index = ZERO_UINT)
		{
			const sp_uint contentLength = std::strlen(content);

			std::memcpy(&_data[contentLength + index], &_data[index], SIZEOF_CHAR * _length);
			std::memcpy(&_data[index], content, SIZEOF_CHAR * contentLength);

			_length += contentLength;
			_data[_length] = END_OF_STRING;
		}

		API_INTERFACE inline sp_uint length() const
		{
			return _length;
		}

		API_INTERFACE inline sp_uint allocatedLength() const
		{
			return _allocatedLength;
		}

		API_INTERFACE inline SpString* substring(const sp_uint start, sp_uint end = ZERO_UINT)
		{
			sp_assert(start >= ZERO_UINT && end < _length, "IndexOutOfRange");

			if (end == ZERO_UINT)
				end = _length;

			SpString* str = sp_mem_new(SpString)(end - start + ONE_UINT, end - start);
			std::memcpy(str->_data, &_data[start], end - start);
			str->_data[end - start] = END_OF_STRING;

			return str;
		}

		API_INTERFACE inline sp_size hashCode() const noexcept override
		{
			sp_size hash = 0;
			sp_char* str = _data;

			for (; *str; ++str)
				hash ^= *str + 0x9e3779b9 + multiplyBy(hash, 6) + divideBy2(hash);

			return hash;
		}

		API_INTERFACE inline sp_bool equals(const void* other) const noexcept override
		{
			const SpString* str = (const SpString*)other;

			return (_length == str->_length) && this->hashCode() == str->hashCode();
			//return (_length == str->_length) && (std::strcmp(_data, str->_data) == ZERO_UINT);
		}

		API_INTERFACE inline sp_uint count(const sp_char character) const
		{
			sp_uint counter = ZERO_UINT;

			for (sp_uint i = ZERO_SIZE; i < _length; i++)
				if (_data[i] == character)
					counter++;

			return counter;
		}

		API_INTERFACE inline sp_uint indexOf(const sp_char character) const
		{
			for (sp_uint i = ZERO_SIZE; i < _length; i++)
				if (_data[i] == character)
					return i;

			return ZERO_UINT;
		}

		API_INTERFACE inline SpString* add(const sp_char character) noexcept
		{
			_data[_length++] = character;
			return this;
		}

		API_INTERFACE inline SpString* add(const sp_char* content) noexcept
		{
			const sp_uint len = std::strlen(content);

			sp_assert(_length + len < _allocatedLength, "InvalidArgumentException");

			std::memcpy(&_data[_length], content, len);
			_length += len;
			_data[_length] = END_OF_STRING;

			return this;
		}

		API_INTERFACE inline SpString* add(const sp_uint uintValue) noexcept
		{
			const sp_uint len = std::numeric_limits<sp_uint>::digits10 + 1u /*0-terminator*/;

			sp_assert(_length + len < _allocatedLength, "InvalidArgumentException");

			sprintf(&_data[_length], "%u", uintValue);
			_length += len;
			_data[_length] = END_OF_STRING;

			return this;
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
			sp_assert(index >= ZERO_INT && (sp_uint)index < _length, "IndexOutOfRangeException");
			return _data[index];
		}
		API_INTERFACE inline sp_char& operator[](const sp_int index)
		{
			sp_assert(index >= ZERO_INT && (sp_uint)index < _length, "IndexOutOfRangeException");
			return _data[index];
		}

		API_INTERFACE inline sp_char operator[](const sp_uint index) const
		{
			sp_assert(index >= ZERO_UINT && index < _length, "IndexOutOfRangeException");
			return _data[index];
		}
		API_INTERFACE inline sp_char& operator[](const sp_uint index)
		{
			sp_assert(index >= ZERO_UINT && index < _length, "IndexOutOfRangeException");
			return _data[index];
		}

#ifdef ENV_64BITS
		API_INTERFACE inline sp_char operator[](const sp_size index) const
		{
			sp_assert(index >= ZERO_SIZE && (sp_uint)index < _length, "IndexOutOfRangeException");
			return _data[index];
		}
		API_INTERFACE inline sp_char& operator[](const sp_size index)
		{
			sp_assert(index >= ZERO_SIZE && (sp_uint)index < _length, "IndexOutOfRangeException");
			return _data[index];
		}
#endif
		
		template <typename T>
		API_INTERFACE inline T to()
		{
			return (T)_data;
		}

		API_INTERFACE operator const sp_char*() const
		{ 
			return _data; 
		}

		API_INTERFACE inline sp_char* data()
		{
			return _data;
		}

		API_INTERFACE inline static SpString* convert(const sp_int intValue)
		{
			const sp_int maxSize = std::numeric_limits<sp_int>::digits10 + 1 /*sign*/ + 1 /*0-terminator*/;

			SpString* str = sp_mem_new(SpString)(maxSize, maxSize);
			sprintf(str->_data, "%d", intValue);
			str->_data[maxSize] = END_OF_STRING;

			return str;
		}

		API_INTERFACE inline static SpString* convert(const sp_uint uintValue)
		{
			const sp_uint maxSize = std::numeric_limits<sp_uint>::digits10 + 1 /*0-terminator*/;

			SpString* str = sp_mem_new(SpString)(maxSize, maxSize);
			sprintf(str->_data, "%u", uintValue);
			str->_data[maxSize] = END_OF_STRING;

			return str;
		}

		API_INTERFACE inline static SpString* convert(const sp_float floatValue)
		{
			const sp_int maxSize = std::numeric_limits<sp_float>::digits10 + 1 /*sign*/ + 1 /*0-terminator*/;

			SpString* str = sp_mem_new(SpString)(maxSize, maxSize);
			sprintf(str->_data, "%f", floatValue);
			str->_data[maxSize] = END_OF_STRING;

			return str;
		}

		API_INTERFACE inline static void convert(const sp_float floatValue, sp_char* value)
		{
			const sp_int maxSize = std::numeric_limits<sp_float>::digits10 + 1 /*sign*/ + 1 /*0-terminator*/;

			sprintf(value, "%f", floatValue);
			value[maxSize] = END_OF_STRING;
		}

		API_INTERFACE virtual const sp_char* toString() override
		{
			return _data;
		}

		API_INTERFACE static inline EndOfLineType endOfLineType(const sp_char* text)
		{
			const sp_uint length = std::strlen(text);
			
			if (length == ZERO_UINT)
				return EndOfLineType::LF;

			sp_char value[2];	
			value[0] = text[0];

			for (sp_uint i = 1; i < length; i++)
			{
				value[1] = text[i];

				if (std::strcmp(value, END_OF_LINE_CRLF) == 0)
					return EndOfLineType::CRLF;

				value[0] = value[1];
			}

			return EndOfLineType::LF;
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

	template <>
	API_INTERFACE inline sp_double SpString::to()
	{
		return std::atof(_data);
	}
	template <>
	API_INTERFACE inline sp_float SpString::to<>()
	{
		return (sp_float)std::atof(_data);
	}
	template <>
	API_INTERFACE inline sp_int SpString::to()
	{
		return std::atoi(_data);
	}
	template <>
	API_INTERFACE inline sp_uint SpString::to()
	{
		return (sp_uint) std::atoi(_data);
	}
	template <>
	API_INTERFACE inline sp_long SpString::to()
	{
		return std::atol(_data);
	}
}

#endif // SP_STRING_HEADER
