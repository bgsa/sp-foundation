#include "SpString.h"
#include "SpArrayOfString.h"

namespace NAMESPACE_FOUNDATION
{
	API_INTERFACE SpArrayOfString* SpString::split(const sp_char separator)
	{
		const sp_uint length = count(separator);
		SpArrayOfString* result = sp_mem_new(SpArrayOfString)(length + ONE_UINT, length + ONE_UINT);

		sp_uint counter = ZERO_UINT;
		for (sp_uint i = ZERO_UINT; i < length + ONE_UINT; i++)
		{
			sp_uint charCounter = ZERO_UINT;

			while (_data[counter] != separator && _data[counter] != END_OF_STRING)
			{
				charCounter++;
				counter++;
			}

			sp_char* str = (sp_char*) sp_mem_calloc(charCounter + ONE_UINT, SIZEOF_CHAR);
			std::memcpy(str, &_data[counter - charCounter], charCounter);
			str[charCounter] = END_OF_STRING;

			result->_data[i] = str;

			counter++;
		}

		return result;
	}

}