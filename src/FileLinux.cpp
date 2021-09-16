#if defined(LINUX) || defined(OSX)

#include "FileLinux.h"

namespace NAMESPACE_FOUNDATION
{

	sp_bool fileExists(const sp_char* filename)
	{
		struct stat status;

		const sp_bool exists = stat(filename, &status) == 0;

		if (!exists)
			errno = 0;

		return exists;
	}

	sp_size fileSize(const sp_char* filename)
	{
		struct stat st;

		stat(filename, &st);

		return  st.st_size;
	}

	sp_size FileLinux::sizeOfFile(const sp_char* filename)
	{
		return fileSize(filename);
	}

	void readTextFile(const sp_char* filename, sp_char* buffer, const sp_size bufferLength)
	{
		std::ifstream file;
		file.open(filename, std::ios::in | std::ios::binary);

		if (errno != 0)
		{
			sp_char* errorMessage = strerror(errno);
			sp_assert(false, errorMessage);
			errno = 0;
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

		for (sp_size i = bufferLength - ONE_SIZE; i > ZERO_SIZE && buffer[i] == '�'; i--)
			updateLength++;

		buffer[bufferLength - updateLength] = END_OF_STRING;

		file.close();	
	}

	void writeTextFile(const sp_char* filename, const sp_char* buffer, const sp_size bufferLength)
	{
		FileLinux file;
		file.open(filename, std::ios_base::out);
		file.write(buffer);
		file.close();
	}

	void FileLinux::open(const sp_char* filename, std::ios_base::openmode mode)
	{
		file.open(filename, mode);

		if (errno != 0)
		{
			sp_char* errorMessage = strerror(errno);
			sp_assert(false, errorMessage);
			errno = 0;
		}

		sp_assert(!file.bad(), "FileException");
		sp_assert(!file.fail(), "FileException");
		sp_assert(file.good(), "FileException");
	}

	sp_bool FileLinux::isOpened()
	{
		return file.is_open();
	}

	sp_size FileLinux::length()
	{
		std::streampos currentPoision = file.tellg();	

		file.seekg(ZERO_SIZE, std::ios_base::end);

		sp_size value = (sp_size)file.tellg();

		file.seekg(currentPoision, std::ios_base::beg);

		return value;
	}

	void FileLinux::seek(const sp_size position, std::ios_base::seekdir direction)
	{
		file.seekg(position, direction);
	}

	sp_bool FileLinux::isAtEnd()
	{
		return file.eof();
	}

	void FileLinux::read(sp_char* buffer, sp_size size)
	{
		file.read(buffer, size);
		buffer[size] = END_OF_STRING;
	}

	void FileLinux::write(const sp_char* buffer)
	{
		file << buffer;
	}

	SpString* FileLinux::readTextFile(const sp_char* filename)
	{
		open(filename, std::ios::in);

		const sp_uint len = length();

		sp_char* content = (sp_char*)sp_mem_alloc(len);
		read(content, len);

		close();

		return sp_mem_new(SpString)(content);
	}

	void FileLinux::readTextFile(const sp_char* filename, sp_char* text)
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

		for (sp_size i = len - ONE_SIZE; i > ZERO_SIZE && text[i] == '�'; i--)
			updateLength++;

		text[len - updateLength] = END_OF_STRING;

		close();
	}

	void FileLinux::close()
	{
		file.close();
	}

	FileLinux::~FileLinux()
	{
		if (file.is_open())
			file.close();
	}
}

#endif // LINUX
