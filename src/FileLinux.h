#if defined(LINUX) || defined(OSX)

#ifndef FILE_LINUX_HEADER
#define FILE_LINUX_HEADER

#include "SpectrumFoundation.h"
#include <fstream>
#include "IFile.h"
#include <sys/stat.h>

namespace NAMESPACE_FOUNDATION
{
	class FileLinux 
		: public IFile
	{
	private:
		std::fstream file;

	public:

		API_INTERFACE sp_size sizeOfFile(const sp_char* filename) override;

		API_INTERFACE void readTextFile(const sp_char* filename, sp_char* text) override;

		API_INTERFACE void open(const sp_char* filename, std::ios_base::openmode mode) override;

		API_INTERFACE sp_bool isOpened() override;

		API_INTERFACE sp_bool isAtEnd() override;

		API_INTERFACE sp_size length() override;

		API_INTERFACE inline sp_size position() override
		{
			return (sp_size)file.tellg();
		}

		API_INTERFACE void seek(const sp_size position, std::ios_base::seekdir direction = std::ios::cur) override;

		API_INTERFACE void read(sp_char* buffer, sp_size size) override;

		API_INTERFACE inline void read(sp_char& buffer) override
		{
			file.read(&buffer, 1);
		}

		API_INTERFACE void write(const sp_char* buffer) override;

		API_INTERFACE SpString* readTextFile(const sp_char* filename) override;

		API_INTERFACE void close() override;

		API_INTERFACE ~FileLinux();
	};
}

#endif // FILE_LINUX_HEADER

#endif // LINUX
