#if defined(LINUX) || defined(OSX)

#include "FileManagerLinux.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <locale.h>

namespace NAMESPACE_FOUNDATION
{
	sp_bool checkFile(std::ifstream& file, const sp_char* filename)
	{
		if (errno == 0)
			return true;

		sp_char* errorMessage = strerror(errno);
		sp_assert(false, errorMessage);
		errno = 0;

		sp_assert(!file.bad(), "FileException");
		sp_assert(!file.fail(), "FileException");
		sp_assert(file.good(), "FileException");
		
		return false;
	}

	std::vector<std::string> FileManagerLinux::getFilesFromResource()
	{
		std::vector<std::string> files;
		files.push_back("teste.txt");
		return files;
	}

	std::vector<std::string> FileManagerLinux::getFilesFromFolder(std::string folder, std::string suffix)
	{
		std::vector<std::string> files;
		std::string search_path = folder + "/*.*";

		DIR *dp;
		struct dirent *entry;

		if((dp  = opendir(search_path.c_str())) == NULL) {

			sp_char* errorMessage = strerror(errno);

			sp_log_error1s(errorMessage);
			sp_log_error1s(search_path.c_str());

			return files;
		}

		struct stat sb;

		while ((entry = readdir(dp)) != NULL) {
			if( std::strcmp(entry->d_name, ".") != 0 && std::strcmp(entry->d_name, "..") != 0 )
			{
				stat(entry->d_name, &sb);

				if( S_ISREG(sb.st_mode) ) // is regular file?
					files.push_back(std::string(entry->d_name));
			}
		}

		closedir(dp);
		
		return files;
	}

	sp_bool FileManagerLinux::exists(const sp_char* filename)
	{
		struct stat status;

		if (stat(filename, &status) != 0) // file exists?
			return false;

		std::ifstream file(filename);

		sp_bool result = file.good();

		file.close();

		return result;
	}

	std::string FileManagerLinux::readTextFile(const sp_char* filename)
	{
		std::ifstream file(filename, std::ios::in);

		sp_assert(file.is_open(), "FileException");
		sp_assert(file.good(), "FileException");

		file.seekg(0, file.end);

		sp_size size = (sp_size) file.tellg();

		sp_char* content = (sp_char*) ALLOC_SIZE(size);

		file.seekg(0, file.beg);
		file.read(content, size);
		content[size] = '\0';

		file.close();

		std::string result(content);

		ALLOC_RELEASE(content);

		return result;
	}

	sp_char* FileManagerLinux::readBinaryFile(const sp_char* filename, sp_uint& size)
	{
		std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);

		sp_assert(file.is_open(), "FileException");
		sp_assert(file.good(), "FileException");

		size = (sp_uint) file.tellg();

		file.seekg(0, std::ios::beg);

		sp_char* content = (sp_char*) ALLOC_SIZE(size);

		file.read(content, size);

		file.close();

		return content;
	}

	IFile* FileManagerLinux::open(std::string filename)
	{
//		return new FileLinux(filename);
		return NULL;
	}
}

#endif // !LINUX
