#include "FileWindows.h"

#ifdef WINDOWS

namespace NAMESPACE_FOUNDATION
{

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

	void FileWindows::read(sp_char* buffer, sp_uint size)
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

		const sp_uint len = length();

		sp_char* content = (sp_char*)sp_mem_alloc(len + 1u);
		read(content, len);

		sp_uint updateLength = ZERO_UINT;
		for (sp_uint i = 1; i < len; i++)
		{
			const sp_char value[2] = { content[i - 1]  , content[i] };
			if ( std::strcmp(value, END_OF_LINE_CRLF) == 0)
				updateLength++;
		}

		for (sp_uint i = len - 1; i > 0 && content[i] == 'Í'; i--)
			updateLength++;
		
		content[len - updateLength] = END_OF_STRING;

		close();

		return sp_mem_new(SpString)(content);
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
