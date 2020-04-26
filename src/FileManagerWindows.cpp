#include "FileManagerWindows.h"

#ifdef WINDOWS

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <locale.h>
#include <cassert>

namespace NAMESPACE_FOUNDATION
{

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

}

#endif