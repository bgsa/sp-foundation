#if defined(LINUX) || defined(OSX)

#include "FileLinux.h"

namespace NAMESPACE_FOUNDATION
{

	sp_bool fileExists(const sp_char* filename)
	{
		struct stat status;

		return stat(filename, &status) == 0;
	}

	inline sp_size fileSize(const sp_char* filename)
	{
		struct stat st;

		stat(filename, &st);

		return  st.st_size;
	}

	void FileLinux::open(const sp_char* filename, std::ios_base::openmode mode)
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
