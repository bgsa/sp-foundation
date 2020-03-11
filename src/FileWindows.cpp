#ifdef WINDOWS

#include "FileWindows.h"

namespace NAMESPACE_FOUNDATION
{
	FileWindows::FileWindows(std::string filename)
	{
		fopen_s(&file, filename.c_str(), "rb");
	}

	void FileWindows::read(void* buffer, sp_uint size, sp_uint count)
	{
		fread(buffer, size, count, file);
	}

	void FileWindows::seek(sp_long offset)
	{
		fseek(file, offset, SEEK_SET);
	}

	void FileWindows::close()
	{
		fclose(file);
	}

	FileWindows::~FileWindows()
	{
		if (file != nullptr)
			fclose(file);
	}
}

#endif //WINDOWS