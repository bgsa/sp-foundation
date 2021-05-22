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
			sp_char crlf[2];

			sp_uint counter = ZERO_SIZE;
			while (text[counter] != END_OF_STRING)
			{
				while (text[counter] != END_OF_LINE_LF
					&& std::strcmp(crlf, END_OF_LINE_CRLF) != 0
					&& text[counter] != END_OF_LINE_CR
					&& text[counter] != END_OF_STRING)
				{
					counter++;
					crlf[0] = crlf[1];
					crlf[1] = text[counter];
				}

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

			sp_char crlf[2];
			sp_uint counter = ZERO_UINT;
			for (sp_uint i = 0; i < _length; i++)
			{
				sp_uint lineSize = ZERO_UINT;

				while (text[counter] != END_OF_LINE_LF && text[counter] != END_OF_STRING 
					&& std::strcmp(crlf, END_OF_LINE_CRLF) != 0 && text[counter] != END_OF_LINE_CR)
				{
					crlf[0] = crlf[1];
					crlf[1] = text[counter];
					lineSize++;
					counter++;
				}

				_data[i] = sp_mem_new(SpString)(lineSize);

				std::memcpy(_data[i]->_data, &text[counter - lineSize], sizeof(sp_char) * lineSize);
				_data[i]->_data[lineSize] = END_OF_STRING;
				_data[i]->_length = lineSize;

				counter++;
			}
		}

		API_INTERFACE inline void add(const sp_char* line)
		{

		}

		API_INTERFACE inline sp_uint countLinesStartWith(const sp_char character)
		{
			sp_uint counter = ZERO_UINT;

			for (sp_uint i = 0; i < _length; i++)
				if (_data[i]->startWith(character))
					counter++;

			return counter;
		}

		API_INTERFACE inline sp_size countLinesStartWith(const sp_char* characteres)
		{
			sp_size counter = ZERO_SIZE;
			sp_size charLength = std::strlen(characteres);
			sp_bool found;
			
			for (sp_size i = 0; i < _length; i++)
			{
				found = false;

				for (sp_size j = 0; j < charLength; j++)
				{
					if (_data[i]->_data[j] != characteres[j])
					{
						found = true;
						break;
					}
					
				}

				if (found)
					counter++;
			}

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
