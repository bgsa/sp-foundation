#ifndef SP_CSV_FILE_WRITER_HEADER
#define SP_CSV_FILE_WRITER_HEADER

#include "SpectrumFoundation.h"
#include "FileSystem.h"
#include "SpString.h"

namespace NAMESPACE_FOUNDATION
{
#define SP_CSV_FILE_DEFAULT_BUFFER_SIZE 1024
#define SP_CSV_SEPARATOR ";"

	class SpCSVFileWriter
	{
	private:
		sp_size bufferSize;
		sp_size currentBuffer;
		sp_char* buffer;
		SP_FILE file;

	public:
		
		/// <summary>
		/// Default constructor
		/// </summary>
		/// <param name="filename">Full filename (with path)</param>
		/// <param name="bufferSize">Default internal buffer size</param>
		/// <returns>void</returns>
		API_INTERFACE inline SpCSVFileWriter(const sp_char* filename, const sp_size bufferSize = SP_CSV_FILE_DEFAULT_BUFFER_SIZE)
		{
			this->bufferSize = bufferSize;
			currentBuffer = ZERO_SIZE;
			buffer = sp_mem_new_array(sp_char, bufferSize);

			file.open(filename, SP_FILE_MODE_WRITE | SP_FILE_MODE_TRUNC);
		}

		/// <summary>
		/// Add header to CSV file
		/// </summary>
		/// <param name="headerName">Header/Column name</param>
		/// <returns>void</returns>
		API_INTERFACE inline SpCSVFileWriter* addHeader(const sp_char* headerName)
		{
			const sp_uint length = strlen(headerName);
			const sp_size size = length * sizeof(sp_char);

			if (currentBuffer + size + 1u > bufferSize)
				flush();

			std::memcpy(&buffer[currentBuffer], headerName, size);

			buffer[currentBuffer + size] = SP_CSV_SEPARATOR[0];
			currentBuffer += size + 1u;

			return this;
		}

		/// <summary>
		/// Add new value to the CSV file
		/// </summary>
		/// <param name="value">Content</param>
		/// <returns></returns>
		API_INTERFACE inline void addValue(const sp_char* value)
		{
			const sp_uint length = strlen(value);
			const sp_size size = length * sizeof(sp_char);

			if (currentBuffer + size + 1u > bufferSize)
				flush();

			std::memcpy(&buffer[currentBuffer], value, size);

			buffer[currentBuffer + size] = SP_CSV_SEPARATOR[0];
			currentBuffer += size + 1u;
		}

		/// <summary>
		/// Add new value to the CSV file
		/// </summary>
		/// <param name="value">Content</param>
		/// <returns></returns>
		API_INTERFACE inline void addValue(const sp_uint value)
		{
			sp_char text[20];
			SpString::convert(value, text);
			addValue(text);
		}

		/// <summary>
		/// Add new value to the CSV file
		/// </summary>
		/// <param name="value">Content</param>
		/// <returns></returns>
		API_INTERFACE inline void addValue(const sp_float value)
		{
			sp_char text[20];
			SpString::convert(value, text);
			addValue(text);
		}

		/// <summary>
		/// Add new record/line to CSV file
		/// </summary>
		/// <returns>void</returns>
		API_INTERFACE inline void newRecord()
		{
			buffer[currentBuffer++] = END_OF_LINE_LF;
		}

		/// <summary>
		/// Update buffer to the file
		/// </summary>
		/// <returns>void</returns>
		API_INTERFACE inline void flush()
		{
			if (currentBuffer == ZERO_UINT)
				return;

			buffer[currentBuffer] = END_OF_STRING;

			file.write(buffer);

			currentBuffer = ZERO_SIZE;
			std::memset(buffer, 0, bufferSize);
		}

		/// <summary>
		/// Release allocated resources
		/// </summary>
		/// <returns>void</returns>
		API_INTERFACE inline void dispose()
		{
			if (file.isOpened())
			{
				flush();
				file.close();
			}

			if (buffer != nullptr)
			{
				sp_mem_release(buffer);
				buffer = nullptr;
			}
		}

		~SpCSVFileWriter()
		{
			dispose();
		}

	};

#undef SP_CSV_FILE_DEFAULT_BUFFER_SIZE
}

#endif // SP_CSV_FILE_WRITER_HEADER