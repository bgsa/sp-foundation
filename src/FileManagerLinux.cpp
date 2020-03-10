#ifdef LINUX

#include "FileManagerLinux.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <locale.h>
#include <cassert>

sp_bool checkFile(std::ifstream& file, const sp_char * filename)
{
    if ( file.fail() || file.bad() || ! file.is_open() ) 
    {
		char errorMessage[1024];
		strerror_r(errno, errorMessage, 1024);

		std::string str1 = std::string(errorMessage);
		std::string str = ": ";
		std::string message = str1 + str + filename;
        
		Log::error(message);
        
        return false;
    }
    
    return true;
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

		char errorMessage[1024];
		strerror_r(errno, errorMessage, 1024);

		std::string str1 = std::string(errorMessage);
		std::string str = ": ";
		std::string message = str1 + str + search_path;
        
		Log::error(message);

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

	assert(file.is_open());
	assert(file.good());

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

	assert(file.is_open());
	assert(file.good());

	size = (sp_uint) file.tellg();

	file.seekg(0, std::ios::beg);

	sp_char* content = (sp_char*) ALLOC_SIZE(size);

	file.read(content, size);

	file.close();

	return content;
}

IFile* FileManagerLinux::open(std::string filename)
{
	return new FileLinux(filename);
}

#endif // !LINUX