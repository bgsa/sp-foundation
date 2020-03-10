#ifdef LINUX

#include "FileLinux.h"

FileLinux::FileLinux(std::string filename)
{
	file = fopen(filename.c_str(), "rb");
}

void FileLinux::read(void* buffer, sp_uint size, sp_uint count)
{
	fread(buffer, size, count, file);
}

void FileLinux::seek(sp_long offset)
{
	fseek(file, offset, SEEK_SET);
}

void FileLinux::close()
{
	fclose(file);
}

FileLinux::~FileLinux()
{
	if (file != nullptr)
		fclose(file);
}

#endif //LINUX