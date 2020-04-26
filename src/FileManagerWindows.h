#ifdef WINDOWS

#ifndef FILE_MANAGER_WINDOWS_HEADER
#define FILE_MANAGER_WINDOWS_HEADER

#include "SpectrumFoundation.h"
#include <fstream>
#include <iostream>

#ifdef APIENTRY // avoid Windows.h redefine APIENTRY symbol
	#undef APIENTRY
#endif

#include "StringHelper.h"
#include "IFileManager.h"
#include "IFile.h"
#include "FileWindows.h"

namespace NAMESPACE_FOUNDATION
{
	class FileManagerWindows 
		: public IFileManager
	{
	public:
		API_INTERFACE std::vector<std::string> getFilesFromResource();

		API_INTERFACE std::vector<std::string> getFilesFromFolder(std::string folder, std::string suffix = "");

		API_INTERFACE  bool exists(const sp_char* filename);

	};
}

#endif // FILE_MANAGER_WINDOWS_HEADER

#endif // WINDOWS