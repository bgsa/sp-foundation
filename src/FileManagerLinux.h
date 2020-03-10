#ifdef LINUX

#ifndef FILE_MANAGER_LINUX_HEADER
#define FILE_MANAGER_LINUX_HEADER

#include "SpectrumFoundation.h"
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>

#include "StringHelper.h"
#include "IFileManager.h"
#include "IFile.h"
#include "FileLinux.h"

class FileManagerLinux : public IFileManager
{
public:
	API_INTERFACE std::vector<std::string> getFilesFromResource();

	API_INTERFACE std::vector<std::string> getFilesFromFolder(std::string folder, std::string suffix = "");

	API_INTERFACE std::string readTextFile(const sp_char* filename);

	API_INTERFACE sp_char* readBinaryFile(const sp_char* filename, sp_uint& size);
    
	API_INTERFACE sp_bool exists(const sp_char* filename);

	API_INTERFACE IFile* open(std::string filename);
};

#endif // FILE_MANAGER_LINUX_HEADER

#endif // LINUX