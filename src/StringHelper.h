#ifndef STRING_HELPER_HEADER
#define STRING_HELPER_HEADER

#include "SpectrumFoundation.h"
#include <cstring>
#include <cctype>
#include <sstream>

#ifdef __cplusplus
	#include <vector>
#endif // __cplusplus

#define DEFAULT_STRING_LENGTH 256

namespace NAMESPACE_FOUNDATION
{
	class StringHelper
	{
	public:

		API_INTERFACE static inline sp_char* crate(sp_uint length = DEFAULT_STRING_LENGTH)
		{
			sp_char* buffer = ALLOC_ARRAY(sp_char, length);
			buffer[length] = END_OF_STRING;

			return buffer;
		}

		API_INTERFACE static inline void copy(const sp_char* source, sp_char* destination, sp_uint maxLength = 1024)
		{
			const sp_size sourceLength = strnlen(source, maxLength);

			std::strcpy(destination, source);

			destination[sourceLength] = '\0';
		}

		API_INTERFACE static inline void append(const sp_char* source, sp_char* destination, sp_uint destinationLength)
		{
			std::strcat(destination, source);
		}
		
	#ifdef __cplusplus

		static std::string toLowerCase(std::string value)
		{
			sp_char* stringAsArray = (sp_char*)value.c_str();

			for (sp_size i = 0; i < value.length(); i++)
				stringAsArray[i] = (sp_char) tolower(stringAsArray[i]);

			return std::string(stringAsArray);
		}

		static std::string toUpperCase(std::string value)
		{
			sp_char* stringAsArray = (sp_char*) value.c_str();

			for (sp_size i = 0; i < value.length(); i++)
				stringAsArray[i] = (sp_char) std::toupper(stringAsArray[i]);

			return std::string(stringAsArray);
		}

		static sp_bool startWith(std::string text, std::string value)
		{
			sp_size textLength = text.length();
			sp_size valueLength = value.length();

			if (valueLength > textLength)
				return false;
					
			std::string startSubstring = text.substr(0, valueLength);
			
			return std::strcmp(startSubstring.c_str(), value.c_str()) == 0;
		}

		static sp_bool startWith(const sp_char* text, const sp_char value)
		{
			for (sp_uint i = ZERO_UINT; i < UINT_MAX; i++)
			{
				if (text[i] == ' ')
					continue;

				return text[i] == value;
			}

			return false;
		}

		static sp_bool endWith(const sp_char* text, const sp_char* suffix)
		{
			if (text == nullptr || suffix == nullptr)
				return false;

			sp_size textLength = std::strlen(text);
			sp_size suffixLength = std::strlen(suffix);

			if (suffixLength > textLength)
				return false;

			return std::strncmp(text + textLength - suffixLength, suffix, suffixLength) == 0;
		}

		template <typename T>
		static std::string toString(T value)
		{
			std::ostringstream os;
			os << value;
			return os.str();
		}

		static std::vector<std::string> split(std::string text, const sp_char* separator)
		{
			std::vector<std::string> result;

			sp_char* values = std::strtok( (sp_char*) text.c_str(), separator);

			while (values != NULL)
			{
				result.push_back(values);
				values = std::strtok(NULL, separator);
			}

			return result;
		}

		static void split(sp_char* text, const sp_char* separator, sp_char** stringArray, sp_uint* arrayLength)
		{
			sp_char* token = std::strtok(text, separator);
			*arrayLength = ZERO_UINT;

			while (token != NULL)
			{
				stringArray[(*arrayLength)++] = token;
				token = std::strtok(NULL, separator);
			}
		}

	#endif // __cplusplus

	};
}

#endif // !STRING_HELPER_HEADER