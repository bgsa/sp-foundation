#include "FileManagerWindows.h"

#ifdef WINDOWS

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <locale.h>
#include <cassert>

bool checkFile(std::ifstream& file, const sp_char * filename)
{
    if ( file.fail() || file.bad() || ! file.is_open() ) 
    {
		const sp_uint errorMessageLength = 1024;
		char errorMessage[errorMessageLength];
		strerror_s(errorMessage, errorMessageLength, errno);

		std::string str1 = std::string(errorMessage);
		std::string str = ": ";
		std::string message = str1 + str + filename;
        
		Log::error(message);
        
        return false;
    }
    
    return true;
}

std::vector<std::string> FileManagerWindows::getFilesFromResource()
{
	std::vector<std::string> files;
	files.push_back("teste.txt");
	return files;
}

std::vector<std::string> FileManagerWindows::getFilesFromFolder(std::string folder, std::string suffix)
{
	std::vector<std::string> files;
	std::string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(search_path.c_str(), &fd);

	if (hFind != INVALID_HANDLE_VALUE) 
	{
		do 
		{
			bool isDirectory = fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
			
			if ( ! isDirectory )
			{
				std::string filename = fd.cFileName;

				if (suffix.empty())
					files.push_back(filename);
				else
					if (StringHelper::endWith(filename.c_str(), suffix.c_str()))
						files.push_back(filename);
			}
		} while (FindNextFile(hFind, &fd));

		FindClose(hFind);
	}

	return files;
}

bool FileManagerWindows::exists(const sp_char* filename)
{
	std::ifstream file(filename);

	bool result = file.good();

	file.close();

    return result;
}

std::string FileManagerWindows::readTextFile(const sp_char* filename)
{
	std::ifstream file(filename, std::ios::in);

	assert(file.is_open());
	assert(file.good());

	file.seekg(0, file.end);

	size_t size = (size_t) file.tellg();

	char* content = (char*) std::malloc(size);

	file.seekg(0, file.beg);
	file.read(content, size);
	content[size] = '\0';

	file.close();

	return std::string(content);
}

char* FileManagerWindows::readBinaryFile(const sp_char* filename, sp_uint& size)
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

IFile* FileManagerWindows::open(std::string filename)
{
	return new FileWindows(filename);
}

#endif