#include "FileWindows.h"

#ifdef WINDOWS

namespace NAMESPACE_FOUNDATION
{

	sp_bool fileExists(const sp_char* filename)
	{
		DWORD handler = GetFileAttributesA(filename);

		if (handler != INVALID_FILE_ATTRIBUTES)
			return true;

		return GetLastError() != ERROR_FILE_NOT_FOUND;
	}

	sp_size fileSize(const sp_char* filename)
	{
		WIN32_FILE_ATTRIBUTE_DATA attributes;

		if (!GetFileAttributesExA(filename, GetFileExInfoStandard, &attributes))
			return -1; // error condition, could call GetLastError to find out more

		LARGE_INTEGER size;
		size.HighPart = attributes.nFileSizeHigh;
		size.LowPart = attributes.nFileSizeLow;

		return (sp_size)size.QuadPart;
	}

	void readTextFile(const sp_char* filename, sp_char* buffer, const sp_size bufferLength)
	{
		std::ifstream file;
		file.open(filename, std::ios::in | std::ios::binary);

		if (errno != NULL)
		{
			sp_char* errorMessage = strerror(errno);
			sp_assert(false, errorMessage);
			errno = NULL;
		}

		sp_assert(!file.bad(), "FileException");
		sp_assert(!file.fail(), "FileException");
		sp_assert(file.good(), "FileException");

		file.read(buffer, bufferLength);
		buffer[bufferLength] = END_OF_STRING;

		sp_size updateLength = ZERO_SIZE;
		for (sp_size i = ONE_SIZE; i < bufferLength; i++)
		{
			const sp_char value[2] = { buffer[i - 1]  , buffer[i] };
			if (std::strcmp(value, END_OF_LINE_CRLF) == 0)
				updateLength++;
		}

		for (sp_size i = bufferLength - ONE_SIZE; i > ZERO_SIZE && buffer[i] == 'Í'; i--)
			updateLength++;

		buffer[bufferLength - updateLength] = END_OF_STRING;

		file.close();
	}


	sp_size FileWindows::sizeOfFile(const sp_char* filename)
	{
		open(filename, std::ios::in | std::ios::ate);

		const sp_size value = (sp_size)file.tellg();

		close();

		return value;
	}

	void FileWindows::open(const sp_char* filename, std::ios_base::openmode mode)
	{
		file.open(filename, mode);

		if (errno != NULL)
		{
			sp_char* errorMessage = strerror(errno);
			sp_assert(false, errorMessage);
			errno = NULL;
		}

		sp_assert(!file.bad(), "FileException");
		sp_assert(!file.fail(), "FileException");
		sp_assert(file.good(), "FileException");
	}

	sp_bool FileWindows::isOpened()
	{
		return file.is_open();
	}

	sp_size FileWindows::length()
	{
		std::streampos currentPoision = file.tellg();	

		file.seekg(ZERO_SIZE, std::ios_base::end);

		sp_size value = (sp_size)file.tellg();

		file.seekg(currentPoision, std::ios_base::beg);

		return value;
	}

	void FileWindows::seek(const sp_size position, std::ios_base::seekdir direction)
	{
		file.seekg(position, direction);
	}

	sp_bool FileWindows::isAtEnd()
	{
		return file.eof();
	}

	void FileWindows::read(sp_char* buffer, sp_size size)
	{
		file.read(buffer, size);
		buffer[size] = END_OF_STRING;
	}

	void FileWindows::write(const sp_char* buffer)
	{
		file << buffer;
	}

	SpString* FileWindows::readTextFile(const sp_char* filename)
	{
		open(filename, std::ios::in | std::ios::binary);

		const sp_size len = length();

		sp_char* content = (sp_char*)sp_mem_alloc(len + 1u);
		read(content, len);

		sp_size updateLength = ZERO_SIZE;
		for (sp_size i = ONE_SIZE; i < len; i++)
		{
			const sp_char value[2] = { content[i - 1]  , content[i] };
			if ( std::strcmp(value, END_OF_LINE_CRLF) == 0)
				updateLength++;
		}

		for (sp_size i = len - ONE_SIZE; i > ZERO_SIZE && content[i] == 'Í'; i--)
			updateLength++;
		
		content[len - updateLength] = END_OF_STRING;

		close();

		return sp_mem_new(SpString)(content);
	}

	void FileWindows::readTextFile(const sp_char* filename, sp_char* text)
	{
		open(filename, std::ios::in);

		const sp_size len = length();
		read(text, len);

		// get the "real" length of file
		sp_size updateLength = ZERO_SIZE;
		for (sp_size i = ONE_SIZE; i < len; i++)
		{
			const sp_char value[2] = { text[i - 1]  , text[i] };
			if (std::strcmp(value, END_OF_LINE_CRLF) == 0)
				updateLength++;
		}

		for (sp_size i = len - ONE_SIZE; i > ZERO_SIZE && text[i] == 'Í'; i--)
			updateLength++;

		text[len - updateLength] = END_OF_STRING;

		close();
	}

	void FileWindows::close()
	{
		file.close();
	}

	FileWindows::~FileWindows()
	{
		if (file.is_open())
			file.close();
	}
}

#endif //WINDOWS
