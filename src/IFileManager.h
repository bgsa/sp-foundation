#ifndef I_FILE_MANAGER_HEADER
#define I_FILE_MANAGER_HEADER

#include "IFile.h"

namespace NAMESPACE_FOUNDATION
{
	class IFileManager
	{
	public:
		virtual ~IFileManager() {};

		virtual std::vector<std::string> getFilesFromResource() = 0;

		virtual std::vector<std::string> getFilesFromFolder(std::string folder, std::string suffix = "") = 0;

		virtual std::string readTextFile(const sp_char* filename) = 0;

		virtual char* readBinaryFile(const sp_char* filename, sp_uint& size) = 0;

		virtual bool exists(const sp_char* filename) = 0;

		virtual IFile* open(std::string filename) = 0;
	};
}

#endif // I_FILE_MANAGER_HEADER