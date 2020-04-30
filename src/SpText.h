#ifndef SP_TEXT_HEADER
#define SP_TEXT_HEADER

#include "SpectrumFoundation.h"
#include "SpString.h"

namespace NAMESPACE_FOUNDATION
{
	class SpText
		: public SpArray<SpString*>
	{
	private:

		sp_uint countLines(const sp_char* text)
		{
			sp_uint lines = ZERO_SIZE;

			sp_uint counter = ZERO_SIZE;
			while (text[counter] != END_OF_STRING)
			{
				while (text[counter] != END_OF_LINE && text[counter] != END_OF_STRING)
					counter++;

				lines++;
				counter++;
			}

			return lines;
		}

	public:

		SpText(const sp_uint) = delete;
		SpText(SpString*, const sp_uint) = delete;

		API_INTERFACE SpText(const sp_char* text)
		{
			_length = countLines(text);
			_data = (SpString**) sp_mem_calloc(_length, sizeof(SpString*));

			sp_uint counter = ZERO_UINT;
			for (sp_uint i = 0; i < _length; i++)
			{
				sp_uint lineSize = ZERO_UINT;

				while (text[counter] != END_OF_LINE && text[counter] != END_OF_STRING)
				{
					lineSize++;
					counter++;
				}

				_data[i] = sp_mem_new(SpString)(lineSize);

				std::memcpy(_data[i]->_data, &text[counter - lineSize], SIZEOF_CHAR * lineSize);
				_data[i]->_data[lineSize] = END_OF_STRING;
				_data[i]->_length = lineSize;

				counter++;
			}
		}

		API_INTERFACE inline sp_uint countLinesStartWith(const sp_char character)
		{
			sp_uint counter = ZERO_UINT;

			for (sp_uint i = 0; i < _length; i++)
				if (_data[i]->startWith(character))
					counter++;

			return counter;
		}

		API_INTERFACE inline virtual const sp_char* toString() override
		{
			return "SpText";
		}

		API_INTERFACE inline virtual void dispose() override
		{
			if (_data != NULL)
			{
				for (sp_uint i = ZERO_UINT; i < _length; i++)
				{
					sp_mem_delete(_data[i], SpString);
				}

				sp_mem_release(_data);
				_length = ZERO_SIZE;
				_allocatedLength = ZERO_SIZE;
			}
		}

	};
}

#endif // SP_STRING_HEADER
