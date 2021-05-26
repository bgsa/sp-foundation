#ifndef SP_CSV_FILE_READER_HEADER
#define SP_CSV_FILE_READER_HEADER

#include "SpectrumFoundation.h"
#include "FileSystem.h"
#include "SpString.h"

namespace NAMESPACE_FOUNDATION
{
#ifndef SP_CSV_SEPARATOR
	#define SP_CSV_SEPARATOR ','
#endif

	class SpCSVFileReader
	{
	private:
		SP_FILE file;
		sp_size fileLength;

	public:
		
		/// <summary>
		/// Default constructor
		/// </summary>
		/// <param name="filename">Full filename (with path)</param>
		/// <returns>void</returns>
		API_INTERFACE inline SpCSVFileReader(const sp_char* filename)
		{
			file.open(filename, SP_FILE_MODE_READ);
			fileLength = file.length();
		}

		/// <summary>
		/// Read a column from CSV file
		/// </summary>
		/// <param name="value">Output value</param>
		/// <param name="maxLength">Max length of value parameter</param>
		/// <returns>value parameter</returns>
		API_INTERFACE inline void readValue(sp_char* value, const sp_uint maxLength)
		{
			sp_assert(file.position() < fileLength, "InvalidOperationException");

			sp_char character = (sp_char)126;
			sp_uint valueIndex = 0;

			do
			{
				file.read(character);
				value[valueIndex++] = character;

				if (valueIndex == maxLength)
				{
					value[valueIndex - 1u] = END_OF_STRING;
					break;
				}
			}
			while (character != SP_CSV_SEPARATOR && character != END_OF_LINE && character != END_OF_STRING);

			value[valueIndex - 1u] = END_OF_STRING;
		}

		/// <summary>
		/// Release allocated resources
		/// </summary>
		/// <returns>void</returns>
		API_INTERFACE inline void dispose()
		{
			if (file.isOpened())
				file.close();
		}

		~SpCSVFileReader()
		{
			dispose();
		}

	};
}

#endif // SP_CSV_FILE_READER_HEADERER