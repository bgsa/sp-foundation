#ifndef SP_STRING_HEADER
#define SP_STRING_HEADER

#include "SpectrumFoundation.h"
#include "Object.h"
#include "SpArray.h"
#include <stdlib.h>
#include <limits>
#include <stdio.h>
#include <stdint.h>
#include <iomanip>
#include <sstream>

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
		sp_size _allocatedLength;
		sp_size _length;
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

		API_INTERFACE SpString(const sp_size length, const sp_size reserved = ZERO_UINT)
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
			_allocatedLength = _length + ONE_SIZE;
			_data = (sp_char*)sp_mem_alloc(_allocatedLength);
			std::memcpy(_data, str, _allocatedLength);
		}

		API_INTERFACE SpString(const SpString& source)
		{
			_length = source._length;
			_allocatedLength = source._allocatedLength;
			_data = (sp_char*)sp_mem_alloc(_allocatedLength);
			std::memcpy(_data, source._data, _allocatedLength * sizeof(sp_char));
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

		API_INTERFACE inline void reserve(const sp_size value)
		{
			sp_assert(value <= _allocatedLength, "IndexOutOfRange");
			_length = value;
		}

		API_INTERFACE inline void resize(const sp_size newLength)
		{
			_allocatedLength = newLength;

			sp_char* newChar = (sp_char*) sp_mem_alloc(sizeof(sp_char) * newLength);
			std::memcpy(newChar, _data, sizeof(sp_char) * _length);
			newChar[_length] = END_OF_STRING;

			sp_mem_release(_data);
			_data = newChar;
		}

		API_INTERFACE inline void append(const sp_char* content, const sp_size index = ZERO_UINT)
		{
			const sp_size contentLength = std::strlen(content);

			std::memcpy(&_data[contentLength + index], &_data[index], sizeof(sp_char) * _length);
			std::memcpy(&_data[index], content, sizeof(sp_char) * contentLength);

			_length += contentLength;
			_data[_length] = END_OF_STRING;
		}

		API_INTERFACE inline sp_size length() const
		{
			return _length;
		}

		API_INTERFACE inline sp_size allocatedLength() const
		{
			return _allocatedLength;
		}

		API_INTERFACE inline SpString* substring(const sp_size start, sp_size end = ZERO_SIZE)
		{
			sp_assert(start >= ZERO_SIZE && end < _length, "IndexOutOfRange");

			if (end == ZERO_SIZE)
				end = _length;

			SpString* str = sp_mem_new(SpString)(end - start + ONE_UINT, end - start);
			std::memcpy(str->_data, &_data[start], end - start);
			str->_data[end - start] = END_OF_STRING;

			return str;
		}

		API_INTERFACE inline sp_size hashCode() const noexcept override
		{
			sp_size hash = ZERO_SIZE;
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
			const sp_size len = std::strlen(content);

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
			sp_size charLength = std::strlen(characteres);

			for (sp_size j = 0; j < charLength; j++)
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

#ifdef ENV_64BITS
		API_INTERFACE inline static void convert(const sp_size sizeValue, sp_char* value)
		{
			const sp_int maxSize = std::numeric_limits<sp_size>::digits10 + 1 /*0-terminator*/;

			sprintf(value, "%zu", sizeValue);
			value[maxSize] = END_OF_STRING;
		}
#endif

		API_INTERFACE inline static void convert(const sp_uint uintValue, sp_char* value)
		{
			const sp_int maxSize = std::numeric_limits<sp_uint>::digits10 + 1 /*0-terminator*/;

			sprintf(value, "%u", uintValue);
			value[maxSize] = END_OF_STRING;
		}

		API_INTERFACE inline static void convert(const sp_int intValue, sp_char* value)
		{
			const sp_int maxSize = std::numeric_limits<sp_int>::digits10 + 1 /*sign*/ + 1 /*0-terminator*/;

			sprintf(value, "%d", intValue);
			value[maxSize] = END_OF_STRING;
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

		API_INTERFACE inline static void convert(const sp_longlong llValue, sp_char* value)
		{
			const sp_int maxSize = std::numeric_limits<sp_longlong>::digits10 + 1 /*0-terminator*/;

			sprintf(value, "%lld", llValue);
			value[maxSize] = END_OF_STRING;
		}

		API_INTERFACE virtual const sp_char* toString() override
		{
			return _data;
		}

		API_INTERFACE static inline EndOfLineType endOfLineType(const sp_char* text)
		{
			const sp_size length = std::strlen(text);
			
			if (length == ZERO_SIZE)
				return EndOfLineType::LF;

			sp_char value[2];	
			value[0] = text[0];

			for (sp_size i = 1; i < length; i++)
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

	/// <summary>
	/// Convert a text content to a float
	/// </summary>
	/// <param name="text">C style string</param>
	/// <returns>Float value</returns>
	API_INTERFACE inline void convert(const sp_char* text, sp_float& value)
	{
		value = (sp_float)std::atof(text);
	}

	/// <summary>
	/// Convert a text content to a uint
	/// </summary>
	/// <param name="text">C style string</param>
	/// <returns>Unsigned Int value</returns>
	API_INTERFACE inline void convert(const sp_char* text, sp_uint& value)
	{
		value = (sp_uint)std::strtoul(text, nullptr, 0);
	}

#ifdef ENV_64BITS
	/// <summary>
	/// Convert a text content to a size
	/// </summary>
	/// <param name="text">C style string</param>
	/// <returns>Size value</returns>
	API_INTERFACE inline void convert(const sp_char* text, sp_size& value)
	{
		value = (sp_size)std::strtoull(text, NULL, 10);
		//value = (sp_size)_atoi64(text);
	}
#endif

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

	API_INTERFACE inline sp_bool endsWith(const sp_char* str, const sp_char* suffix)
	{
		const sp_size length = strlen(str);
		const sp_size lengthSuffix = strlen(suffix);

		sp_size suffixIndex = ZERO_SIZE;

		for (sp_size i = length - lengthSuffix; i < length; i++, suffixIndex++)
			if (str[i] != suffix[suffixIndex])
				return false;

		return true;
	}

	API_INTERFACE inline void convert(const sp_float floatValue, sp_char* output, sp_uint& length)
	{
		sprintf(output, "%f", floatValue);

		length = (sp_uint) std::strlen(output);

		output[length] = END_OF_STRING;
	}

	API_INTERFACE inline void convert(const sp_int intValue, sp_char* output, sp_uint& length)
	{
		sprintf(output, "%i", intValue);

		length = (sp_uint) std::strlen(output);

		output[length] = END_OF_STRING;
	}

	API_INTERFACE inline void convert(const sp_uint uintValue, sp_char* output, sp_uint& length)
	{
		sprintf(output, "%u", uintValue);
		
		length = (sp_uint) std::strlen(output);

		output[length] = END_OF_STRING;
	}

#ifdef ENV_64BITS

	/// <summary>
	/// Convert SIZE value to string
	/// </summary>
	/// <param name="sizeValue"></param>
	/// <param name="output">String</param>
	/// <param name="length">String Length</param>
	/// <returns>output parameter</returns>
	API_INTERFACE inline void convert(const sp_size sizeValue, sp_char* output, sp_size& length)
	{
		sprintf(output, "%zu", sizeValue);

		length = std::strlen(output);

		output[length] = END_OF_STRING;
	}

#endif

	/// <summary>
	/// Check the input string is null or empty
	/// </summary>
	/// <param name="input">Input string</param>
	/// <returns></returns>
	API_INTERFACE inline sp_bool strIsNullOrEmpty(const sp_char* input)
	{
		return input == nullptr || std::strlen(input) == 0;
	}

	/// <summary>
	/// Remove a content from input string by indexes (begin to end)
	/// </summary>
	/// <param name="input">Input String</param>
	/// <param name="inputLength">Input String Length</param>
	/// <param name="begin">Index Begin</param>
	/// <param name="end">Index End</param>
	/// <returns>void</returns>
	API_INTERFACE inline void strRemove(sp_char* input, const sp_size inputLength, const sp_size begin, const sp_size end)
	{
		std::memcpy(&input[begin], &input[end + 1], inputLength - end);
		input[inputLength - (end - begin) - 1] = END_OF_STRING;
	}

	API_INTERFACE inline void strReplace(const sp_char* input, sp_char pattern, sp_char newValue, sp_char* output)
	{
		const sp_size length = std::strlen(input);

		for (sp_size i = 0; i < length; i++)
			if (input[i] == pattern)
				output[i] = newValue;
			else
				output[i] = input[i];

		output[length] = END_OF_STRING;
	}

	/// <summary>
	/// Find all patterns in input string and replace by newValue
	/// </summary>
	/// <param name="input">Input String</param>
	/// <param name="pattern">Pattern to be searched</param>
	/// <param name="newValue">New Value to be replaced</param>
	/// <param name="output">New String</param>
	/// <returns>output parameter</returns>
	API_INTERFACE inline void strReplace(const sp_char* input, const sp_char* pattern, const sp_char* newValue, sp_char* output)
	{
		const sp_size inputLength = std::strlen(input);
		const sp_size patternLength = std::strlen(pattern);
		const sp_size newValueLength = std::strlen(newValue);

		sp_size index = SP_SIZE_MAX;
		sp_size patternIndex = 0;
		sp_size outputIndex = 0;

		for (sp_size i = 0; i < inputLength; i++)
		{
			if (input[i] == pattern[patternIndex])
				patternIndex++;
			else
			{
				patternIndex = 0;
				output[outputIndex++] = input[i];
			}

			if (patternIndex == patternLength) // match ?
			{
				std::memcpy(&output[outputIndex], newValue, sizeof(sp_char) * newValueLength);
				outputIndex += newValueLength;
				patternIndex = 0;
			}
		}

		output[outputIndex] = END_OF_STRING;
	}

	API_INTERFACE inline sp_int strIndexOf(const sp_char* input, sp_char pattern)
	{
		const sp_size length = std::strlen(input);

		for (sp_size i = 0; i < length; i++)
			if (input[i] == pattern)
				return (sp_int) i;

		return -1;
	}

	API_INTERFACE inline sp_size strIndexOf(const sp_char* input, const sp_char* pattern)
	{
		const sp_size length = std::strlen(input);
		const sp_size patternLength = std::strlen(pattern);
		sp_size patternIndex = ZERO_SIZE;
		sp_size idx = ZERO_SIZE;

		for (sp_size i = ZERO_SIZE; i < length; i++)
		{
			if (input[i] == pattern[patternIndex])
			{
				if (patternIndex == ZERO_SIZE)
					idx = i;

				patternIndex++;

				if (patternIndex == patternLength)
					return idx;
			}
			else
				idx = ZERO_SIZE;
		}

		return SP_SIZE_MAX;
	}

	API_INTERFACE inline sp_size strLastIndexOf(const sp_char* input, const sp_size inputLength, sp_char pattern)
	{
		for (sp_size i = inputLength; i != 0; i--)
			if (input[i] == pattern)
				return i;

		return SP_SIZE_MAX;
	}

	API_INTERFACE inline sp_bool strContains(const sp_char* input, const sp_char* pattern)
	{
		return strIndexOf(input, pattern) != SP_SIZE_MAX;
	}

	API_INTERFACE inline void strCountChar(const sp_char* value, sp_char character, sp_size& parameterSize, sp_size* indexes)
	{
		parameterSize = ZERO_SIZE;
		sp_size indexesLength = ZERO_SIZE;
		const sp_size valueLength = std::strlen(value);
		
		for (sp_size i = 0; i < valueLength; i++)
		{
			if (value[i] == character)
			{
				indexes[indexesLength++] = i;
				parameterSize++;
			}
		}
	}

	API_INTERFACE inline sp_bool strStartWith(const sp_char* text, const sp_size textLength, const sp_char* content, const sp_size contentLength)
	{
		for (sp_size j = 0; j < textLength; j++)
			if (text[j] != content[j])
				if (j == contentLength)
					return true;
				else
					return false;

		return true;
	}

	API_INTERFACE inline void strInsert(const sp_char* text, const sp_size textLength, const sp_char* content,  const sp_size contentLength, const sp_size index, sp_char* newText)
	{
		std::memcpy(newText, text, sizeof(sp_char) * index);
		std::memcpy(&newText[index], content, sizeof(sp_char) * contentLength);
		std::memcpy(&newText[index + contentLength], &text[index], textLength - index);
	}

	/// <summary>
	/// Convert a size value to Hex String
	/// </summary>
	/// <param name="value">Size Value</param>
	/// <param name="output">String in Hex</param>
	/// <returns>output parameter</returns>
	API_INTERFACE inline void strToHex(const sp_size value, sp_char* output)
	{
		std::stringstream stream;
		stream << std::hex << value;
		const sp_size len = stream.str().length();

		std::memcpy(output, "0x", 2);
		std::memcpy(&output[2], stream.str().c_str(), len);
		output[len + 2] = END_OF_STRING;
	}

	/// <summary>
	/// Convert a size value to Memory Address as string
	/// </summary>
	/// <param name="value">Size Value</param>
	/// <param name="output">Memory Address as string</param>
	/// <returns>output parameter</returns>
	API_INTERFACE inline void strToMemoryAddress(const sp_size value, sp_char* output, sp_uint& outputLength)
	{
		std::stringstream stream;
		stream << std::hex << value;
		const sp_uint len = (sp_uint)stream.str().length();

		const sp_uint complement = multiplyBy2(SIZEOF_WORD) - len;

		sp_uint shift = 2u;
		std::memcpy(output, "0x", shift);

		if (complement > ZERO_UINT)
		{
			for (sp_uint i = 0; i < complement; i++)
				output[shift + i] = '0';

			shift += complement;
		}

		std::memcpy(&output[shift], stream.str().c_str(), len);
		output[len + shift] = END_OF_STRING;
		outputLength = len + shift;
	}

#ifdef ENV_32BITS

	static const sp_uint crc32Table[256] = {
		0x00000000L, 0xF26B8303L, 0xE13B70F7L, 0x1350F3F4L,
		0xC79A971FL, 0x35F1141CL, 0x26A1E7E8L, 0xD4CA64EBL,
		0x8AD958CFL, 0x78B2DBCCL, 0x6BE22838L, 0x9989AB3BL,
		0x4D43CFD0L, 0xBF284CD3L, 0xAC78BF27L, 0x5E133C24L,
		0x105EC76FL, 0xE235446CL, 0xF165B798L, 0x030E349BL,
		0xD7C45070L, 0x25AFD373L, 0x36FF2087L, 0xC494A384L,
		0x9A879FA0L, 0x68EC1CA3L, 0x7BBCEF57L, 0x89D76C54L,
		0x5D1D08BFL, 0xAF768BBCL, 0xBC267848L, 0x4E4DFB4BL,
		0x20BD8EDEL, 0xD2D60DDDL, 0xC186FE29L, 0x33ED7D2AL,
		0xE72719C1L, 0x154C9AC2L, 0x061C6936L, 0xF477EA35L,
		0xAA64D611L, 0x580F5512L, 0x4B5FA6E6L, 0xB93425E5L,
		0x6DFE410EL, 0x9F95C20DL, 0x8CC531F9L, 0x7EAEB2FAL,
		0x30E349B1L, 0xC288CAB2L, 0xD1D83946L, 0x23B3BA45L,
		0xF779DEAEL, 0x05125DADL, 0x1642AE59L, 0xE4292D5AL,
		0xBA3A117EL, 0x4851927DL, 0x5B016189L, 0xA96AE28AL,
		0x7DA08661L, 0x8FCB0562L, 0x9C9BF696L, 0x6EF07595L,
		0x417B1DBCL, 0xB3109EBFL, 0xA0406D4BL, 0x522BEE48L,
		0x86E18AA3L, 0x748A09A0L, 0x67DAFA54L, 0x95B17957L,
		0xCBA24573L, 0x39C9C670L, 0x2A993584L, 0xD8F2B687L,
		0x0C38D26CL, 0xFE53516FL, 0xED03A29BL, 0x1F682198L,
		0x5125DAD3L, 0xA34E59D0L, 0xB01EAA24L, 0x42752927L,
		0x96BF4DCCL, 0x64D4CECFL, 0x77843D3BL, 0x85EFBE38L,
		0xDBFC821CL, 0x2997011FL, 0x3AC7F2EBL, 0xC8AC71E8L,
		0x1C661503L, 0xEE0D9600L, 0xFD5D65F4L, 0x0F36E6F7L,
		0x61C69362L, 0x93AD1061L, 0x80FDE395L, 0x72966096L,
		0xA65C047DL, 0x5437877EL, 0x4767748AL, 0xB50CF789L,
		0xEB1FCBADL, 0x197448AEL, 0x0A24BB5AL, 0xF84F3859L,
		0x2C855CB2L, 0xDEEEDFB1L, 0xCDBE2C45L, 0x3FD5AF46L,
		0x7198540DL, 0x83F3D70EL, 0x90A324FAL, 0x62C8A7F9L,
		0xB602C312L, 0x44694011L, 0x5739B3E5L, 0xA55230E6L,
		0xFB410CC2L, 0x092A8FC1L, 0x1A7A7C35L, 0xE811FF36L,
		0x3CDB9BDDL, 0xCEB018DEL, 0xDDE0EB2AL, 0x2F8B6829L,
		0x82F63B78L, 0x709DB87BL, 0x63CD4B8FL, 0x91A6C88CL,
		0x456CAC67L, 0xB7072F64L, 0xA457DC90L, 0x563C5F93L,
		0x082F63B7L, 0xFA44E0B4L, 0xE9141340L, 0x1B7F9043L,
		0xCFB5F4A8L, 0x3DDE77ABL, 0x2E8E845FL, 0xDCE5075CL,
		0x92A8FC17L, 0x60C37F14L, 0x73938CE0L, 0x81F80FE3L,
		0x55326B08L, 0xA759E80BL, 0xB4091BFFL, 0x466298FCL,
		0x1871A4D8L, 0xEA1A27DBL, 0xF94AD42FL, 0x0B21572CL,
		0xDFEB33C7L, 0x2D80B0C4L, 0x3ED04330L, 0xCCBBC033L,
		0xA24BB5A6L, 0x502036A5L, 0x4370C551L, 0xB11B4652L,
		0x65D122B9L, 0x97BAA1BAL, 0x84EA524EL, 0x7681D14DL,
		0x2892ED69L, 0xDAF96E6AL, 0xC9A99D9EL, 0x3BC21E9DL,
		0xEF087A76L, 0x1D63F975L, 0x0E330A81L, 0xFC588982L,
		0xB21572C9L, 0x407EF1CAL, 0x532E023EL, 0xA145813DL,
		0x758FE5D6L, 0x87E466D5L, 0x94B49521L, 0x66DF1622L,
		0x38CC2A06L, 0xCAA7A905L, 0xD9F75AF1L, 0x2B9CD9F2L,
		0xFF56BD19L, 0x0D3D3E1AL, 0x1E6DCDEEL, 0xEC064EEDL,
		0xC38D26C4L, 0x31E6A5C7L, 0x22B65633L, 0xD0DDD530L,
		0x0417B1DBL, 0xF67C32D8L, 0xE52CC12CL, 0x1747422FL,
		0x49547E0BL, 0xBB3FFD08L, 0xA86F0EFCL, 0x5A048DFFL,
		0x8ECEE914L, 0x7CA56A17L, 0x6FF599E3L, 0x9D9E1AE0L,
		0xD3D3E1ABL, 0x21B862A8L, 0x32E8915CL, 0xC083125FL,
		0x144976B4L, 0xE622F5B7L, 0xF5720643L, 0x07198540L,
		0x590AB964L, 0xAB613A67L, 0xB831C993L, 0x4A5A4A90L,
		0x9E902E7BL, 0x6CFBAD78L, 0x7FAB5E8CL, 0x8DC0DD8FL,
		0xE330A81AL, 0x115B2B19L, 0x020BD8EDL, 0xF0605BEEL,
		0x24AA3F05L, 0xD6C1BC06L, 0xC5914FF2L, 0x37FACCF1L,
		0x69E9F0D5L, 0x9B8273D6L, 0x88D28022L, 0x7AB90321L,
		0xAE7367CAL, 0x5C18E4C9L, 0x4F48173DL, 0xBD23943EL,
		0xF36E6F75L, 0x0105EC76L, 0x12551F82L, 0xE03E9C81L,
		0x34F4F86AL, 0xC69F7B69L, 0xD5CF889DL, 0x27A40B9EL,
		0x79B737BAL, 0x8BDCB4B9L, 0x988C474DL, 0x6AE7C44EL,
		0xBE2DA0A5L, 0x4C4623A6L, 0x5F16D052L, 0xAD7D5351L
	};

	// If CPP is greater than 11 (14, 17, 20, ...), it supports constspr with condicional and looping!
#if isCppGreatherThanCpp11
	#define USE_CONSTEXPR SP_CONSTEXPR
#else
	#define USE_CONSTEXPR
#endif
	API_INTERFACE USE_CONSTEXPR inline sp_uint strHash(const sp_char* text, sp_uint textLength, sp_uint crc = ZERO_UINT)
	{
		const uint8_t* p = (const uint8_t *)text;

		while (textLength--)
			crc = crc32Table[(crc ^ *p++) & 0xff] ^ (crc >> 8);

		return crc;
	}

#endif

#ifdef ENV_64BITS

	static const sp_size crc64Table[256] = {
		UINT64_C(0x0000000000000000), UINT64_C(0x7ad870c830358979),
		UINT64_C(0xf5b0e190606b12f2), UINT64_C(0x8f689158505e9b8b),
		UINT64_C(0xc038e5739841b68f), UINT64_C(0xbae095bba8743ff6),
		UINT64_C(0x358804e3f82aa47d), UINT64_C(0x4f50742bc81f2d04),
		UINT64_C(0xab28ecb46814fe75), UINT64_C(0xd1f09c7c5821770c),
		UINT64_C(0x5e980d24087fec87), UINT64_C(0x24407dec384a65fe),
		UINT64_C(0x6b1009c7f05548fa), UINT64_C(0x11c8790fc060c183),
		UINT64_C(0x9ea0e857903e5a08), UINT64_C(0xe478989fa00bd371),
		UINT64_C(0x7d08ff3b88be6f81), UINT64_C(0x07d08ff3b88be6f8),
		UINT64_C(0x88b81eabe8d57d73), UINT64_C(0xf2606e63d8e0f40a),
		UINT64_C(0xbd301a4810ffd90e), UINT64_C(0xc7e86a8020ca5077),
		UINT64_C(0x4880fbd87094cbfc), UINT64_C(0x32588b1040a14285),
		UINT64_C(0xd620138fe0aa91f4), UINT64_C(0xacf86347d09f188d),
		UINT64_C(0x2390f21f80c18306), UINT64_C(0x594882d7b0f40a7f),
		UINT64_C(0x1618f6fc78eb277b), UINT64_C(0x6cc0863448deae02),
		UINT64_C(0xe3a8176c18803589), UINT64_C(0x997067a428b5bcf0),
		UINT64_C(0xfa11fe77117cdf02), UINT64_C(0x80c98ebf2149567b),
		UINT64_C(0x0fa11fe77117cdf0), UINT64_C(0x75796f2f41224489),
		UINT64_C(0x3a291b04893d698d), UINT64_C(0x40f16bccb908e0f4),
		UINT64_C(0xcf99fa94e9567b7f), UINT64_C(0xb5418a5cd963f206),
		UINT64_C(0x513912c379682177), UINT64_C(0x2be1620b495da80e),
		UINT64_C(0xa489f35319033385), UINT64_C(0xde51839b2936bafc),
		UINT64_C(0x9101f7b0e12997f8), UINT64_C(0xebd98778d11c1e81),
		UINT64_C(0x64b116208142850a), UINT64_C(0x1e6966e8b1770c73),
		UINT64_C(0x8719014c99c2b083), UINT64_C(0xfdc17184a9f739fa),
		UINT64_C(0x72a9e0dcf9a9a271), UINT64_C(0x08719014c99c2b08),
		UINT64_C(0x4721e43f0183060c), UINT64_C(0x3df994f731b68f75),
		UINT64_C(0xb29105af61e814fe), UINT64_C(0xc849756751dd9d87),
		UINT64_C(0x2c31edf8f1d64ef6), UINT64_C(0x56e99d30c1e3c78f),
		UINT64_C(0xd9810c6891bd5c04), UINT64_C(0xa3597ca0a188d57d),
		UINT64_C(0xec09088b6997f879), UINT64_C(0x96d1784359a27100),
		UINT64_C(0x19b9e91b09fcea8b), UINT64_C(0x636199d339c963f2),
		UINT64_C(0xdf7adabd7a6e2d6f), UINT64_C(0xa5a2aa754a5ba416),
		UINT64_C(0x2aca3b2d1a053f9d), UINT64_C(0x50124be52a30b6e4),
		UINT64_C(0x1f423fcee22f9be0), UINT64_C(0x659a4f06d21a1299),
		UINT64_C(0xeaf2de5e82448912), UINT64_C(0x902aae96b271006b),
		UINT64_C(0x74523609127ad31a), UINT64_C(0x0e8a46c1224f5a63),
		UINT64_C(0x81e2d7997211c1e8), UINT64_C(0xfb3aa75142244891),
		UINT64_C(0xb46ad37a8a3b6595), UINT64_C(0xceb2a3b2ba0eecec),
		UINT64_C(0x41da32eaea507767), UINT64_C(0x3b024222da65fe1e),
		UINT64_C(0xa2722586f2d042ee), UINT64_C(0xd8aa554ec2e5cb97),
		UINT64_C(0x57c2c41692bb501c), UINT64_C(0x2d1ab4dea28ed965),
		UINT64_C(0x624ac0f56a91f461), UINT64_C(0x1892b03d5aa47d18),
		UINT64_C(0x97fa21650afae693), UINT64_C(0xed2251ad3acf6fea),
		UINT64_C(0x095ac9329ac4bc9b), UINT64_C(0x7382b9faaaf135e2),
		UINT64_C(0xfcea28a2faafae69), UINT64_C(0x8632586aca9a2710),
		UINT64_C(0xc9622c4102850a14), UINT64_C(0xb3ba5c8932b0836d),
		UINT64_C(0x3cd2cdd162ee18e6), UINT64_C(0x460abd1952db919f),
		UINT64_C(0x256b24ca6b12f26d), UINT64_C(0x5fb354025b277b14),
		UINT64_C(0xd0dbc55a0b79e09f), UINT64_C(0xaa03b5923b4c69e6),
		UINT64_C(0xe553c1b9f35344e2), UINT64_C(0x9f8bb171c366cd9b),
		UINT64_C(0x10e3202993385610), UINT64_C(0x6a3b50e1a30ddf69),
		UINT64_C(0x8e43c87e03060c18), UINT64_C(0xf49bb8b633338561),
		UINT64_C(0x7bf329ee636d1eea), UINT64_C(0x012b592653589793),
		UINT64_C(0x4e7b2d0d9b47ba97), UINT64_C(0x34a35dc5ab7233ee),
		UINT64_C(0xbbcbcc9dfb2ca865), UINT64_C(0xc113bc55cb19211c),
		UINT64_C(0x5863dbf1e3ac9dec), UINT64_C(0x22bbab39d3991495),
		UINT64_C(0xadd33a6183c78f1e), UINT64_C(0xd70b4aa9b3f20667),
		UINT64_C(0x985b3e827bed2b63), UINT64_C(0xe2834e4a4bd8a21a),
		UINT64_C(0x6debdf121b863991), UINT64_C(0x1733afda2bb3b0e8),
		UINT64_C(0xf34b37458bb86399), UINT64_C(0x8993478dbb8deae0),
		UINT64_C(0x06fbd6d5ebd3716b), UINT64_C(0x7c23a61ddbe6f812),
		UINT64_C(0x3373d23613f9d516), UINT64_C(0x49aba2fe23cc5c6f),
		UINT64_C(0xc6c333a67392c7e4), UINT64_C(0xbc1b436e43a74e9d),
		UINT64_C(0x95ac9329ac4bc9b5), UINT64_C(0xef74e3e19c7e40cc),
		UINT64_C(0x601c72b9cc20db47), UINT64_C(0x1ac40271fc15523e),
		UINT64_C(0x5594765a340a7f3a), UINT64_C(0x2f4c0692043ff643),
		UINT64_C(0xa02497ca54616dc8), UINT64_C(0xdafce7026454e4b1),
		UINT64_C(0x3e847f9dc45f37c0), UINT64_C(0x445c0f55f46abeb9),
		UINT64_C(0xcb349e0da4342532), UINT64_C(0xb1eceec59401ac4b),
		UINT64_C(0xfebc9aee5c1e814f), UINT64_C(0x8464ea266c2b0836),
		UINT64_C(0x0b0c7b7e3c7593bd), UINT64_C(0x71d40bb60c401ac4),
		UINT64_C(0xe8a46c1224f5a634), UINT64_C(0x927c1cda14c02f4d),
		UINT64_C(0x1d148d82449eb4c6), UINT64_C(0x67ccfd4a74ab3dbf),
		UINT64_C(0x289c8961bcb410bb), UINT64_C(0x5244f9a98c8199c2),
		UINT64_C(0xdd2c68f1dcdf0249), UINT64_C(0xa7f41839ecea8b30),
		UINT64_C(0x438c80a64ce15841), UINT64_C(0x3954f06e7cd4d138),
		UINT64_C(0xb63c61362c8a4ab3), UINT64_C(0xcce411fe1cbfc3ca),
		UINT64_C(0x83b465d5d4a0eece), UINT64_C(0xf96c151de49567b7),
		UINT64_C(0x76048445b4cbfc3c), UINT64_C(0x0cdcf48d84fe7545),
		UINT64_C(0x6fbd6d5ebd3716b7), UINT64_C(0x15651d968d029fce),
		UINT64_C(0x9a0d8ccedd5c0445), UINT64_C(0xe0d5fc06ed698d3c),
		UINT64_C(0xaf85882d2576a038), UINT64_C(0xd55df8e515432941),
		UINT64_C(0x5a3569bd451db2ca), UINT64_C(0x20ed197575283bb3),
		UINT64_C(0xc49581ead523e8c2), UINT64_C(0xbe4df122e51661bb),
		UINT64_C(0x3125607ab548fa30), UINT64_C(0x4bfd10b2857d7349),
		UINT64_C(0x04ad64994d625e4d), UINT64_C(0x7e7514517d57d734),
		UINT64_C(0xf11d85092d094cbf), UINT64_C(0x8bc5f5c11d3cc5c6),
		UINT64_C(0x12b5926535897936), UINT64_C(0x686de2ad05bcf04f),
		UINT64_C(0xe70573f555e26bc4), UINT64_C(0x9ddd033d65d7e2bd),
		UINT64_C(0xd28d7716adc8cfb9), UINT64_C(0xa85507de9dfd46c0),
		UINT64_C(0x273d9686cda3dd4b), UINT64_C(0x5de5e64efd965432),
		UINT64_C(0xb99d7ed15d9d8743), UINT64_C(0xc3450e196da80e3a),
		UINT64_C(0x4c2d9f413df695b1), UINT64_C(0x36f5ef890dc31cc8),
		UINT64_C(0x79a59ba2c5dc31cc), UINT64_C(0x037deb6af5e9b8b5),
		UINT64_C(0x8c157a32a5b7233e), UINT64_C(0xf6cd0afa9582aa47),
		UINT64_C(0x4ad64994d625e4da), UINT64_C(0x300e395ce6106da3),
		UINT64_C(0xbf66a804b64ef628), UINT64_C(0xc5bed8cc867b7f51),
		UINT64_C(0x8aeeace74e645255), UINT64_C(0xf036dc2f7e51db2c),
		UINT64_C(0x7f5e4d772e0f40a7), UINT64_C(0x05863dbf1e3ac9de),
		UINT64_C(0xe1fea520be311aaf), UINT64_C(0x9b26d5e88e0493d6),
		UINT64_C(0x144e44b0de5a085d), UINT64_C(0x6e963478ee6f8124),
		UINT64_C(0x21c640532670ac20), UINT64_C(0x5b1e309b16452559),
		UINT64_C(0xd476a1c3461bbed2), UINT64_C(0xaeaed10b762e37ab),
		UINT64_C(0x37deb6af5e9b8b5b), UINT64_C(0x4d06c6676eae0222),
		UINT64_C(0xc26e573f3ef099a9), UINT64_C(0xb8b627f70ec510d0),
		UINT64_C(0xf7e653dcc6da3dd4), UINT64_C(0x8d3e2314f6efb4ad),
		UINT64_C(0x0256b24ca6b12f26), UINT64_C(0x788ec2849684a65f),
		UINT64_C(0x9cf65a1b368f752e), UINT64_C(0xe62e2ad306bafc57),
		UINT64_C(0x6946bb8b56e467dc), UINT64_C(0x139ecb4366d1eea5),
		UINT64_C(0x5ccebf68aecec3a1), UINT64_C(0x2616cfa09efb4ad8),
		UINT64_C(0xa97e5ef8cea5d153), UINT64_C(0xd3a62e30fe90582a),
		UINT64_C(0xb0c7b7e3c7593bd8), UINT64_C(0xca1fc72bf76cb2a1),
		UINT64_C(0x45775673a732292a), UINT64_C(0x3faf26bb9707a053),
		UINT64_C(0x70ff52905f188d57), UINT64_C(0x0a2722586f2d042e),
		UINT64_C(0x854fb3003f739fa5), UINT64_C(0xff97c3c80f4616dc),
		UINT64_C(0x1bef5b57af4dc5ad), UINT64_C(0x61372b9f9f784cd4),
		UINT64_C(0xee5fbac7cf26d75f), UINT64_C(0x9487ca0fff135e26),
		UINT64_C(0xdbd7be24370c7322), UINT64_C(0xa10fceec0739fa5b),
		UINT64_C(0x2e675fb4576761d0), UINT64_C(0x54bf2f7c6752e8a9),
		UINT64_C(0xcdcf48d84fe75459), UINT64_C(0xb71738107fd2dd20),
		UINT64_C(0x387fa9482f8c46ab), UINT64_C(0x42a7d9801fb9cfd2),
		UINT64_C(0x0df7adabd7a6e2d6), UINT64_C(0x772fdd63e7936baf),
		UINT64_C(0xf8474c3bb7cdf024), UINT64_C(0x829f3cf387f8795d),
		UINT64_C(0x66e7a46c27f3aa2c), UINT64_C(0x1c3fd4a417c62355),
		UINT64_C(0x935745fc4798b8de), UINT64_C(0xe98f353477ad31a7),
		UINT64_C(0xa6df411fbfb21ca3), UINT64_C(0xdc0731d78f8795da),
		UINT64_C(0x536fa08fdfd90e51), UINT64_C(0x29b7d047efec8728),
	};

// If CPP is greater than 11 (14, 17, 20, ...), it supports constspr with condicional and looping!
#if isCppGreatherThanCpp11
	#define USE_CONSTEXPR SP_CONSTEXPR
#else
	#define USE_CONSTEXPR
#endif
	API_INTERFACE USE_CONSTEXPR inline sp_size strHash(const sp_char* text, sp_size textLength, sp_size crc = ZERO_SIZE)
	{
		for (sp_size j = 0; j < textLength; j++) 
			crc = crc64Table[(uint8_t)crc ^ text[j]] ^ (crc >> 8);

		return crc;
	}
#undef USE_CONSTEXPR

#endif

}

#endif // SP_STRING_HEADER
