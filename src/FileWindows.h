#ifdef WINDOWS

#ifndef FILE_WINDOWS_HEADER
#define FILE_WINDOWS_HEADER

#include <fstream>
#include "apollo.h"
#include "IFile.h"

class FileWindows : public IFile
{
private:
	FILE *file;

public:
	API_INTERFACE FileWindows(std::string filename);

	API_INTERFACE void read(void* buffer, sp_uint size, sp_uint count = 1);
	API_INTERFACE void seek(sp_long offset);
	API_INTERFACE void close();

	API_INTERFACE ~FileWindows();
};

#endif // !FILE_WINDOWS_HEADER

#endif // WINDOWS