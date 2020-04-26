#ifdef WINDOWS

#include "FileWindows.h"

namespace NAMESPACE_FOUNDATION
{
	void FileWindows::open(const sp_char* filename, std::ios::open_mode mode)
	{
		file.open(filename, mode);

		assert(!file.bad());
		assert(!file.fail());
		assert(file.good());
	}

	sp_bool FileWindows::isOpened()
	{
		return file.is_open();
	}

	sp_size FileWindows::length()
	{
		file.seekg(ZERO_SIZE, std::ios_base::end);
		return (sp_size) file.tellg();
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