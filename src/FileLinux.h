#ifdef LINUX

#ifndef FILE_LINUX_HEADER
#define FILE_LINUX_HEADER

#include "SpectrumFoundation.h"
#include <fstream>
#include "IFile.h"

namespace NAMESPACE_FOUNDATION
{
	class FileLinux : public IFile
	{
	private:
		FILE *file;

	public:
		API_INTERFACE FileLinux(std::string filename);

		API_INTERFACE void read(void* buffer, sp_uint size, sp_uint count = 1);
		API_INTERFACE void seek(sp_long offset);
		API_INTERFACE void close();

		API_INTERFACE ~FileLinux();
	};
}

#endif // !FILE_LINUX_HEADER

#endif // LINUX