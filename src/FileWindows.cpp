#include "FileWindows.h"

#ifdef WINDOWS

namespace NAMESPACE_FOUNDATION
{
	void FileWindows::open(const sp_char* filename, std::ios::open_mode mode)
	{
		file.open(filename, mode);

		sp_assert(!file.bad());
		sp_assert(!file.fail());
		sp_assert(file.good());
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