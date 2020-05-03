#ifdef LINUX

#include "FileLinux.h"

namespace NAMESPACE_FOUNDATION
{
	void FileLinux::open(const sp_char* filename, std::ios::open_mode mode)
	{
		file.open(filename, mode);

		sp_assert(!file.bad());
		sp_assert(!file.fail());
		sp_assert(file.good());
	}

	sp_bool FileLinux::isOpened()
	{
		return file.is_open();
	}

	sp_size FileLinux::length()
	{
		file.seekg(ZERO_SIZE, std::ios_base::end);
		return file.tellg();
	}

	void FileLinux::seek(const sp_size position, std::ios_base::seekdir direction)
	{
		file.seekg(position, direction);
	}

	sp_bool FileLinux::isAtEnd()
	{
		return file.eof();
	}

	void FileLinux::read(sp_char* buffer, sp_uint size)
	{
		file.read(buffer, size);
	}

	void FileLinux::write(const sp_char* buffer)
	{
		file << buffer;
	}

	SpString* FileLinux::readTextFile(const sp_char* filename) override
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